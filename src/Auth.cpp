#include "Auth.h"
#include "Library.h"
#include <iostream>

const std::string Auth::ADMIN_USERNAME = "admin";
const std::string Auth::ADMIN_PASSWORD = "library@123";

Auth::Auth() : currentRole(UserRole::NONE), loggedMemberID("") {}

bool Auth::loginAdmin(const std::string& user, const std::string& pass) {
    if (user == ADMIN_USERNAME && pass == ADMIN_PASSWORD) {
        currentRole = UserRole::ADMIN;
        return true;
    }
    return false;
}

bool Auth::loginMember(const std::string& memberID, const std::string& contact,
                       Library& lib) {
    const auto& members = lib.getMembersRef();
    for (const auto& m : members) {
        if (m.getMemberID() == memberID && m.getContact() == contact) {
            currentRole    = UserRole::MEMBER;
            loggedMemberID = memberID;
            return true;
        }
    }
    return false;
}

void Auth::logout() {
    currentRole    = UserRole::NONE;
    loggedMemberID = "";
}
