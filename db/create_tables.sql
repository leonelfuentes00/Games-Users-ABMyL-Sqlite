-- Creación de la tabla Users
CREATE TABLE IF NOT EXISTS Users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    email TEXT NOT NULL UNIQUE,
    age INTEGER
);

-- Creación de la tabla Games
CREATE TABLE IF NOT EXISTS Games (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL UNIQUE,
    genre TEXT,
    release_date TEXT
);

-- Creación de la tabla Users_Games para la relación muchos a muchos
CREATE TABLE IF NOT EXISTS Users_Games (
    user_id INTEGER NOT NULL,
    game_id INTEGER NOT NULL,
    purchase_date TEXT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Users(id),
    FOREIGN KEY (game_id) REFERENCES Games(id),
    PRIMARY KEY (user_id, game_id)
);
