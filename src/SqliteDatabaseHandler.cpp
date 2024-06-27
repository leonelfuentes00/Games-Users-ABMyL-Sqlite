#include "SqliteDatabaseHandler.h"

SqliteDatabaseHandler::SqliteDatabaseHandler() : pDB(nullptr), stmt(nullptr), errorStatus(false) {
    iniReader = std::make_shared<IniReader>();
}

SqliteDatabaseHandler::~SqliteDatabaseHandler() {
    if (stmt) {
        sqlite3_finalize(stmt);
    }
    if (pDB) {
        sqlite3_close(pDB);
    }
}

void SqliteDatabaseHandler::setConfFile(const std::string confFilePath) {
    iniReader->open(confFilePath);
    std::string dbPath = iniReader->selectSection("SQLITE")->getValue("path");
    this->openDb(dbPath);
}

void SqliteDatabaseHandler::openDb(const std::string& dbPath) {
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

void SqliteDatabaseHandler::prepareQuery(const std::string query) {
    int iReturn = sqlite3_prepare_v2(pDB, query.c_str(), -1, &stmt, nullptr);
    if (iReturn != SQLITE_OK) {
        errorStatus = true;
        std::cerr << "Error preparing query: " << sqlite3_errmsg(pDB) << std::endl;
        throw std::runtime_error("Failed to prepare query");
    }
}

void SqliteDatabaseHandler::addParameter(int index, const std::string value) {
    int iReturn = sqlite3_bind_text(stmt, index, value.c_str(), -1, SQLITE_TRANSIENT);
    if (iReturn != SQLITE_OK) {
        errorStatus = true;
        std::cerr << "Error binding parameter: " << sqlite3_errmsg(pDB) << std::endl;
        throw std::runtime_error("Failed to bind parameter");
    }
}

void SqliteDatabaseHandler::execute() {
    int iReturn = sqlite3_step(stmt);
    if (iReturn != SQLITE_DONE && iReturn != SQLITE_ROW) {
        errorStatus = true;
        std::cerr << "Error executing statement: " << sqlite3_errmsg(pDB) << std::endl;
        throw std::runtime_error("Failed to execute statement");
    }
}

Row SqliteDatabaseHandler::fetch() {
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

Table SqliteDatabaseHandler::fetchAll() {
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

bool SqliteDatabaseHandler::getErrorStatus() const {
    return errorStatus;
}
