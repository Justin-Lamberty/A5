#ifndef DB_H
#define DB_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <ctime>

class Database {
private:
    std::string db;
    std::string username;
    std::string password;
    bool connected = false;

    static Database* instance;

    time_t last_activity;
    static const int TIMEOUT{5};

    // Private constructor & destructor
    Database(const std::string& dbName, const std::string& user, const std::string& pass);
    

public:
    // Copy/Move operations throw runtime_error
    Database(const Database&);
    Database& operator=(const Database&);
    Database(Database&&) noexcept(false);
    Database& operator=(Database&&) noexcept(false);
    ~Database();
    static Database* getInstance(const std::string& dbName, const std::string& user, const std::string& pass);

    void connect();
    void disconnect();
    bool isConnected() const;

    // Timeout functionality
    bool isTimeout();
    void refreshConnection();

    // Overload new and delete
    void* operator new(size_t size);
    void operator delete(void* ptr);

    // Setters and Getters
    void set_username(const std::string& user);
    std::string get_username() const;

    void set_password(const std::string& pass);
    std::string get_password() const;

    static void resetInstance();
};

#endif // DB_H
