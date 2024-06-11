#include <iostream>
#include <ctime>

#include "mac.hpp"
#include "disk.hpp"
#include "bios.hpp"
#include "hwid.hpp"

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
        restoreSystemSnapshot();
        restoreHWID();
        restoreVolumeSerial("C:");
        restoreBIOSInfo();
    }
    else if (choice == "spoof")
    {
        storeSystemSnapshot();
        storeHWID();
        storeVolumeSerial("C:");
        storeBIOSInfo();

        auto adapters = getNetworkAdapters();
        for (const auto &adapter : adapters)
        {
            std::string newMAC = generateRandomMAC();
            spoofMACAddress(adapter, newMAC);
        }

        std::string drive = "C:";
        std::string newSerial = generateRandomVolumeSerial();
        spoofVolumeSerial(drive, newSerial);

        spoofBIOS();
        spoofHWID();
    }
    else
    {
        std::cerr << "Invalid choice" << std::endl;
        return 1;
    }
    return 0;
}
