#include <iostream>
#include <Windows.h>
#include <fstream>
#include "disk.h"

bool spoofVolumeSerial(const std::string &drive, const std::string &newSerial)
{
    std::string command = "Volumeid " + drive + " " + newSerial;
    if (system(command.c_str()) == 0)
    {
        std::cout << "volume serial num spoof executed <3" << std::endl;
        return true;
    }
    else
    {
        std::cerr << "failed to spoof volume serial number :/" << std::endl;
        return false;
    }
}

void storeVolumeSerial(const std::string &drive)
{
    DWORD serialNumber = 0;
    GetVolumeInformationA(drive.c_str(), nullptr, 0, &serialNumber, nullptr, nullptr, nullptr, 0);
    std::ofstream snapshotFile("vol_snapshot.txt");
    snapshotFile << serialNumber << std::endl;
    snapshotFile.close();
}

void restoreVolumeSerial(const std::string &drive)
{
    std::ifstream snapshotFile("vol_snapshot.txt");
    DWORD serialNumber;
    snapshotFile >> serialNumber;
    snapshotFile.close();
    std::string command = "Volumeid " + drive + " " + std::to_string(serialNumber);
    system(command.c_str());
}
