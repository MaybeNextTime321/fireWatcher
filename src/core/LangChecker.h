#pragma once
#include <vector>
#include <filesystem>
#include <string>
#include <unordered_map>

struct LangDuplicate
{
    LangDuplicate() {}
    std::string key;
    int firstLine;
    std::vector<int> duplicateLines;
    LangDuplicate(std::string key, int firstLine) : key(key), firstLine(firstLine) {}
    void AddLine(int line) { duplicateLines.push_back(line); }
};

class LangChecker
{
public:
    const std::unordered_map<std::string, LangDuplicate>& CheckFile(const std::filesystem::path& fileToCheck);

private:
    std::unordered_map<std::string, LangDuplicate> duplicateEntry;
};