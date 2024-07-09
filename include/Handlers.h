#ifndef HANDLERS_H
#define HANDLERS_H

#include <string>
#include "SqliteDatabaseHandler.h"
using namespace std;

class Handlers {
private:
    SqliteDatabaseHandler dbHandler;

public:
    Handlers(const string& confFilePath);

    // User handling methods
    void addUser(const string& username, const string& email, int age);
    void removeUser(int userId);
    void updateUser(int userId, const string& newUsername, const string& newEmail, int newAge);
    void listUsers();

    // Game handling methods
    void addGame(const string& title, const string& genre, const string& releaseDate);
    void removeGame(int gameId);
    void updateGame(int gameId, const string& newTitle, const string& newGenre, const string& newReleaseDate);
    void listGames();

    // Association handling methods
    void associateUserWithGame(int userId, int gameId, const string& purchaseDate);
    void listAssociations();
    void findAssociationsByUser(int userId);
    void findAssociationsByGame(int gameId);
};

#endif // HANDLERS_H
