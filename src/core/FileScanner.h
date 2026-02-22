
#include <string>
#include <filesystem>
#include <vector>

struct FileEntry
{
    FileEntry(const std::filesystem::path path) : path(path) {}
    std::filesystem::path path;
    std::string filename() const { return path.filename().string(); };
};

class FileScanner
{

public:
    FileScanner(const std::filesystem::path pathToFile);
    std::vector<FileEntry> ScanPath() const;

    void ChangeBlockedDirs(const std::vector<std::string>& newBlockedDirs);
    void ResetBlockedDirs();
    void ChangeBlockedFormats(const std::vector<std::string>& newBlockedFormats);
    void ResetBlockedFormats();

private:
    const std::filesystem::path pathToFile;
    std::vector<std::string> blockedDirs;
    std::vector<std::string> blockedFormats;
    bool IsPathBlocked(const std::string& pathToCheck) const;
    bool IsFormatBlocked(const std::filesystem::path& path) const;
};