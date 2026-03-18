#include "ReportGenerator.h"
#include "core/LangChecker.h"
#include <iostream>
#include <chrono>

ReportGenerator::ReportGenerator()
{
    ClearReport();
    log = std::ofstream(outputPath, std::ios_base::app | std::ios_base::out);

    if (!log.is_open())
    {
        std::cout << "Cannot open file: " << outputPath << std::endl;
    }
}

ReportGenerator::ReportGenerator(std::string outputPath) : outputPath(outputPath)
{
    ClearReport();
    log = std::ofstream(outputPath, std::ios_base::app | std::ios_base::out);

    if (!log.is_open())
    {
        std::cout << "Cannot open file: " << outputPath << std::endl;
    }
}

void ReportGenerator::AddToReport(std::unordered_map<std::string, LangDuplicate>& langDuplicate)
{
    for (const auto& item : langDuplicate)
    {
        if (item.second.duplicateLines.empty())
        {
            continue;
        }

        log << "Lang Duplicated ID: " << item.first << std::endl;
        log << "\tUsed line: " << item.second.firstLine << std::endl;

        for (const auto& usedLine : item.second.duplicateLines)
        {
            log << "\tUsed line: " << usedLine << std::endl;
        }
    }
}

void ReportGenerator::AddToReport(std::unordered_map<std::string, std::vector<std::filesystem::path>>& idCheckerResult)
{
    for (const auto& idCheckerResultEntry : idCheckerResult)
    {
        log << "Duplicated ID: " << idCheckerResultEntry.first << std::endl;
        for (const auto& path : idCheckerResultEntry.second)
        {
            log << "\tUsed in path:\t" << path.string() << std::endl;
        }
    }
}

void ReportGenerator::ClearReport()
{
    try
    {
        std::remove(outputPath.c_str());
    }
    catch (const std::exception& e)
    {
        std::cout << "Exeption during delete old report: " << e.what() << std::endl;
    }
}

ReportGenerator::~ReportGenerator()
{
    if (log.is_open())
    {
        log.flush();
        log.close();
    }
}