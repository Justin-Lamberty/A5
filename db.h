#ifndef DB_H
#define DB_H

#include <string>
#include <stdexcept>
#include <iostream>

class Database {
private:
    std::string db;
    std::string username;
    std::string password;
    bool connected = false;

    static Database* instance;

    // Private constructor
    Database(const std::string& dbName, const std::string& user, const std::string& pass);

    // Private destructor
    ~Database();

public:
    // Delete copy constructor and assignment to prevent copying
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database* getInstance(const std::string& dbName, const std::string& user, const std::string& pass);

    void connect();
    void disconnect();
    bool isConnected() const;

    // Overload new and delete
    void* operator new(size_t size);
    void operator delete(void* ptr);

    // Setters and Getters
    void set_username(const std::string& user);
    std::string get_username() const;

    void set_password(const std::string& pass);
    std::string get_password() const;

    // Reset the instance
    static void resetInstance();
};

#endif // DB_H

