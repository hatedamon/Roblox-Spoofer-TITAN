/**
 * clean.c++
 * log cleanup
 * clears rbx logs + settings to essentially remove history and callbacks
 * might force roblox re-install
 */

#include "../clean.hpp"

#include <iostream>
#include <filesystem>
#include <windows.h>
#include <shlobj.h>

namespace fs = std::filesystem;

void delRBXIds()
{
    std::string robloxPath = findRobloxPath();

    if (robloxPath.empty())
    {
        std::cerr << "Roblox directory not found." << std::endl;
        return;
    }

    // del logs
    std::string logsDir = robloxPath + "logs";
    if (pathExists(logsDir))
    {
        delDir(logsDir);
    }
    std::vector<std::string> filesToDelete = {
        robloxPath + "AnalysticsSettings.xml",
        robloxPath + "GlobalBasicSettings_13.xml",
        robloxPath + "GlobalBasicSettings_13_Studio.xml",
        robloxPath + "LocalStorage\\appStorage.json" };
    for (const std::string& filePath : filesToDelete)
    {
        if (pathExists(filePath))
        {
            delFile(filePath);
        }
    }

    // del clientsets
    std::string clientSettingsDir = robloxPath + "ClientSettings";
    if (pathExists(clientSettingsDir))
    {
        delDir(clientSettingsDir);
    }

    // del plugins
    for (const auto& entry : fs::directory_iterator(robloxPath))
    {
        if (fs::is_directory(entry) && entry.path().filename() == "InstalledPlugins")
        {
            delDir(entry.path().string());
        }
    }

    // del sense files
    for (const auto& entry : fs::recursive_directory_iterator(robloxPath))
    {
        if (fs::is_regular_file(entry))
        {
            std::string fileName = entry.path().filename().string();
            if (fileName.find("hwid") != std::string::npos ||
                fileName.find("ip") != std::string::npos ||
                fileName.find("log") != std::string::npos)
            {
                delFile(entry.path().string());
            }
        }
    }
}

bool delFile(const std::string& filePath)
{
    try
    { // use FILEOPSTRUCT to del w/o user interaction or recycle bin bs
        SHFILEOPSTRUCTW fileOp;
        ZeroMemory(&fileOp, sizeof(SHFILEOPSTRUCTW));
        fileOp.wFunc = FO_DELETE;
        std::wstring wFilePath = std::filesystem::path(filePath).wstring() + L'\0';
        fileOp.pFrom = wFilePath.c_str();
        fileOp.fFlags = FOF_NO_UI | FOF_NOCONFIRMATION | FOF_SILENT | FOF_ALLOWUNDO;
        return SHFileOperationW(&fileOp) == 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "error deleting: " << e.what() << std::endl;
        return false;
    }
}

bool delDir(const std::string& dirPath)
{
    try
    { // same here
        SHFILEOPSTRUCTW fileOp;
        ZeroMemory(&fileOp, sizeof(SHFILEOPSTRUCTW));
        fileOp.wFunc = FO_DELETE;
        std::wstring wDirPath = std::filesystem::path(dirPath).wstring() + L'\0';
        fileOp.pFrom = wDirPath.c_str();
        fileOp.fFlags = FOF_NO_UI | FOF_NOCONFIRMATION | FOF_SILENT | FOF_ALLOWUNDO;
        return SHFileOperationW(&fileOp) == 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "error deleting dir: " << e.what() << std::endl;
        return false;
    }
}

// find drives so i can find shit
std::vector<std::string> getDrives()
{
    std::vector<std::string> drives;
    char drive = 'A';
    DWORD driveMask = GetLogicalDrives();
    while (driveMask)
    {
        if (driveMask & 1)
        {
            drives.push_back(std::string(1, drive) + ":\\");
        }
        driveMask >>= 1;
        ++drive;
    }
    return drives;
}

// woah, dont look at shit that doesnt exist?
// magical.
bool pathExists(const std::string& path)
{
    return fs::exists(path);
}

// again, looking for shit
std::string getLocalAppDataPath()
{
    char* localAppData;
    size_t len;
    _dupenv_s(&localAppData, &len, "LOCALAPPDATA");
    std::string localAppDataPath = localAppData;
    free(localAppData);
    return localAppDataPath;
}

// same here
std::string findRobloxPath()
{
    std::string localAppDataPath = getLocalAppDataPath();
    std::string robloxPath = localAppDataPath + "\\Roblox\\";
    return pathExists(robloxPath) ? robloxPath : "";
}