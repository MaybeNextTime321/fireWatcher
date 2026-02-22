#include "LangChecker.h"

#include <iostream>
#include <fstream>

const std::unordered_map<std::string, LangDuplicate>& LangChecker::CheckFile(const std::filesystem::path& fileToCheck)
{
    duplicateEntry.clear();
    duplicateEntry.reserve(25000);

    std::string line;

    std::ifstream in(fileToCheck.string());
    in.imbue(std::locale::classic());

    int i = 0;

    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            ++i;
            if (line.empty()) continue;

            size_t splitterPos = line.find("=");

            if (splitterPos == std::string::npos)
            {
                std::cout << "ERROR IN LINE: " << i << std::endl;
                std::cout << "CAN'T FIND SPLITTER" << std::endl;
                std::cout << "LINE CONTENT: " << line << std::endl;

                continue;
            }

            try
            {
                std::string key = line.substr(0, splitterPos);

                if (duplicateEntry.find(key) == duplicateEntry.end())
                {
                    duplicateEntry[key] = LangDuplicate(key, i);
                }
                else
                {
                    duplicateEntry[key].AddLine(i);
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "ERROR IN LINE: " << i << std::endl;
                std::cout << "LINE CONTENT: " << line << std::endl;
                std::cout << "ERROR VALUE: " << e.what() << std::endl;
            }
        }
    }
    in.close();

    return duplicateEntry;
}
