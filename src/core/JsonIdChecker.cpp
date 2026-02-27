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

    std::ifstream f(std::filesystem::absolute(fileToAdd));

    if (f.is_open())
    {
        try
        {
            json data = json::parse(f, nullptr, false, true);

            if (data.is_array())
            {

                for (json::iterator it = data.begin(); it != data.end(); ++it)
                {
                    if (it->is_object())
                    {
                        for (const auto id : idNames)
                        {

                            if (it->contains(id))
                            {
                                std::string idString;

                                if (it->at(id).is_string())
                                {
                                    idString = it->at(id);
                                }
                                else if (it->at(id).is_number())
                                {
                                    idString = std::to_string((int)it->at(id));
                                }
                                else
                                {
                                    continue;
                                }

                                fileEntry[idString].push_back(fileToAdd);
                            }
                        }
                    }
                }
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "JSON ERROR: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Could not open file by sourse: " << fileToAdd.string() << std::endl;
    }
}

std::unordered_map<std::string, std::vector<std::filesystem::path>> JsonIdChecker::GetDuplicates() const
{
    std::unordered_map<std::string, std::vector<std::filesystem::path>> result;

    for (const auto& entry : fileEntry)
    {
        if (entry.second.size() > 1)
        {
            result.emplace(entry);
        }
    }

    return result;
}
