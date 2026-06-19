#include "Book.h"
#include "Utils.h"
#include <iostream>

void Book::display() const {
    std::cout << "  ID: " << bookID 
              << " | Title: " << title 
              << " | Author: " << author 
              << " | Category: " << category 
              << " | Status: " << (isAvailable ? "Available" : "Issued") 
              << " | Borrowed " << borrowCount << " times\n";
}

std::string Book::toCSV() const {
    return bookID + "|" + title + "|" + author + "|" + category + "|" 
           + (isAvailable ? "1" : "0") + "|" + std::to_string(borrowCount);
}

Book Book::fromCSV(const std::string &line) {
    auto tokens = Utils::splitCSV(line);
    if (tokens.size() < 4) {
        return Book();
    }
    std::string id = tokens[0];
    std::string t = tokens[1];
    std::string a = tokens[2];
    std::string c = tokens[3];
    bool avail = true;
    if (tokens.size() > 4) {
        avail = (tokens[4] == "1");
    }
    int bc = 0;
    if (tokens.size() > 5) {
        try {
            bc = std::stoi(tokens[5]);
        } catch (...) {
            bc = 0;
        }
    }
    return Book(id, t, a, c, avail, bc);
}
