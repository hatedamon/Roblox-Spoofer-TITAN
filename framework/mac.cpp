#include <iostream>
#include <Windows.h>
#include <iphlpapi.h>
#include <iomanip>
#include <vector>
#include "mac.h"

#pragma comment(lib, "iphlpapi.lib")

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
        std::cerr << "GetAdaptersInfo failed :0" << std::endl;
    }
    return adapters;
}

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

void spoofMACAddress(const std::string &adapterName, const std::string &newMAC)
{
    ULONG len = sizeof(IP_ADAPTER_INFO);
    IP_ADAPTER_INFO adapterInfo[16]; // alloc info
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
            std::cout << "MAC addy spoofed successfully 4 adapter: " << adapterName << std::endl;
            return;
        }
    }

    std::cerr << "adapter not found: " << adapterName << std::endl;
}

void storeSystemSnapshot()
{
    // save current network state
    auto adapters = getNetworkAdapters();
    std::ofstream snapshotFile("snapshot.txt");

    for (const auto &adapter : adapters)
    {
        snapshotFile << adapter << std::endl;
    }
    snapshotFile.close();
}

void restoreSystemSnapshot()
{
#include <iostream>
#include <Windows.h>
#include <iphlpapi.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include "mac.h"

#pragma comment(lib, "iphlpapi.lib")

    std::vector<std::string> getNetworkAdapters()
    {
        ULONG len = sizeof(IP_ADAPTER_INFO);
        IP_ADAPTER_INFO adapterInfo[16]; // alloc info
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
            std::cerr << "GetAdaptersInfo failed." << std::endl;
        }
        return adapters;
    }

    std::string generateRandomMAC()
    {
        std::ostringstream

            std::ifstream snapshotFile("snapshot.txt");
        std::string line;
        while (std::getline(snapshotFile, line))
        {
            // logic to restore each adapter to its original state
        }
    }
}