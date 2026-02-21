#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "core/FileScanner.h"

int main()
{
    const std::filesystem::path filePath = std::filesystem::relative("G:\\stalcraftassets");

    FileScanner scanner = FileScanner(filePath);


    std::vector<FileEntry> loadedFiles = scanner.ScanPath();


    for (const auto file : loadedFiles)
    {
        std::cout << "FileName: " << file.filename() << "  File Path: " << file.path.string() << std::endl;
    }





}