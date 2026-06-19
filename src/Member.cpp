#include "Member.h"
#include "Utils.h"
#include <iostream>
#include <sstream>

void Member::display() const {
    std::cout << "  Member ID: " << memberID 
              << " | Name: " << name 
              << " | Contact: " << contact 
              << " | Active Borrows: " << activeBorrowCount << "\n";
    if (!borrowHistory.empty()) {
        std::cout << "    Borrow History (Book IDs): ";
        for (size_t i = 0; i < borrowHistory.size(); ++i) {
            std::cout << borrowHistory[i];
            if (i < borrowHistory.size() - 1) std::cout << ", ";
        }
        std::cout << "\n";
    }
}

std::string Member::toCSV() const {
    std::string histStr = "";
    for (size_t i = 0; i < borrowHistory.size(); ++i) {
        histStr += borrowHistory[i];
        if (i < borrowHistory.size() - 1) histStr += ",";
    }
    return memberID + "|" + name + "|" + contact + "|" 
           + std::to_string(activeBorrowCount) + "|" + histStr;
}

Member Member::fromCSV(const std::string &line) {
    auto tokens = Utils::splitCSV(line);
    if (tokens.size() < 3) {
        return Member();
    }
    std::string id = tokens[0];
    std::string n = tokens[1];
    std::string c = tokens[2];
    int abc = 0;
    if (tokens.size() > 3) {
        try {
            abc = std::stoi(tokens[3]);
        } catch (...) {
            abc = 0;
        }
    }
    Member m(id, n, c, abc);
    if (tokens.size() > 4 && !tokens[4].empty()) {
        std::stringstream ss(tokens[4]);
        std::string bid;
        std::vector<std::string> hist;
        while (std::getline(ss, bid, ',')) {
            bid = Utils::trim(bid);
            if (!bid.empty()) {
                hist.push_back(bid);
            }
        }
        m.setBorrowHistory(hist);
    }
    return m;
}
