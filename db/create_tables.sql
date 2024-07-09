CREATE TABLE IF NOT EXISTS Users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    email TEXT NOT NULL UNIQUE,
    age INTEGER
);

CREATE TABLE IF NOT EXISTS Games (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL UNIQUE,
    genre TEXT,
    release_date TEXT
);

CREATE TABLE IF NOT EXISTS Users_Games (
    user_id INTEGER NOT NULL,
    game_id INTEGER NOT NULL,
    purchase_date TEXT NOT NULL,
    PRIMARY KEY (user_id, game_id),
    FOREIGN KEY (user_id) REFERENCES Users(id),
    FOREIGN KEY (game_id) REFERENCES Games(id)
);
