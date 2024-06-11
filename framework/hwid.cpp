#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>

#include "../hwid.hpp"
#include "../utils.hpp"

std::string generateRandomHWID()
{
    std::ostringstream hwid;
    for (int i = 0; i < 10; ++i)
    {
        hwid << rand() % 10;
    }
    return hwid.str();
}

void storeHWID()
{
    std::ofstream snapshotFile("../snapshots/hwid_snapshot.txt");
    snapshotFile << getRegistryValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber") << std::endl;
    snapshotFile << getRegistryValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber") << std::endl;
    snapshotFile.close();
}

void restoreHWID()
{
    std::ifstream snapshotFile("../snapshots/hwid_snapshot.txt");
    std::string biosSerialNumber, baseBoardSerialNumber;
    std::getline(snapshotFile, biosSerialNumber);
    std::getline(snapshotFile, baseBoardSerialNumber);
    snapshotFile.close();
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber", biosSerialNumber);
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber", baseBoardSerialNumber);
}

void spoofHWID()
{
    std::string newSystemSerial = generateRandomHWID();
    std::string newBaseBoardSerial = generateRandomHWID();
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber", newSystemSerial);
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber", newBaseBoardSerial);
}