#pragma once

#include <vector>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

class Database {

    string db_path;

    public:
        map<string, string> db_content;

        Database(string, vector<string>&, vector<string>&);
        ~Database();

        void setUp();
        void tearDown();
        map<string, string> get_content();

};
