#include "Transaction.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

const double Transaction::FINE_PER_DAY = 2.0;

int Transaction::daysOverdue(time_t nowVal) const {
    time_t end = returned ? returnDate : (nowVal == 0 ? Utils::now() : nowVal);
    int days = Utils::daysBetween(issueDate, end);
    return (days > MAX_BORROW_DAYS) ? (days - MAX_BORROW_DAYS) : 0;
}

double Transaction::calculateFine(time_t nowVal) const {
    if (returned) return fineAmount;
    int overdue = daysOverdue(nowVal);
    return overdue * FINE_PER_DAY;
}

std::string Transaction::issueDateStr() const {
    return Utils::timeToStr(issueDate);
}

std::string Transaction::returnDateStr() const {
    return returned ? Utils::timeToStr(returnDate) : "Not Returned";
}

void Transaction::display() const {
    std::cout << "  Tx ID: " << transactionID 
              << " | Book: " << bookTitle << " (" << bookID << ")"
              << " | Member: " << memberName << " (" << memberID << ")\n"
              << "    Issued: " << issueDateStr() 
              << " | Returned: " << returnDateStr() 
              << " | Overdue: " << daysOverdue() << " days"
              << " | Fine: $" << std::fixed << std::setprecision(2) << calculateFine() << "\n";
}

std::string Transaction::toCSV() const {
    return transactionID + "|" + bookID + "|" + memberID + "|" + bookTitle + "|" + memberName + "|"
           + std::to_string(issueDate) + "|" + std::to_string(returnDate) + "|"
           + (returned ? "1" : "0") + "|" + std::to_string(fineAmount);
}

Transaction Transaction::fromCSV(const std::string& line) {
    auto tokens = Utils::splitCSV(line);
    if (tokens.size() < 5) {
        return Transaction();
    }
    std::string tid = tokens[0];
    std::string bid = tokens[1];
    std::string mid = tokens[2];
    std::string bt = tokens[3];
    std::string mn = tokens[4];
    time_t issue = 0;
    if (tokens.size() > 5) {
        try { issue = std::stoll(tokens[5]); } catch (...) {}
    }
    time_t ret = 0;
    if (tokens.size() > 6) {
        try { ret = std::stoll(tokens[6]); } catch (...) {}
    }
    bool isRet = false;
    if (tokens.size() > 7) {
        isRet = (tokens[7] == "1");
    }
    double fine = 0.0;
    if (tokens.size() > 8) {
        try { fine = std::stod(tokens[8]); } catch (...) {}
    }
    Transaction t(tid, bid, mid, bt, mn, issue);
    if (isRet) {
        t.markReturned(ret);
    }
    t.setFineAmount(fine);
    return t;
}
