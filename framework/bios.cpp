#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>

#include "../bios.hpp"
#include "../utils.hpp"

std::string generateRandomSerial()
{
    std::ostringstream serial;
    for (int i = 0; i < 10; ++i)
    {
        serial << rand() % 10;
    }
    return serial.str();
}

void spoofBIOS()
{
    std::string newSystemSerial = generateRandomSerial();
    std::string newBaseBoardSerial = generateRandomSerial();
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber", newSystemSerial);
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber", newBaseBoardSerial);
}

void storeBIOSInfo()
{
    std::ofstream snapshotFile("../snapshots/bios_snapshot.txt");
    snapshotFile << getRegistryValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber") << std::endl;
    snapshotFile << getRegistryValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber") << std::endl;
    snapshotFile.close();
}

void restoreBIOSInfo()
{
    std::ifstream snapshotFile("../snapshots/bios_snapshot.txt");
    std::string biosSerialNumber, baseBoardSerialNumber;
    std::getline(snapshotFile, biosSerialNumber);
    std::getline(snapshotFile, baseBoardSerialNumber);
    snapshotFile.close();
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber", biosSerialNumber);
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber", baseBoardSerialNumber);
}