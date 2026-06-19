#include "Library.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

Library::Library() {
    loadAll();
}

std::string Library::generateBookID() const {
    int maxNum = 0;
    for (const auto &b : books) {
        std::string id = b.getBookID();
        if (id.size() > 1 && id[0] == 'B') {
            try {
                int num = std::stoi(id.substr(1));
                if (num > maxNum) maxNum = num;
            } catch (...) {}
        }
    }
    std::stringstream ss;
    ss << "B" << std::setw(4) << std::setfill('0') << (maxNum + 1);
    return ss.str();
}

std::string Library::generateMemberID() const {
    int maxNum = 0;
    for (const auto &m : members) {
        std::string id = m.getMemberID();
        if (id.size() > 1 && id[0] == 'M') {
            try {
                int num = std::stoi(id.substr(1));
                if (num > maxNum) maxNum = num;
            } catch (...) {}
        }
    }
    std::stringstream ss;
    ss << "M" << std::setw(4) << std::setfill('0') << (maxNum + 1);
    return ss.str();
}

std::string Library::generateTransactionID() const {
    int maxNum = 0;
    for (const auto &t : transactions) {
        std::string id = t.getTransactionID();
        if (id.size() > 1 && id[0] == 'T') {
            try {
                int num = std::stoi(id.substr(1));
                if (num > maxNum) maxNum = num;
            } catch (...) {}
        }
    }
    std::stringstream ss;
    ss << "T" << std::setw(4) << std::setfill('0') << (maxNum + 1);
    return ss.str();
}

int Library::findBookIdx(const std::string& id) const {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getBookID() == id) return static_cast<int>(i);
    }
    return -1;
}

int Library::findMemberIdx(const std::string& id) const {
    for (size_t i = 0; i < members.size(); ++i) {
        if (members[i].getMemberID() == id) return static_cast<int>(i);
    }
    return -1;
}

void Library::addBook() {
    Utils::printHeader("Add Book");
    std::string title = Utils::getLine("  Enter Title  : ");
    std::string author = Utils::getLine("  Enter Author : ");
    std::string category = Utils::getLine("  Enter Category: ");
    
    if (title.empty() || author.empty()) {
        std::cout << "\n  [!] Title and Author cannot be empty.\n";
        Utils::pause();
        return;
    }
    
    std::string id = generateBookID();
    Book b(id, title, author, category, true, 0);
    books.push_back(b);
    saveAll();
    std::cout << "\n  [✓] Book added successfully! ID: " << id << "\n";
    Utils::pause();
}

void Library::updateBook() {
    Utils::printHeader("Update Book");
    std::string id = Utils::getLine("  Enter Book ID to Update: ");
    int idx = findBookIdx(id);
    if (idx == -1) {
        std::cout << "\n  [!] Book not found.\n";
        Utils::pause();
        return;
    }
    
    std::cout << "\n  Current details:\n";
    books[idx].display();
    std::cout << "\n  (Leave field empty to keep current value)\n";
    
    std::string title = Utils::getLine("  New Title : ");
    std::string author = Utils::getLine("  New Author: ");
    std::string category = Utils::getLine("  New Category: ");
    
    if (!title.empty()) books[idx].setTitle(title);
    if (!author.empty()) books[idx].setAuthor(author);
    if (!category.empty()) books[idx].setCategory(category);
    
    saveAll();
    std::cout << "\n  [✓] Book updated successfully!\n";
    Utils::pause();
}

void Library::deleteBook() {
    Utils::printHeader("Delete Book");
    std::string id = Utils::getLine("  Enter Book ID to Delete: ");
    int idx = findBookIdx(id);
    if (idx == -1) {
        std::cout << "\n  [!] Book not found.\n";
        Utils::pause();
        return;
    }
    
    books[idx].display();
    if (Utils::confirm("\n  Are you sure you want to delete this book?")) {
        books.erase(books.begin() + idx);
        saveAll();
        std::cout << "\n  [✓] Book deleted successfully!\n";
    } else {
        std::cout << "\n  Delete cancelled.\n";
    }
    Utils::pause();
}

void Library::viewAllBooks() const {
    Utils::printHeader("All Books");
    if (books.empty()) {
        std::cout << "  No books available in the library.\n";
    } else {
        for (const auto &b : books) {
            b.display();
        }
    }
    Utils::pause();
}

void Library::addMember() {
    Utils::printHeader("Add Member");
    std::string name = Utils::getLine("  Enter Member Name: ");
    std::string contact = Utils::getLine("  Enter Contact Info: ");
    
    if (name.empty() || contact.empty()) {
        std::cout << "\n  [!] Name and Contact cannot be empty.\n";
        Utils::pause();
        return;
    }
    
    std::string id = generateMemberID();
    Member m(id, name, contact, 0);
    members.push_back(m);
    saveAll();
    std::cout << "\n  [✓] Member added successfully! ID: " << id << "\n";
    Utils::pause();
}

void Library::viewAllMembers() const {
    Utils::printHeader("All Members");
    if (members.empty()) {
        std::cout << "  No members registered.\n";
    } else {
        for (const auto &m : members) {
            m.display();
        }
    }
    Utils::pause();
}

void Library::viewMemberHistory() const {
    Utils::printHeader("Member History");
    std::string id = Utils::getLine("  Enter Member ID: ");
    int idx = findMemberIdx(id);
    if (idx == -1) {
        std::cout << "\n  [!] Member not found.\n";
        Utils::pause();
        return;
    }
    
    members[idx].display();
    std::cout << "\n  ── Borrow Transactions ───────────────────\n";
    bool foundTx = false;
    for (const auto &t : transactions) {
        if (t.getMemberID() == id) {
            t.display();
            foundTx = true;
        }
    }
    if (!foundTx) {
        std::cout << "  No transactions found for this member.\n";
    }
    Utils::pause();
}

void Library::issueBook() {
    Utils::printHeader("Issue Book");
    std::string mid = Utils::getLine("  Enter Member ID: ");
    int mIdx = findMemberIdx(mid);
    if (mIdx == -1) {
        std::cout << "\n  [!] Member not found.\n";
        Utils::pause();
        return;
    }
    
    std::string bid = Utils::getLine("  Enter Book ID: ");
    int bIdx = findBookIdx(bid);
    if (bIdx == -1) {
        std::cout << "\n  [!] Book not found.\n";
        Utils::pause();
        return;
    }
    
    if (!books[bIdx].getAvailability()) {
        std::cout << "\n  [!] Book is already issued.\n";
        Utils::pause();
        return;
    }
    
    std::string tid = generateTransactionID();
    Transaction t(tid, bid, mid, books[bIdx].getTitle(), members[mIdx].getName(), Utils::now());
    transactions.push_back(t);
    
    books[bIdx].setAvailability(false);
    books[bIdx].incrementBorrowCount();
    
    members[mIdx].incrementBorrow();
    members[mIdx].addToBorrowHistory(bid);
    
    saveAll();
    std::cout << "\n  [✓] Book issued successfully! Tx ID: " << tid << "\n";
    Utils::pause();
}

void Library::returnBook() {
    Utils::printHeader("Return Book");
    std::string bid = Utils::getLine("  Enter Book ID: ");
    int bIdx = findBookIdx(bid);
    if (bIdx == -1) {
        std::cout << "\n  [!] Book not found.\n";
        Utils::pause();
        return;
    }
    
    if (books[bIdx].getAvailability()) {
        std::cout << "\n  [!] This book is not currently issued.\n";
        Utils::pause();
        return;
    }
    
    int txIdx = -1;
    for (size_t i = 0; i < transactions.size(); ++i) {
        if (transactions[i].getBookID() == bid && !transactions[i].isReturned()) {
            txIdx = static_cast<int>(i);
            break;
        }
    }
    
    if (txIdx == -1) {
        std::cout << "\n  [!] Active transaction not found for this book.\n";
        books[bIdx].setAvailability(true);
        saveAll();
        Utils::pause();
        return;
    }
    
    time_t nowTime = Utils::now();
    double fine = transactions[txIdx].calculateFine(nowTime);
    transactions[txIdx].markReturned(nowTime);
    transactions[txIdx].setFineAmount(fine);
    
    books[bIdx].setAvailability(true);
    
    int mIdx = findMemberIdx(transactions[txIdx].getMemberID());
    if (mIdx != -1) {
        members[mIdx].decrementBorrow();
    }
    
    saveAll();
    std::cout << "\n  [✓] Book returned successfully!\n";
    if (fine > 0.0) {
        std::cout << "  [!] Fine Calculated: $" << std::fixed << std::setprecision(2) << fine << "\n";
    } else {
        std::cout << "  No fine incurred.\n";
    }
    Utils::pause();
}

void Library::searchByID() const {
    Utils::printHeader("Search by ID");
    std::string id = Utils::getLine("  Enter Book ID: ");
    int idx = findBookIdx(id);
    if (idx != -1) {
        books[idx].display();
    } else {
        std::cout << "  Book not found.\n";
    }
    Utils::pause();
}

void Library::searchByTitle() const {
    Utils::printHeader("Search by Title");
    std::string title = Utils::getLine("  Enter title keywords: ");
    bool found = false;
    for (const auto &b : books) {
        if (Utils::containsCI(b.getTitle(), title)) {
            b.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No books matching the title were found.\n";
    }
    Utils::pause();
}

void Library::searchByAuthor() const {
    Utils::printHeader("Search by Author");
    std::string author = Utils::getLine("  Enter author keywords: ");
    bool found = false;
    for (const auto &b : books) {
        if (Utils::containsCI(b.getAuthor(), author)) {
            b.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No books matching the author were found.\n";
    }
    Utils::pause();
}

void Library::reportMostBorrowed() const {
    Utils::printHeader("Most Borrowed Books");
    if (books.empty()) {
        std::cout << "  No books available.\n";
        Utils::pause();
        return;
    }
    
    auto sortedBooks = books;
    std::sort(sortedBooks.begin(), sortedBooks.end(), [](const Book &a, const Book &b) {
        return a.getBorrowCount() > b.getBorrowCount();
    });
    
    int limit = std::min(5, static_cast<int>(sortedBooks.size()));
    std::cout << "  Top " << limit << " most borrowed books:\n\n";
    for (int i = 0; i < limit; ++i) {
        std::cout << "  " << (i + 1) << ". ";
        sortedBooks[i].display();
    }
    Utils::pause();
}

void Library::reportCurrentlyIssued() const {
    Utils::printHeader("Currently Issued Books");
    bool found = false;
    for (const auto &t : transactions) {
        if (!t.isReturned()) {
            t.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No books are currently issued.\n";
    }
    Utils::pause();
}

void Library::reportOverdue() const {
    Utils::printHeader("Overdue Report");
    bool found = false;
    time_t currTime = Utils::now();
    for (const auto &t : transactions) {
        if (!t.isReturned() && t.daysOverdue(currTime) > 0) {
            t.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No overdue books found.\n";
    }
    Utils::pause();
}

void Library::exportReports() const {
    Utils::printHeader("Export Reports");
    std::string bFile = Utils::getLine("  Enter filename for Books Export (e.g. books_export.csv): ");
    std::string tFile = Utils::getLine("  Enter filename for Transactions Export (e.g. txns_export.csv): ");
    
    if (bFile.empty()) bFile = "books_export.csv";
    if (tFile.empty()) tFile = "txns_export.csv";
    
    bool okB = fileManager.exportBooksCSV(books, bFile);
    bool okT = fileManager.exportTransactionsCSV(transactions, tFile);
    
    if (okB && okT) {
        std::cout << "\n  [✓] Reports exported successfully to " << bFile << " and " << tFile << ".\n";
    } else {
        std::cout << "\n  [!] Error occurred during export.\n";
    }
    Utils::pause();
}

void Library::loadAll() {
    books = fileManager.loadBooks();
    members = fileManager.loadMembers();
    transactions = fileManager.loadTransactions();
}

void Library::saveAll() const {
    fileManager.saveBooks(books);
    fileManager.saveMembers(members);
    fileManager.saveTransactions(transactions);
}
