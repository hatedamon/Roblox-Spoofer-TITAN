/**
 * utils.c++
 * Handles bios.c++
 */

#include "../utils.hpp"

#include <iostream>
#include <Windows.h>

bool spoofRegistryKey(HKEY root, const std::string &subKey, const std::string &valueName, const std::string &newValue)
{
    HKEY hKey;
    if (RegOpenKeyExA(root, subKey.c_str(), 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS)
    {
        std::cerr << "failed to open registry key" << std::endl;
        return false;
    }
    if (RegSetValueExA(hKey, valueName.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE *>(newValue.c_str()), newValue.size()) != ERROR_SUCCESS)
    {
        std::cerr << "failed to set registry value" << std::endl;
        RegCloseKey(hKey);
        return false;
    }
    RegCloseKey(hKey);
    std::cout << "registry key spoofed successfully." << std::endl;
    return true;
}

std::string getRegistryValue(HKEY root, const std::string &subKey, const std::string &valueName)
{
    HKEY hKey;
    char value[256];
    DWORD bufferSize = sizeof(value);

    if (RegOpenKeyExA(root, subKey.c_str(), 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
    {
        std::cerr << "failed to open registry key" << std::endl;
        return "";
    }

    if (RegQueryValueExA(hKey, valueName.c_str(), 0, NULL, (LPBYTE)value, &bufferSize) != ERROR_SUCCESS)
    {
        std::cerr << "failed to query registry value" << std::endl;
        RegCloseKey(hKey);
        return "";
    }

    RegCloseKey(hKey);
    return std::string(value);
}