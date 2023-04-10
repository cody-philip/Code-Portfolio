#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class AdventureFileReader{
public:
    explicit AdventureFileReader();
    static map<string, map<string, vector<vector<string>>>> ReadData(const string& filename);
};