#ifndef DISK_H
#define DISK_H

#include <string>

bool spoofVolumeSerial(const std::string &drive, const std::string &newSerial);
void storeVolumeSerial(const std::string &drive);
void restoreVolumeSerial(const std::string &drive);

#endif
