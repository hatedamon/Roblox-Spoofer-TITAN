#include <iostream>
#include <Windows.h>
#include <fstream>
#include "hwid.h"
#include "bios.h"

bool spoofRegistryKey(HKEY root, const std::string &subKey, const std::string &valueName, const std::string &newValue)
{
    HKEY hKey;
    if (RegOpenKeyExA(root, subKey.c_str(), 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS)
    {
        std::cerr << "failed to open rege key :/" << std::endl;
        return false;
    }

    if (RegSetValueExA(hKey, valueName.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE *>(newValue.c_str()), newValue.size()) != ERROR_SUCCESS)
    {
        std::cerr << "failed to set rege value" << std::endl;
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);
    std::cout << "rege key spoof executed" << std::endl;
    return true;
}

std::string getRegistryValue(HKEY root, const std::string &subKey, const std::string &valueName)
{
    HKEY hKey;
    char value[256];
    DWORD bufferSize = sizeof(value);

    if (RegOpenKeyExA(root, subKey.c_str(), 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
    {
        std::cerr << "failed to open rege key" << std::endl;
        return "";
    }

    if (RegQueryValueExA(hKey, valueName.c_str(), 0, NULL, (LPBYTE)value, &bufferSize) != ERROR_SUCCESS)
    {
        std::cerr << "faled to query rege value" << std::endl;
        RegCloseKey(hKey);
        return "";
    }

    RegCloseKey(hKey);
    return std::string(value);
}

void storeHWID()
{
    std::ofstream snapshotFile("hwid_snapshot.txt");

    // store bios serial number
    snapshotFile << getRegistryValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber") << std::endl;

    // store baseboard serial number
    snapshotFile << getRegistryValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber") << std::endl;

    snapshotFile.close();
}

void restoreHWID()
{
    std::ifstream snapshotFile("hwid_snapshot.txt");
    std::string biosSerialNumber, baseBoardSerialNumber;

    std::getline(snapshotFile, biosSerialNumber);
    std::getline(snapshotFile, baseBoardSerialNumber);

    snapshotFile.close();

    // restore bios serial num
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber", biosSerialNumber);

    // restore baseboard serial num
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber", baseBoardSerialNumber);
}

void spoofHWID()
{
    // spoof bios serial num
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber", "1234567890");

    // spoof baseboard serial num
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber", "0987654321");
}
