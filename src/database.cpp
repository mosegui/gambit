#include <map>
#include <iostream>
#include "database.h"


Database::Database(string db_filepath, vector<string> &issue_titles, vector<string> &issue_descriptions)
{
    string line;
    ifstream db;

    db.open(db_filepath);

    if(db.is_open()) {

        bool _awaiting_desription = false;

        while(getline(db, line, '\n')) {

            if (line == "")
            {
                continue;
            }

            if (line.front() == '#')
            {
                line.erase(line.begin(), line.begin() + 2);
                issue_titles.push_back(line);
                _awaiting_desription = true;
            }
            else if (line == "%")
            {
                if (_awaiting_desription == true)
                {
                    issue_descriptions.push_back("");
                    _awaiting_desription = false;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                issue_descriptions.push_back(line);
                _awaiting_desription = false;
            }

        }
        // DEBUG LOG: CONTENT FROM DATABASE READ SUCCESSFULLY
//        std::cout << "Read DB contents successfully" << std::endl;
    }
    else {
//        cout << "Unable to open file" << endl;
    }

    db.close();
}


Database::~Database()
{
    map<string, string>::iterator it;
    ofstream db;

    db.open(db_path, fstream::out);

    if(db.is_open()) {

        for (auto it=db_content.begin(); it != db_content.end(); it++) {

            string key = it->first;
            string value = it->second;

            db << "# " << key << endl;
            db << value << endl;
            db << "%" << endl;
            db << endl;

        }
    }
    else {
        cout << "Unable to open file" << endl;
    }

    db.close();
}

map<string, string> Database::get_content()
{
    return db_content;
}
