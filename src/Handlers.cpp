#include "Handlers.h"
using namespace std;

/** @brief Constructs a Handlers object and sets the configuration file. */
Handlers::Handlers(const string& confFilePath) {
    dbHandler.setConfFile(confFilePath);
}

// User handling methods

/** @brief Adds a user to the database. */
void Handlers::addUser(const string& username, const string& email, int age) {
    dbHandler.prepareQuery("INSERT INTO Users (username, email, age) VALUES (?, ?, ?);");
    dbHandler.addParameter(1, username);
    dbHandler.addParameter(2, email);
    dbHandler.addParameter(3, to_string(age));
    dbHandler.execute();
}

/** @brief Removes a user from the database by ID. */
void Handlers::removeUser(int userId) {
    dbHandler.prepareQuery("DELETE FROM Users WHERE id = ?;");
    dbHandler.addParameter(1, to_string(userId));
    dbHandler.execute();
}

/** @brief Updates a user's details in the database by ID. */
void Handlers::updateUser(int userId, const string& newUsername, const string& newEmail, int newAge) {
    dbHandler.prepareQuery("UPDATE Users SET username = ?, email = ?, age = ? WHERE id = ?;");
    dbHandler.addParameter(1, newUsername);
    dbHandler.addParameter(2, newEmail);
    dbHandler.addParameter(3, to_string(newAge));
    dbHandler.addParameter(4, to_string(userId));
    dbHandler.execute();
}

/** @brief Lists all users in the database. */
void Handlers::listUsers() {
    dbHandler.prepareQuery("SELECT * FROM Users;");
    auto users = dbHandler.fetchAll();
    for (const auto& user : users) {
        cout << "ID: " << user.at("id") << ", Username: " << user.at("username") << ", Email: " << user.at("email") << ", Age: " << user.at("age") << endl;
    }
}

// Game handling methods

/** @brief Adds a game to the database. */
void Handlers::addGame(const string& title, const string& genre, const string& releaseDate) {
    dbHandler.prepareQuery("INSERT INTO Games (title, genre, release_date) VALUES (?, ?, ?);");
    dbHandler.addParameter(1, title);
    dbHandler.addParameter(2, genre);
    dbHandler.addParameter(3, releaseDate);
    dbHandler.execute();
}

/** @brief Removes a game from the database by ID. */
void Handlers::removeGame(int gameId) {
    dbHandler.prepareQuery("DELETE FROM Games WHERE id = ?;");
    dbHandler.addParameter(1, to_string(gameId));
    dbHandler.execute();
}

/** @brief Updates a game's details in the database by ID. */
void Handlers::updateGame(int gameId, const string& newTitle, const string& newGenre, const string& newReleaseDate) {
    dbHandler.prepareQuery("UPDATE Games SET title = ?, genre = ?, release_date = ? WHERE id = ?;");
    dbHandler.addParameter(1, newTitle);
    dbHandler.addParameter(2, newGenre);
    dbHandler.addParameter(3, newReleaseDate);
    dbHandler.addParameter(4, to_string(gameId));
    dbHandler.execute();
}

/** @brief Lists all games in the database. */
void Handlers::listGames() {
    dbHandler.prepareQuery("SELECT * FROM Games;");
    auto games = dbHandler.fetchAll();
    for (const auto& game : games) {
        cout << "ID: " << game.at("id") << ", Title: " << game.at("title") << ", Genre: " << game.at("genre") << ", Release Date: " << game.at("release_date") << endl;
    }
}

// Association handling methods

/** @brief Associates a user with a game in the database. */
void Handlers::associateUserWithGame(int userId, int gameId, const string& purchaseDate) {
    dbHandler.prepareQuery("INSERT INTO Users_Games (user_id, game_id, purchase_date) VALUES (?, ?, ?);");
    dbHandler.addParameter(1, to_string(userId));
    dbHandler.addParameter(2, to_string(gameId));
    dbHandler.addParameter(3, purchaseDate);
    dbHandler.execute();
}

/** @brief Lists all associations between users and games in the database. */
void Handlers::listAssociations() {
    dbHandler.prepareQuery("SELECT * FROM Users_Games;");
    auto associations = dbHandler.fetchAll();
    for (const auto& assoc : associations) {
        cout << "User ID: " << assoc.at("user_id") << ", Game ID: " << assoc.at("game_id") << ", Purchase Date: " << assoc.at("purchase_date") << endl;
    }
}

/** @brief Finds associations by user ID. */
void Handlers::findAssociationsByUser(int userId) {
    dbHandler.prepareQuery("SELECT * FROM Users_Games WHERE user_id = ?;");
    dbHandler.addParameter(1, to_string(userId));
    auto associations = dbHandler.fetchAll();
    for (const auto& assoc : associations) {
        cout << "User ID: " << assoc.at("user_id") << ", Game ID: " << assoc.at("game_id") << ", Purchase Date: " << assoc.at("purchase_date") << endl;
    }
}

/** @brief Finds associations by game ID. */
void Handlers::findAssociationsByGame(int gameId) {
    dbHandler.prepareQuery("SELECT * FROM Users_Games WHERE game_id = ?;");
    dbHandler.addParameter(1, to_string(gameId));
    auto associations = dbHandler.fetchAll();
    for (const auto& assoc : associations) {
        cout << "User ID: " << assoc.at("user_id") << ", Game ID: " << assoc.at("game_id") << ", Purchase Date: " << assoc.at("purchase_date") << endl;
    }
}
