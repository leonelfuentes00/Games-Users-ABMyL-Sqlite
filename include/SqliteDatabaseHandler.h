/**
* Copyright (c) 2020 Gabriel Nicolás González Ferreira. All rights reserved.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef SQLITE_DATABASE_HANDLER_H
#define SQLITE_DATABASE_HANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <sqlite3.h>
#include "DatabaseHandler.h"
#include "IniReader.h"

class SqliteDatabaseHandler : public DatabaseHandler {
private:
    sqlite3* pDB;
    sqlite3_stmt* stmt;
    bool errorStatus;
    Row row;
    Table table;
    std::string columnName;
    std::string columnValue;
    int columnCount;
    std::shared_ptr<IniReader> iniReader;

    void openDb(const std::string& dbPath) {
        errorStatus = false;
        int iReturn = sqlite3_open(dbPath.c_str(), &pDB);
        if (iReturn != SQLITE_OK) {
            errorStatus = true;
            std::cerr << "Error opening DB: " << sqlite3_errmsg(pDB) << std::endl;
            sqlite3_close(pDB);
            throw std::runtime_error("Failed to open database");
        }
        stmt = nullptr;
    }

public:
    SqliteDatabaseHandler() : pDB(nullptr), stmt(nullptr), errorStatus(false) {
        iniReader = std::make_shared<IniReader>();
    }

    ~SqliteDatabaseHandler() override {
        if (stmt) {
            sqlite3_finalize(stmt);
        }
        if (pDB) {
            sqlite3_close(pDB);
        }
    }

    void setConfFile(const std::string confFilePath) override {
        iniReader->open(confFilePath);
        std::string dbPath = iniReader->selectSection("SQLITE")->getValue("path");
        this->openDb(dbPath);
    }

    void prepareQuery(const std::string query) override {
        int iReturn = sqlite3_prepare_v2(pDB, query.c_str(), -1, &stmt, nullptr);
        if (iReturn != SQLITE_OK) {
            errorStatus = true;
            std::cerr << "Error preparing query: " << sqlite3_errmsg(pDB) << std::endl;
            throw std::runtime_error("Failed to prepare query");
        }
    }

    void addParameter(int index, const std::string value) override {
        int iReturn = sqlite3_bind_text(stmt, index, value.c_str(), -1, SQLITE_TRANSIENT);
        if (iReturn != SQLITE_OK) {
            errorStatus = true;
            std::cerr << "Error binding parameter: " << sqlite3_errmsg(pDB) << std::endl;
            throw std::runtime_error("Failed to bind parameter");
        }
    }

    void execute() override {
        int iReturn = sqlite3_step(stmt);
        if (iReturn != SQLITE_DONE && iReturn != SQLITE_ROW) {
            errorStatus = true;
            std::cerr << "Error executing statement: " << sqlite3_errmsg(pDB) << std::endl;
            throw std::runtime_error("Failed to execute statement");
        }
    }

    Row fetch() override {
        row.clear();
        int iReturn = sqlite3_step(stmt);
        if (iReturn == SQLITE_ROW) {
            columnCount = sqlite3_column_count(stmt);
            for (int i = 0; i < columnCount; ++i) {
                columnName = reinterpret_cast<const char*>(sqlite3_column_name(stmt, i));
                columnValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                row[columnName] = columnValue;
            }
        } else if (iReturn != SQLITE_DONE) {
            errorStatus = true;
            std::cerr << "Error fetching row: " << sqlite3_errmsg(pDB) << std::endl;
            throw std::runtime_error("Failed to fetch row");
        }
        return row;
    }

    Table fetchAll() override {
        table.clear();
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            row.clear();
            columnCount = sqlite3_column_count(stmt);
            for (int i = 0; i < columnCount; ++i) {
                columnName = reinterpret_cast<const char*>(sqlite3_column_name(stmt, i));
                columnValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                row[columnName] = columnValue;
            }
            table.push_back(row);
        }
        return table;
    }

    bool getErrorStatus() const {
        return errorStatus;
    }
};

#endif // SQLITE_DATABASE_HANDLER_H
