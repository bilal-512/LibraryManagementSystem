#pragma once
#include <vector>
#include <string>
#include "Book.h"
#include "Member.h"
#include "Transaction.h"
#include "FileManager.h"

class Library {
private:
    std::vector<Book>        books;
    std::vector<Member>      members;
    std::vector<Transaction> transactions;
    FileManager              fileManager;

    // ID generators
    std::string generateBookID()        const;
    std::string generateMemberID()      const;
    std::string generateTransactionID() const;

    // Internal finders
    int findBookIdx(const std::string& id)   const;
    int findMemberIdx(const std::string& id) const;

public:
    Library();

    // ── Book Management ──────────────────────────────────────────────
    void addBook();
    void updateBook();
    void deleteBook();
    void viewAllBooks() const;

    // ── Member Management ────────────────────────────────────────────
    void addMember();
    void viewAllMembers() const;
    void viewMemberHistory() const;

    // ── Borrow & Return ──────────────────────────────────────────────
    void issueBook();
    void returnBook();

    // ── Search ───────────────────────────────────────────────────────
    void searchByID()     const;
    void searchByTitle()  const;
    void searchByAuthor() const;

    // ── Reports ──────────────────────────────────────────────────────
    void reportMostBorrowed()   const;
    void reportCurrentlyIssued() const;
    void reportOverdue()         const;
    void exportReports()         const;

    // ── Persistence ──────────────────────────────────────────────────
    void loadAll();
    void saveAll() const;

    // Read-only accessors for Auth
    const std::vector<Member>& getMembersRef() const { return members; }
};