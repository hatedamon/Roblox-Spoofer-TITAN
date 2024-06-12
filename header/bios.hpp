#ifndef BIOS_HPP
#define BIOS_HPP

#include <string>

std::string generateRandomSerial();
void storeHWIDAndBIOS();
void restoreHWIDAndBIOS();
void spoofHWIDAndBIOS();

#endif // BIOS_HPP