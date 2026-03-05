#include "JsonIdChecker.h"
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"

bool JsonIdChecker::IsIdUsed(const std::string& id) const
{
    return fileEntry.find(id) != fileEntry.end();
}

void JsonIdChecker::ProcessFile(const std::filesystem::path& fileToAdd)
{
    using json = nlohmann::json;

    std::ifstream f(fileToAdd);

    if (!f.is_open())
    {
        std::cout << "Could not open file by source: " << fileToAdd.string() << std::endl;
        return;
    }

    try
    {
        json data = json::parse(f, nullptr, false, true);

        if (!data.is_array())
        {
            return;
        }

        for (json::iterator it = data.begin(); it != data.end(); ++it)
        {
            if (!it->is_object())
            {
                continue;
            }
            for (const auto& id : idNames)
            {

                if (!it->contains(id))
                {
                    continue;
                }

                std::string idString;
                const auto& value = it->at(id);

                if (value.is_string())
                {
                    idString = value;
                }

                else if (value.is_number())
                {
                    idString = std::to_string(value.get<long long>());
                }
                else
                {
                    continue;
                }

                fileEntry[idString][fileToAdd]++;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "JSON ERROR: " << e.what() << std::endl;
    }
}

std::unordered_map<std::string, std::vector<std::filesystem::path>> JsonIdChecker::GetDuplicates() const
{
    std::unordered_map<std::string, std::vector<std::filesystem::path>> result;

    for (const auto& id : fileEntry)
    {
        const bool isMultipleFiles = id.second.size() > 1;

        for (const auto entry : id.second)
        {
            if (isMultipleFiles || entry.second > 1)
            {
                result[id.first].push_back(entry.first);
            }
        }
    }

    return result;
}
