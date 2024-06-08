#ifndef BIOS_H
#define BIOS_H

#include <string>

bool spoofRegistryKey(HKEY root, const std::string &subKey, const std::string &valueName, const std::string &newValue);
void spoofBIOS();
void storeBIOSInfo();
void restoreBIOSInfo();

#endif
