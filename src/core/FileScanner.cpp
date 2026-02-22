#include "FileScanner.h"
#include <iostream>

FileScanner::FileScanner(const std::filesystem::path pathToFile) : pathToFile(pathToFile)
{
    ResetBlockedDirs();
    ResetBlockedFormats();
}

std::vector<FileEntry> FileScanner::ScanPath() const
{
    std::vector<FileEntry> result;

    if (std::filesystem::exists(pathToFile))
    {
        for (auto it = std::filesystem::recursive_directory_iterator(pathToFile); it != std::filesystem::recursive_directory_iterator();
            ++it)
        {

            std::string pathString = it->path().filename().string();

            if (IsPathBlocked(pathString) && it->is_directory())
            {
                it.disable_recursion_pending();
                continue;
            }

            if (IsFormatBlocked(it->path()) || it->is_directory())
            {
                continue;
            }

            result.push_back(FileEntry(it->path()));
        }

        return result;
    }
    else
    {
        std::cout << "Directory does not exist" << std::endl << std::filesystem::absolute(pathToFile) << std::endl;
        return result;
    }
}

void FileScanner::ChangeBlockedDirs(const std::vector<std::string>& newBlockedDirs)
{
    blockedDirs = newBlockedDirs;
}

void FileScanner::ResetBlockedDirs()
{
    blockedDirs = {".git", ".gradle", ".gitattributes", ".gitignore", ".idea", "configurations", "FmodProject", "_localized", "sound",
        "icons", "textures", "maprend_overlays", "mcpatcher", "src", "models", "customnpcs", "highpoly", "behaviour", "weather",
        "ctmpatcher", "map_overlay", "gloomycore", "music", "aabb", "fonts", "stalkersounds", "stream", "figma_gui", "global_map", "video",
        "figma", "streamrandom", "shop", "stalkerguide", "prepare-commit-msg", "enable_all_feature_flags", "stalkermobs", "Texture"};
}

void FileScanner::ChangeBlockedFormats(const std::vector<std::string>& newBlockedFormats)
{
    blockedFormats = newBlockedFormats;
}

void FileScanner::ResetBlockedFormats()
{
    blockedFormats = {".srt", ".efkefc", ".smm", ".txt", ".kts", ".ini", ".efkmat", ".efkmodel", ".dds"};
}

bool FileScanner::IsPathBlocked(const std::string& pathToCheck) const
{
    bool result = false;
    for (const auto& blockedPath : blockedDirs)
    {
        if (pathToCheck == blockedPath)
        {
            result = true;
            break;
        }
    }
    return result;
}

bool FileScanner::IsFormatBlocked(const std::filesystem::path& path) const
{
    bool result = false;
    std::string fileType = path.extension().string();
    for (const auto blockedType : blockedFormats)
    {
        if (fileType == blockedType)
        {
            result = true;
            break;
        }
    }

    return result;
}
