/**
 * bios.c++
 * Spoofs BIOS & Baseboard
 */

#include "../bios.hpp"
#include "../utils.hpp"

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>

std::string generateRandomSerial()
{
    std::ostringstream serial;
    for (int i = 0; i < 10; ++i)
    {
        serial << rand() % 10;
    }
    return serial.str();
}

void storeHWIDAndBIOS()
{
    std::ofstream snapshotFile("../snapshots/hwid_bios_snapshot.txt");
    snapshotFile << getRegistryValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber") << std::endl;
    snapshotFile << getRegistryValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber") << std::endl;
    snapshotFile.close();
}

void restoreHWIDAndBIOS()
{
    std::ifstream snapshotFile("../snapshots/hwid_bios_snapshot.txt");
    std::string biosSerialNumber, baseBoardSerialNumber;
    std::getline(snapshotFile, biosSerialNumber);
    std::getline(snapshotFile, baseBoardSerialNumber);
    snapshotFile.close();
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber", biosSerialNumber);
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber", baseBoardSerialNumber);
}

void spoofHWIDAndBIOS()
{
    std::string newSystemSerial = generateRandomSerial();
    std::string newBaseBoardSerial = generateRandomSerial();
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSerialNumber", newSystemSerial);
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardSerialNumber", newBaseBoardSerial);
}