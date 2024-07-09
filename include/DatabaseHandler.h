/**
 * @file DatabaseHandler.h
 * @brief Abstract base class for database handling.
 */

#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> Row;
typedef std::vector<Row> Table;

/** @brief Abstract base class for handling database operations. */
class DatabaseHandler {
public:
    virtual ~DatabaseHandler() = default; /**< Virtual destructor. */
    virtual void setConfFile(const std::string& confFilePath) = 0; /**< Sets the configuration file for the database connection. */
    virtual void prepareQuery(const std::string& query) = 0; /**< Prepares an SQL query for execution. */
    virtual void addParameter(int key, const std::string& value) = 0; /**< Adds a parameter to the prepared SQL query. */
    virtual void execute() = 0; /**< Executes the prepared SQL query. */
    virtual Row fetch() = 0; /**< Fetches the next row from the result set. */
    virtual Table fetchAll() = 0; /**< Fetches all rows from the result set. */
    virtual bool getErrorStatus() = 0; /**< Gets the error status of the last operation. */
};

#endif // DATABASE_HANDLER_H
