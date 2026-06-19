#pragma once
#include <string>

// Forward declaration of Library since we need it in loginMember
class Library;

enum class UserRole {
    NONE,
    ADMIN,
    MEMBER
};

class Auth {
private:
    UserRole currentRole;
    std::string loggedMemberID;

public:
    static const std::string ADMIN_USERNAME;
    static const std::string ADMIN_PASSWORD;

    Auth();

    bool loginAdmin(const std::string& user, const std::string& pass);
    bool loginMember(const std::string& memberID, const std::string& contact, Library& lib);
    void logout();

    bool isAdmin() const { return currentRole == UserRole::ADMIN; }
    std::string getMemberID() const { return loggedMemberID; }
};