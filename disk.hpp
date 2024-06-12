#ifndef DISK_HPP
#define DISK_HPP

#include <string>

std::string generateRandomVolumeSerial();

bool spoofVolumeSerial(const std::string &drive, const std::string &newSerial);
void storeVolumeSerial(const std::string &drive);
void restoreVolumeSerial(const std::string &drive);

#endif // DISK_HPP