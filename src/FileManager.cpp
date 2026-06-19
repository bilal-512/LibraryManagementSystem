#include "FileManager.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

FileManager::FileManager(const std::string &dataDir) {
    if (!dataDir.empty() && !fs::exists(dataDir)) {
        fs::create_directories(dataDir);
    }
    booksFile = dataDir + "books.csv";
    membersFile = dataDir + "members.csv";
    transactionsFile = dataDir + "transactions.csv";
    
    ensureFileExists(booksFile, "bookID|title|author|category|isAvailable|borrowCount");
    ensureFileExists(membersFile, "memberID|name|contact|activeBorrowCount|borrowHistory");
    ensureFileExists(transactionsFile, "transactionID|bookID|memberID|bookTitle|memberName|issueDate|returnDate|returned|fineAmount");
}

void FileManager::ensureFileExists(const std::string &filepath, const std::string &header) const {
    if (!fs::exists(filepath)) {
        std::ofstream f(filepath);
        if (f.is_open()) {
            f << header << "\n";
        }
    }
}

std::vector<Book> FileManager::loadBooks() const {
    std::vector<Book> list;
    std::ifstream f(booksFile);
    if (!f.is_open()) return list;
    
    std::string line;
    std::getline(f, line); // header
    while (std::getline(f, line)) {
        if (!line.empty()) {
            list.push_back(Book::fromCSV(line));
        }
    }
    return list;
}

void FileManager::saveBooks(const std::vector<Book> &books) const {
    std::ofstream f(booksFile);
    if (!f.is_open()) return;
    
    f << "bookID|title|author|category|isAvailable|borrowCount\n";
    for (const auto &b : books) {
        f << b.toCSV() << "\n";
    }
}

std::vector<Member> FileManager::loadMembers() const {
    std::vector<Member> list;
    std::ifstream f(membersFile);
    if (!f.is_open()) return list;
    
    std::string line;
    std::getline(f, line); // header
    while (std::getline(f, line)) {
        if (!line.empty()) {
            list.push_back(Member::fromCSV(line));
        }
    }
    return list;
}

void FileManager::saveMembers(const std::vector<Member> &members) const {
    std::ofstream f(membersFile);
    if (!f.is_open()) return;
    
    f << "memberID|name|contact|activeBorrowCount|borrowHistory\n";
    for (const auto &m : members) {
        f << m.toCSV() << "\n";
    }
}

std::vector<Transaction> FileManager::loadTransactions() const {
    std::vector<Transaction> list;
    std::ifstream f(transactionsFile);
    if (!f.is_open()) return list;
    
    std::string line;
    std::getline(f, line); // header
    while (std::getline(f, line)) {
        if (!line.empty()) {
            list.push_back(Transaction::fromCSV(line));
        }
    }
    return list;
}

void FileManager::saveTransactions(const std::vector<Transaction> &transactions) const {
    std::ofstream f(transactionsFile);
    if (!f.is_open()) return;
    
    f << "transactionID|bookID|memberID|bookTitle|memberName|issueDate|returnDate|returned|fineAmount\n";
    for (const auto &t : transactions) {
        f << t.toCSV() << "\n";
    }
}

bool FileManager::exportBooksCSV(const std::vector<Book> &books, const std::string &filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) return false;
    
    f << "Book ID,Title,Author,Category,Availability,Borrow Count\n";
    for (const auto &b : books) {
        std::string titleEsc = b.getTitle();
        if (titleEsc.find(',') != std::string::npos) titleEsc = "\"" + titleEsc + "\"";
        std::string authorEsc = b.getAuthor();
        if (authorEsc.find(',') != std::string::npos) authorEsc = "\"" + authorEsc + "\"";
        std::string catEsc = b.getCategory();
        if (catEsc.find(',') != std::string::npos) catEsc = "\"" + catEsc + "\"";
        
        f << b.getBookID() << "," 
          << titleEsc << "," 
          << authorEsc << "," 
          << catEsc << "," 
          << (b.getAvailability() ? "Available" : "Issued") << "," 
          << b.getBorrowCount() << "\n";
    }
    return true;
}

bool FileManager::exportTransactionsCSV(const std::vector<Transaction> &txns, const std::string &filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) return false;
    
    f << "Transaction ID,Book ID,Member ID,Book Title,Member Name,Issue Date,Return Date,Status,Fine Amount\n";
    for (const auto &t : txns) {
        std::string bt = t.getBookTitle();
        if (bt.find(',') != std::string::npos) bt = "\"" + bt + "\"";
        std::string mn = t.getMemberName();
        if (mn.find(',') != std::string::npos) mn = "\"" + mn + "\"";
        
        f << t.getTransactionID() << ","
          << t.getBookID() << ","
          << t.getMemberID() << ","
          << bt << ","
          << mn << ","
          << t.issueDateStr() << ","
          << t.returnDateStr() << ","
          << (t.isReturned() ? "Returned" : "Issued") << ","
          << t.getFineAmount() << "\n";
    }
    return true;
}
