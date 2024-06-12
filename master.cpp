/**
 * APACHE PROTECTED
 * master.c++
 * compilation file
 * author @hatedamon
 */

#include "header/mac.hpp"
#include "header/disk.hpp"
#include "header/bios.hpp"
#include "header/edid.hpp"
#include "header/clean.hpp"

#include <iostream>
#include <ctime>

void createSnapshotDirectory()
{
    system("mkdir ./snapshots");
}

std::string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[20];
    sprintf(date, "%04d-%02d-%02d_%02d-%02d-%02d",
            1900 + ltm->tm_year,
            1 + ltm->tm_mon,
            ltm->tm_mday,
            ltm->tm_hour,
            ltm->tm_min,
            ltm->tm_sec);
    return std::string(date);
}

int main()
{
    createSnapshotDirectory();

    std::string date = getCurrentDate();
    std::string snapshotDirectory = "./snapshots/" + date;
    system(("mkdir " + snapshotDirectory).c_str());

    std::string choice;
    std::cout << "TITAN: Would you like to restore an old snapshot or spoof again? type: (restore/spoof): ";
    std::cin >> choice;

    if (choice == "restore")
    {
        delRBXIds();
        restoreSystemSnapshot();
        restoreHWIDAndBIOS();
        restoreVolumeSerial("C:");
        restoreEDID();
    }
    else if (choice == "spoof")
    {
        delRBXIds();
        storeSystemSnapshot();
        storeHWIDAndBIOS();
        storeVolumeSerial("C:");
        storeEDID();

        auto adapters = getNetworkAdapters();
        for (const auto &adapter : adapters)
        {
            std::string newMAC = generateRandomMAC();
            spoofMACAddress(adapter, newMAC);
        }

        std::string drive = "C:";
        std::string newSerial = generateRandomVolumeSerial();
        spoofVolumeSerial(drive, newSerial);
        spoofHWIDAndBIOS();
        spoofEDID();
    }
    else
    {
        std::cerr << "Invalid choice" << std::endl;
        return 1;
    }
    return 0;
}