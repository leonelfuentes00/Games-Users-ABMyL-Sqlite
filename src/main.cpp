#include <iostream>
#include <memory>
#include <fstream>
#include "SqliteDatabaseHandler.h"
#include "Handlers.h"

using namespace std;

/** @brief Initializes the database with the provided schema. */
void initializeDatabase(shared_ptr<DatabaseHandler> dbHandler) {
    ifstream schemaFile("../db/create_tables.sql");
    if (!schemaFile.is_open()) {
        cerr << "Error: Could not open schema file." << endl;
        return;
    }
    string schema((istreambuf_iterator<char>(schemaFile)), istreambuf_iterator<char>());
    dbHandler->prepareQuery(schema);
    dbHandler->execute();
}

/** @brief Displays the main menu options. */
void displayMenu() {
    cout << "1. Add User" << endl;
    cout << "2. Remove User" << endl;
    cout << "3. Update User" << endl;
    cout << "4. List Users" << endl;
    cout << "5. Add Game" << endl;
    cout << "6. Remove Game" << endl;
    cout << "7. Update Game" << endl;
    cout << "8. List Games" << endl;
    cout << "9. Associate User with Game" << endl;
    cout << "10. List Associations" << endl;
    cout << "11. Find Associations by User" << endl;
    cout << "12. Find Associations by Game" << endl;
    cout << "13. Exit" << endl;
}

/** @brief Main function to demonstrate database operations. */
int main() {
    auto dbHandler = make_shared<SqliteDatabaseHandler>();
    dbHandler->setConfFile("configuration.ini");
    initializeDatabase(dbHandler);

    Handlers handlers("configuration.ini");

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string username, email;
                int age;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter age: ";
                cin >> age;
                handlers.addUser(username, email, age);
                break;
            }
            case 2: {
                int userId;
                cout << "Enter user ID to remove: ";
                cin >> userId;
                handlers.removeUser(userId);
                break;
            }
            case 3: {
                int userId, newAge;
                string newUsername, newEmail;
                cout << "Enter user ID to update: ";
                cin >> userId;
                cout << "Enter new username: ";
                cin >> newUsername;
                cout << "Enter new email: ";
                cin >> newEmail;
                cout << "Enter new age: ";
                cin >> newAge;
                handlers.updateUser(userId, newUsername, newEmail, newAge);
                break;
            }
            case 4:
                handlers.listUsers();
                break;
            case 5: {
                string title, genre, releaseDate;
                cout << "Enter game title: ";
                cin >> title;
                cout << "Enter game genre: ";
                cin >> genre;
                cout << "Enter release date (YYYY-MM-DD): ";
                cin >> releaseDate;
                handlers.addGame(title, genre, releaseDate);
                break;
            }
            case 6: {
                int gameId;
                cout << "Enter game ID to remove: ";
                cin >> gameId;
                handlers.removeGame(gameId);
                break;
            }
            case 7: {
                int gameId;
                string newTitle, newGenre, newReleaseDate;
                cout << "Enter game ID to update: ";
                cin >> gameId;
                cout << "Enter new title: ";
                cin >> newTitle;
                cout << "Enter new genre: ";
                cin >> newGenre;
                cout << "Enter new release date (YYYY-MM-DD): ";
                cin >> newReleaseDate;
                handlers.updateGame(gameId, newTitle, newGenre, newReleaseDate);
                break;
            }
            case 8:
                handlers.listGames();
                break;
            case 9: {
                int userId, gameId;
                string purchaseDate;
                cout << "Enter user ID: ";
                cin >> userId;
                cout << "Enter game ID: ";
                cin >> gameId;
                cout << "Enter purchase date (YYYY-MM-DD): ";
                cin >> purchaseDate;
                handlers.associateUserWithGame(userId, gameId, purchaseDate);
                break;
            }
            case 10:
                handlers.listAssociations();
                break;
            case 11: {
                int userId;
                cout << "Enter user ID: ";
                cin >> userId;
                handlers.findAssociationsByUser(userId);
                break;
            }
            case 12: {
                int gameId;
                cout << "Enter game ID: ";
                cin >> gameId;
                handlers.findAssociationsByGame(gameId);
                break;
            }
            case 13:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 13);

    return 0;
}
