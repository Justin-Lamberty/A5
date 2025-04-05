#include "db.h"
#include <cstdlib>
#include <stdexcept>

Database* Database::instance = nullptr;

Database::Database(const std::string& dbName, const std::string& user, const std::string& pass)
    : db(dbName), username(user), password(pass), connected(false) {
    last_activity = std::time(nullptr);
}

Database::~Database() {
    if (connected) {
        disconnect();
    }
}

// Throwing Copy Constructor
Database::Database(const Database&) {
    throw std::runtime_error("Copy constructor is disabled.");
}

// Throwing Copy Assignment
Database& Database::operator=(const Database&) {
    throw std::runtime_error("Copy assignment is disabled.");
}

// Throwing Move Constructor
Database::Database(Database&&) noexcept(false) {
    throw std::runtime_error("Move constructor is disabled.");
}

// Throwing Move Assignment
Database& Database::operator=(Database&&) noexcept(false) {
    throw std::runtime_error("Move assignment is disabled.");
}

Database* Database::getInstance(const std::string& dbName, const std::string& user, const std::string& pass) {
    if (instance == nullptr) {
        instance = new Database(dbName, user, pass);
    } else {
        if (instance->db != dbName || instance->username != user || instance->password != pass) {
            throw std::runtime_error("invalid database name, username or password");
        }
    }
    instance->refreshConnection(); // Refresh on access
    return instance;
}

void Database::connect() {
    connected = true;
    refreshConnection();
}

void Database::disconnect() {
    connected = false;
}

bool Database::isConnected() const {
    return connected;
}

bool Database::isTimeout() {
    return std::difftime(std::time(nullptr), last_activity) > TIMEOUT;
}

void Database::refreshConnection() {
    last_activity = std::time(nullptr);
}

void* Database::operator new(size_t size) {
    std::cout << "overloaded new ";
    void* ptr = std::malloc(size);
    if (!ptr) throw std::bad_alloc();
    return ptr;
}

void Database::operator delete(void* ptr) {
    std::cout << "overloaded delete ";
    std::free(ptr);
}

void Database::set_username(const std::string& user) {
    username = user;
    refreshConnection();
}

std::string Database::get_username() const {
    return username;
}

void Database::set_password(const std::string& pass) {
    password = pass;
    refreshConnection();
}

std::string Database::get_password() const {
    return password;
}

void Database::resetInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}
