#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "core/FileScanner.h"
#include "core/JsonIdChecker.h"
#include "core/LangChecker.h"
#include "nlohmann/json.hpp"

int main()
{
    const std::filesystem::path filePath = std::filesystem::relative("G:\\stalcraftassets");
    FileScanner scanner = FileScanner(filePath);
    LangChecker langChecker = LangChecker();
    JsonIdChecker idChecker = JsonIdChecker();

    std::vector<FileEntry> loadedFiles = scanner.ScanPath();
    auto start = std::chrono::steady_clock::now();

    for (const auto file : loadedFiles)
    {
        if (file.path.extension().string() == ".json")
        {
            idChecker.ProcessFile(file.path);
        }

        if (file.path.extension().string() == ".lang")
        {
            std::unordered_map<std::string, LangDuplicate> duplicateEntry = langChecker.CheckFile(file.path);
        }
    }

    std::unordered_map<std::string, std::vector<std::filesystem::path>> idCheckerResult = idChecker.GetDuplicates();
    for (const auto dublicate : idCheckerResult)
    {
        std::cout << "ID DUBLICATE:" << dublicate.first << std::endl;

        for (const auto path : dublicate.second)
        {
            std::cout << "PATH:" << path.string() << std::endl;
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Lang Scanning Time: " << elapsed.count() << " sec\n";
}