#include <iostream>
#include <Windows.h>
#include "bios.h"

bool spoofRegistryKey(HKEY root, const std::string &subKey, const std::string &valueName, const std::string &newValue)
{
    HKEY hKey;
    if (RegOpenKeyExA(root, subKey.c_str(), 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS)
    {
        std::cerr << "failed to open rege key" << std::endl;
        return false;
    }

    if (RegSetValueExA(hKey, valueName.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE *>(newValue.c_str()), newValue.size()) != ERROR_SUCCESS)
    {
        std::cerr << "failed to set rege value" << std::endl;
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);
    std::cout << "Registry key spoofed successfully." << std::endl;
    return true;
}

void spoofBIOS()
{
    // bio serial num
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber", "1234567890");

    // baseboard serial num
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber", "0987654321");
}

void storeBIOSInfo()
{
    // logic to store current bios info
}

void restoreBIOSInfo()
{
    // logic to restore bios info from snapshot
}
