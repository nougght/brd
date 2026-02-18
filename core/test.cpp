#include <sqlite3.h>
#include "string"
#include <iostream>
#include <thread>

int main()
{
    sqlite3 * db;
    sqlite3_open("test.db", &db);
    std::string query = "CREATE TABLE IF NOT EXISTS history ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "url TEXT NOT NULL,"
        "title TEXT,"
        "visit_time INTEGER);";

    if(sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr) == 0)
    {
        std::cout << "ok" << std::endl;
    }
    if(sqlite3_exec(db, "INSERT INTO history(url, title) VALUES ('google.com', 'google');", nullptr, nullptr, nullptr) == 0)
    {
        std::cout << "ok" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "end";
    sqlite3_close(db);

}