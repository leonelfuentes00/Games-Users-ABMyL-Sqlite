/**
* Copyright (c) 2020 Gabriel Nicolás González Ferreira. All rights reserved.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> Row; 
typedef std::vector<Row> Table; 

class DatabaseHandler {
public:
    virtual ~DatabaseHandler() = default; //Agrego un destructor virtual

    virtual void setConfFile(std::string confFilePath) = 0;
    virtual void prepareQuery(std::string query) = 0;
    virtual void addParameter(int key, std::string value) = 0;
    virtual void execute() = 0;
    virtual Row fetch() = 0;
    virtual Table fetchAll() = 0;
    virtual bool getErrorStatus() = 0;
};

#endif // DATABASE_HANDLER_H
