#include "HeaderFiles/Game/UtilityFunctions.h"

std::string UtilityFunctions::ToLower(const std::string& str) {
    std::string result;
    for (auto c : str) {
        result += tolower(c);
    }
    return result;
}

std::string UtilityFunctions::TrimExtension(const std::string &str) {
    std::string result = str;
    result.erase(0,13);
    for (int i = 0; i < 4; ++i) {
        result.pop_back();
    }
    return result;
}

std::string UtilityFunctions::Capitalise(const std::string &str) {
    std::vector<std::string> breakdown = Split(str);
    std::string result;
    for (auto s: breakdown) {
        s[0] = toupper(s[0]);
        result += s + " ";
    }
    result.pop_back();
    return result;
}

std::vector<std::string> UtilityFunctions::Split(const std::string& cmd) {
    size_t pos = 0;
    std::vector<std::string> breakdown;
    std::string copy = ToLower(cmd);
    while ((pos = copy.find(' ')) != std::string::npos){
        breakdown.push_back(copy.substr(0,pos));
        copy.erase(0, pos+1);
    }
    breakdown.push_back(copy);
    return breakdown;
}