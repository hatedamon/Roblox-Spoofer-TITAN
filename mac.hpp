#ifndef MAC_HPP
#define MAC_HPP

#include <string>
#include <vector>

std::vector<std::string> getNetworkAdapters();
std::string generateRandomMAC();

void spoofMACAddress(const std::string &adapterName, const std::string &newMAC);
void storeSystemSnapshot();
void restoreSystemSnapshot();

#endif