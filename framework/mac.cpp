/**
 * mac.c++
 * Spoofs MAC Adapters
 */

#include "../header/mac.hpp"
#include "../header/utils.hpp"

#include <iostream>
#include <Windows.h>
#include <iphlpapi.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

#pragma comment(lib, "iphlpapi.lib")

std::string generateRandomMAC()
{
    std::ostringstream mac;
    for (int i = 0; i < 6; ++i)
    {
        int byte = rand() % 256;
        if (i != 0)
            mac << ":";
        mac << std::setw(2) << std::setfill('0') << std::hex << byte;
    }
    return mac.str();
}

std::vector<std::string> getNetworkAdapters()
{
    ULONG len = sizeof(IP_ADAPTER_INFO);
    IP_ADAPTER_INFO adapterInfo[16];
    DWORD dwRetVal = GetAdaptersInfo(adapterInfo, &len);

    std::vector<std::string> adapters;
    if (dwRetVal == ERROR_SUCCESS)
    {
        for (PIP_ADAPTER_INFO pAdapter = adapterInfo; pAdapter; pAdapter = pAdapter->Next)
        {
            adapters.push_back(pAdapter->AdapterName);
        }
    }
    else
    {
        std::cerr << "GetAdaptersInfo failed" << std::endl;
    }
    return adapters;
}

void spoofMACAddress(const std::string &adapterName, const std::string &newMAC)
{
    ULONG len = sizeof(IP_ADAPTER_INFO);
    IP_ADAPTER_INFO adapterInfo[16];
    DWORD dwRetVal = GetAdaptersInfo(adapterInfo, &len);

    if (dwRetVal != ERROR_SUCCESS)
    {
        std::cerr << "GetAdaptersInfo failed." << std::endl;
        return;
    }

    for (PIP_ADAPTER_INFO pAdapter = adapterInfo; pAdapter; pAdapter = pAdapter->Next)
    {
        if (pAdapter->AdapterName == adapterName)
        {
            ULONG macAddrLen = 6;
            BYTE newMACBytes[6];
            sscanf(newMAC.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                   &newMACBytes[0], &newMACBytes[1], &newMACBytes[2],
                   &newMACBytes[3], &newMACBytes[4], &newMACBytes[5]);

            memcpy(pAdapter->Address, newMACBytes, macAddrLen);
            std::cout << "adapter spoofed => " << adapterName << std::endl;
            return;
        }
    }

    std::cerr << "adapter not found => " << adapterName << std::endl;
}

void storeSystemSnapshot()
{
    auto adapters = getNetworkAdapters();
    std::ofstream snapshotFile("../snapshots/mac_snapshot.txt");

    ULONG len = sizeof(IP_ADAPTER_INFO);
    IP_ADAPTER_INFO adapterInfo[16];
    DWORD dwRetVal = GetAdaptersInfo(adapterInfo, &len);

    if (dwRetVal != ERROR_SUCCESS)
    {
        std::cerr << "GetAdaptersInfo failed" << std::endl;
        return;
    }

    for (const auto &adapter : adapters)
    {
        for (PIP_ADAPTER_INFO pAdapter = adapterInfo; pAdapter; pAdapter = pAdapter->Next)
        {
            if (pAdapter->AdapterName == adapter)
            {
                snapshotFile << adapter << " " << std::setw(2) << std::setfill('0') << std::hex
                             << static_cast<int>(pAdapter->Address[0]) << ":"
                             << static_cast<int>(pAdapter->Address[1]) << ":"
                             << static_cast<int>(pAdapter->Address[2]) << ":"
                             << static_cast<int>(pAdapter->Address[3]) << ":"
                             << static_cast<int>(pAdapter->Address[4]) << ":"
                             << static_cast<int>(pAdapter->Address[5]) << std::endl;
            }
        }
    }

    snapshotFile.close();
}

void restoreSystemSnapshot()
{
    std::ifstream snapshotFile("../snapshots/mac_snapshot.txt");
    std::string adapterName, macAddress;
    while (snapshotFile >> adapterName >> macAddress)
    {
        spoofMACAddress(adapterName, macAddress);
    }
}