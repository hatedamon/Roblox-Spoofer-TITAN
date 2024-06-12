/**
 * edid.c++
 * Spoofs monitors identifier (yes, roblox detects this)
 */

#include "../utils.hpp"
#include "../edid.hpp"

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>

std::string genRndEDID()
{
    std::ostringstream edid;
    for (int i = 0; i < 128; ++i)
    {
        edid << std::hex << (rand() % 256);
    }
    return edid.str();
}

void storeEDID()
{
    std::ofstream snapshotFile("../snapshots/edid_snapshot.txt");
    snapshotFile << getRegistryValue(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY", "EDID") << std::endl;
    snapshotFile.close();
}

void restoreEDID()
{
    std::ifstream snapshotFile("../snapshots/edid_snapshot.txt");
    std::string edidData;
    std::getline(snapshotFile, edidData);
    snapshotFile.close();
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY", "EDID", edidData);
}

void spoofEDID()
{
    std::string newEDID = genRndEDID();
    spoofRegistryKey(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY", "EDID", newEDID);
}