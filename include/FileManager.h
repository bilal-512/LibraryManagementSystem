#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include "Member.h"
#include "Transaction.h"

class FileManager
{
private:
    std::string booksFile;
    std::string membersFile;
    std::string transactionsFile;

public:
    FileManager(const std::string &dataDir = "data/");

    // Books
    std::vector<Book> loadBooks() const;
    void saveBooks(const std::vector<Book> &books) const;

    // Members
    std::vector<Member> loadMembers() const;
    void saveMembers(const std::vector<Member> &members) const;

    // Transactions
    std::vector<Transaction> loadTransactions() const;
    void saveTransactions(const std::vector<Transaction> &transactions) const;

    // CSV Export
    bool exportBooksCSV(const std::vector<Book> &books,
                        const std::string &filename) const;
    bool exportTransactionsCSV(const std::vector<Transaction> &txns,
                               const std::string &filename) const;

private:
    void ensureFileExists(const std::string &filepath,
                          const std::string &header) const;
};