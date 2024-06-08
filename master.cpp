#include <iostream>
#include "mac.h"
#include "disk.h"
#include "bios.h"
#include "hwid.h"

int main()
{
    // store current sys snapshot so rollback is possible
    storeSystemSnapshot();
    storeHWID();

    // spoof mac addy
    auto adapters = getNetworkAdapters();
    for (const auto &adapter : adapters)
    {
        std::string newMAC = generateRandomMAC();
        spoofMACAddress(adapter, newMAC);
    }

    // spoof vol serials
    std::string drive = "C:";
    std::string newSerial = "1234-5678";
    spoofVolumeSerial(drive, newSerial);

    // spoof bio & hardware id
    spoofBIOS();
    spoofHWID();

    // restore sys state (optional)
    // restoreSystemSnapshot();
    // restoreHWID();

    return 0;
}
