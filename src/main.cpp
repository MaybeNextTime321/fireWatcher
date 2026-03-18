#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "core/FileScanner.h"
#include "core/JsonIdChecker.h"
#include "core/LangChecker.h"
#include "ReportGenerator.h"
#include "nlohmann/json.hpp"

int main()
{
    const std::filesystem::path filePath = std::filesystem::relative("G:\\stalcraftassets");
    FileScanner scanner = FileScanner(filePath);
    LangChecker langChecker = LangChecker();
    JsonIdChecker idChecker = JsonIdChecker();
    ReportGenerator reportGenerator = ReportGenerator();

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
            reportGenerator.AddToReport(duplicateEntry);
        }
    }

    std::unordered_map<std::string, std::vector<std::filesystem::path>> idCheckerResult = idChecker.GetDuplicates();
    reportGenerator.AddToReport(idCheckerResult);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Lang Scanning Time: " << elapsed.count() << " sec\n";
}