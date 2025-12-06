#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include <string>
#include <map>

class AuthSystem {
private:
    std::map<std::string, std::string> users;
    
public:
    AuthSystem();
    bool authenticateOwner(const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);
    void saveUsersToFile(const std::string& filename);
    void loadUsersFromFile(const std::string& filename);
    
private:
    std::string hashPassword(const std::string& password);
};

#endif