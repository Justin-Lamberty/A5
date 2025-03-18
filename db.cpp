#include "db.h"
#include <cstdlib> // for malloc and free

Database* Database::instance = nullptr;

Database::Database(const std::string& dbName, const std::string& user, const std::string& pass)
    : db(dbName), username(user), password(pass), connected(false) {}

Database::~Database() {
    if (connected) {
        disconnect();
    }
}

Database* Database::getInstance(const std::string& dbName, const std::string& user, const std::string& pass) {
    if (instance == nullptr) {
        instance = new Database(dbName, user, pass);
    } else {
        if (instance->db != dbName || instance->username != user || instance->password != pass) {
            throw std::runtime_error("invalid database name, username or password");
        }
    }
    return instance;
}

void Database::connect() {
    connected = true;
}

void Database::disconnect() {
    connected = false;
}

bool Database::isConnected() const {
    return connected;
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
}

std::string Database::get_username() const {
    return username;
}

void Database::set_password(const std::string& pass) {
    password = pass;
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
