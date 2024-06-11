#ifndef BIOS_HPP
#define BIOS_HPP

#include <string>
#include <windows.h>

std::string getRegistryValue(HKEY root, const std::string &subKey, const std::string &valueName);

bool spoofRegistryKey(HKEY root, const std::string &subKey, const std::string &valueName, const std::string &newValue);
void spoofBIOS();
void storeBIOSInfo();
void restoreBIOSInfo();

#endif
