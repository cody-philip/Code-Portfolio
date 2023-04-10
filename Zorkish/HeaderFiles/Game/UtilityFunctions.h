#ifndef ZORKISH_UTILITYFUNCTIONS_H
#define ZORKISH_UTILITYFUNCTIONS_H


#include <string>
#include <vector>

class UtilityFunctions {

public:
    static std::string ToLower(const std::string& str);
    static std::string TrimExtension(const std::string& str);
    static std::string Capitalise(const std::string& str);

    static std::vector<std::string> Split(const std::string& cmd);
};


#endif //ZORKISH_UTILITYFUNCTIONS_H
