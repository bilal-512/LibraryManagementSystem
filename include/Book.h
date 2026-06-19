#pragma once
#include <string>

class Book
{
private:
    std::string bookID;
    std::string title;
    std::string author;
    std::string category;
    bool isAvailable;
    int borrowCount;

public:
    Book() : isAvailable(true), borrowCount(0) {}
    Book(std::string id, std::string t, std::string a, std::string c,
         bool avail = true, int bc = 0)
        : bookID(id), title(t), author(a), category(c),
          isAvailable(avail), borrowCount(bc) {}

    // Getters
    std::string getBookID() const { return bookID; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getCategory() const { return category; }
    bool getAvailability() const { return isAvailable; }
    int getBorrowCount() const { return borrowCount; }

    // Setters
    void setTitle(const std::string &t) { title = t; }
    void setAuthor(const std::string &a) { author = a; }
    void setCategory(const std::string &c) { category = c; }
    void setAvailability(bool a) { isAvailable = a; }
    void incrementBorrowCount() { borrowCount++; }

    void display() const;
    std::string toCSV() const;
    static Book fromCSV(const std::string &line);
};