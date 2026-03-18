#include <string>
#include <unordered_map>
#include <core/LangChecker.h>
#include <fstream>

#pragma once

class ReportGenerator
{
public:
    ReportGenerator();
    ReportGenerator(std::string outputPath);
    ReportGenerator::~ReportGenerator();

    void AddToReport(std::unordered_map<std::string, LangDuplicate>& langDuplicate);
    void AddToReport(std::unordered_map<std::string, std::vector<std::filesystem::path>>& idCheckerResult);

private:
    std::string outputPath = "report.txt";
    void ClearReport();
    std::ofstream log;
};