#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "core/FileScanner.h"
#include "core/LangChecker.h"

int main()
{
    const std::filesystem::path filePath = std::filesystem::relative("G:\\stalcraftassets");

    FileScanner scanner = FileScanner(filePath);
    LangChecker langChecker = LangChecker();

    std::vector<FileEntry> loadedFiles = scanner.ScanPath();

    for (const auto file : loadedFiles)
    {
        if (file.path.extension().string() == ".lang")
        {
            std::cout << "FileName: " << file.filename() << "  File Path: " << file.path.string() << std::endl;

            std::unordered_map<std::string, LangDuplicate> duplicateEntry = langChecker.CheckFile(file.path);

            for (const auto item : duplicateEntry)
            {
                if (item.second.duplicateLines.size() > 0)
                {
                    std::cout << "Found dublicated ID: " << item.first << " in lines: " << std::endl;
                    for (const auto line : item.second.duplicateLines)
                    {
                        std::cout << "\t" << line << std::endl;
                    }
                }
            }
        }
    }
}