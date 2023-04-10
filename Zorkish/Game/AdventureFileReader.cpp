#include "HeaderFiles/Game/AdventureFileReader.h"

using namespace std;

AdventureFileReader::AdventureFileReader() = default;

map<string, map<string, vector<vector<string>>>> AdventureFileReader::ReadData(const string &filename) {
    ifstream file(filename);
    string fLine, token;
    size_t pos = 0;
    map<string, map<string, vector<vector<string>>>> result;
    vector<string> line;

    if (!file.is_open()){
        cout << "Failed to open the file" << endl;
        return result;
    }

    while (getline(file, fLine)) {
        if (reinterpret_cast<const char *>(fLine.at(0)) != reinterpret_cast<const char *>('#')) {
            token = fLine.at(0);
            pos = 0;
            while ((pos = fLine.find(':')) != string::npos) {
                line.push_back(fLine.substr(0, pos));
                fLine.erase(0, pos + 1);
            }
            line.erase(line.begin());
            result[token][line[0]].push_back(line);
            line.clear();
        }
    }

    return result;



    //return std::map<std::string, std::map<std::string, std::vector<std::string>>>();
}
