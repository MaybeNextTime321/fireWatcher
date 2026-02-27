#include <unordered_map>
#include <filesystem>
#include <vector>

class JsonIdChecker
{

public:
    bool IsIdUsed(const std::string& id) const;
    void ProcessFile(const std::filesystem::path& fileToAdd);
    std::unordered_map<std::string, std::vector<std::filesystem::path>> GetDuplicates() const;

private:
    std::unordered_map<std::string, std::vector<std::filesystem::path>> fileEntry;
    const std::vector<std::string> idNames{"item_id", "id", "object_id"};
};