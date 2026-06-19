#pragma once
#include <string>
#include <ctime>

class Transaction {
private:
    std::string transactionID;
    std::string bookID;
    std::string memberID;
    std::string bookTitle;
    std::string memberName;
    time_t issueDate;
    time_t returnDate;   // 0 if not returned
    bool returned;
    double fineAmount;

public:
    static const int MAX_BORROW_DAYS = 14;
    static const double FINE_PER_DAY;

    Transaction() : issueDate(0), returnDate(0), returned(false), fineAmount(0.0) {}
    Transaction(std::string tid, std::string bid, std::string mid,
                std::string bt, std::string mn, time_t issue)
        : transactionID(tid), bookID(bid), memberID(mid),
          bookTitle(bt), memberName(mn),
          issueDate(issue), returnDate(0), returned(false), fineAmount(0.0) {}

    // Getters
    std::string getTransactionID() const { return transactionID; }
    std::string getBookID()        const { return bookID; }
    std::string getMemberID()      const { return memberID; }
    std::string getBookTitle()     const { return bookTitle; }
    std::string getMemberName()    const { return memberName; }
    time_t getIssueDate()          const { return issueDate; }
    time_t getReturnDate()         const { return returnDate; }
    bool   isReturned()            const { return returned; }
    double getFineAmount()         const { return fineAmount; }

    // Setters
    void markReturned(time_t rd) {
        returnDate = rd;
        returned   = true;
    }
    void setFineAmount(double f) { fineAmount = f; }

    int daysOverdue(time_t now = 0) const;
    double calculateFine(time_t now = 0) const;

    std::string issueDateStr()  const;
    std::string returnDateStr() const;

    void display() const;
    std::string toCSV() const;
    static Transaction fromCSV(const std::string& line);
};