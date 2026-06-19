#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <climits>
namespace Utils {

// ── String helpers ────────────────────────────────────────────────────
inline std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

inline std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

inline bool containsCI(const std::string& haystack, const std::string& needle) {
    return toLower(haystack).find(toLower(needle)) != std::string::npos;
}

// ── CSV helpers ───────────────────────────────────────────────────────
inline std::vector<std::string> splitCSV(const std::string& line, char delim = '|') {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string tok;
    while (std::getline(ss, tok, delim))
        tokens.push_back(tok);
    return tokens;
}

// ── Time helpers ──────────────────────────────────────────────────────
inline std::string timeToStr(time_t t) {
    if (t == 0) return "N/A";
    struct tm* tm_info = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d", tm_info);
    return std::string(buf);
}

inline time_t now() { return time(nullptr); }

inline int daysBetween(time_t from, time_t to) {
    double diff = difftime(to, from);
    return static_cast<int>(diff / 86400.0);
}

// ── Console UI helpers ────────────────────────────────────────────────
inline void printLine(char c = '-', int len = 60) {
    std::cout << std::string(len, c) << "\n";
}

inline void printHeader(const std::string& title) {
    printLine('=');
    int pad = (60 - static_cast<int>(title.size()) - 2) / 2;
    std::cout << std::string(pad > 0 ? pad : 0, ' ')
              << "[ " << title << " ]\n";
    printLine('=');
}

inline void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(10000, '\n');
    // Sometimes cin has already consumed newline; absorb one more
    if (std::cin.peek() == '\n') std::cin.ignore();
}

// ── Input helpers ─────────────────────────────────────────────────────
inline std::string getLine(const std::string& prompt) {
    std::string val;
    std::cout << prompt;
    std::getline(std::cin, val);
    return trim(val);
}

inline int getInt(const std::string& prompt, int lo = INT_MIN, int hi = INT_MAX) {
    while (true) {
        std::cout << prompt;
        std::string raw;
        std::getline(std::cin, raw);
        raw = trim(raw);
        try {
            int v = std::stoi(raw);
            if (v >= lo && v <= hi) return v;
            std::cout << "  [!] Enter a value between " << lo << " and " << hi << ".\n";
        } catch (...) {
            std::cout << "  [!] Invalid number. Try again.\n";
        }
    }
}

inline bool confirm(const std::string& msg) {
    std::string ans = getLine(msg + " (y/n): ");
    return !ans.empty() && ::tolower(ans[0]) == 'y';
}

} // namespace Utils