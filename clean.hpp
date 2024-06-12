#ifndef CLEAN_HPP
#define CLEAN_HPP

#include <string>
#include <vector>

void delRBXIds();
bool delFile(const std::string &filePath);
bool delDir(const std::string &dirPath);
std::vector<std::string> getDrives();
bool pathExists(const std::string &path);
std::string getLocalAppDataPath();
std::string findRobloxPath();

#endif // CLEAN_HPP