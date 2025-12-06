#include "AuthSystem.h"
#include <fstream>
#include <sstream>
#include <iostream>

AuthSystem::AuthSystem() {
    // Default owner password
    users["admin"] = hashPassword("owner123");
}

std::string AuthSystem::hashPassword(const std::string& password) {
    // Simple hash untuk testing
    std::string hashed = "";
    for (char c : password) {
        hashed += std::to_string((int)c + 10);
    }
    return hashed;
}

bool AuthSystem::authenticateOwner(const std::string& password) {
    auto it = users.find("admin");
    if (it != users.end()) {
        return it->second == hashPassword(password);
    }
    return false;
}

bool AuthSystem::authenticateUser(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second == hashPassword(password);
    }
    return false;
}

bool AuthSystem::registerUser(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end()) {
        return false;
    }
    users[username] = hashPassword(password);
    return true;
}

void AuthSystem::saveUsersToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : users) {
            file << pair.first << ";" << pair.second << std::endl;
        }
        file.close();
    }
}

void AuthSystem::loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string username, password;
            if (std::getline(ss, username, ';') && std::getline(ss, password)) {
                users[username] = password;
            }
        }
        file.close();
    }
}