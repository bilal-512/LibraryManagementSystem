#pragma once
#include <string>
#include <vector>

class Member
{
private:
    std::string memberID;
    std::string name;
    std::string contact;
    int activeBorrowCount;
    std::vector<std::string> borrowHistory; // bookIDs

public:
    Member() : activeBorrowCount(0) {}
    Member(std::string id, std::string n, std::string c, int abc = 0)
        : memberID(id), name(n), contact(c), activeBorrowCount(abc) {}

    // Getters
    std::string getMemberID() const { return memberID; }
    std::string getName() const { return name; }
    std::string getContact() const { return contact; }
    int getActiveBorrowCount() const { return activeBorrowCount; }
    const std::vector<std::string> &getBorrowHistory() const { return borrowHistory; }

    // Setters
    void setName(const std::string &n) { name = n; }
    void setContact(const std::string &c) { contact = c; }
    void incrementBorrow() { activeBorrowCount++; }
    void decrementBorrow()
    {
        if (activeBorrowCount > 0)
            activeBorrowCount--;
    }
    void addToBorrowHistory(const std::string &bookID) { borrowHistory.push_back(bookID); }
    void setBorrowHistory(const std::vector<std::string> &hist) { borrowHistory = hist; }

    void display() const;
    std::string toCSV() const;
    static Member fromCSV(const std::string &line);
};