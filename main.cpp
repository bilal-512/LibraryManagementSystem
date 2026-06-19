#include <iostream>
#include <string>
#include <limits>
#include "../include/Library.h"
#include "../include/Auth.h"
#include "../include/Utils.h"

// ── Forward declarations ──────────────────────────────────────────────
void adminMenu(Library &lib);
void memberMenu(Library &lib, const std::string &memberID);
bool loginScreen(Auth &auth, Library &lib);

// ════════════════════════════════════════════════════════════════════
// ENTRY POINT
// ════════════════════════════════════════════════════════════════════
int main()
{
    Library lib;
    Auth auth;

    while (true)
    {
        if (!loginScreen(auth, lib))
            break; // user chose Exit

        if (auth.isAdmin())
            adminMenu(lib);
        else
            memberMenu(lib, auth.getMemberID());

        auth.logout();
    }

    std::cout << "\n  Goodbye! Data saved.\n\n";
    return 0;
}

// ════════════════════════════════════════════════════════════════════
// LOGIN SCREEN
// ════════════════════════════════════════════════════════════════════
bool loginScreen(Auth &auth, Library &lib)
{
    while (true)
    {
        system("clear");
        Utils::printLine('=');
        std::cout << "         TEYZIX CORE — Library Management System\n";
        Utils::printLine('=');
        std::cout << "\n  [1] Login as Admin\n"
                  << "  [2] Login as Member\n"
                  << "  [0] Exit\n\n";

        int ch = Utils::getInt("  Choice: ", 0, 2);

        if (ch == 0)
            return false;

        if (ch == 1)
        {
            std::string user = Utils::getLine("  Username: ");
            std::cout << "  Password: ";
            std::string pass;
            std::getline(std::cin, pass); // keep password simple
            if (auth.loginAdmin(user, pass))
            {
                std::cout << "\n  [✓] Welcome, Admin!\n";
                Utils::pause();
                return true;
            }
            else
            {
                std::cout << "\n  [!] Invalid credentials.\n";
                Utils::pause();
            }
        }
        else
        {
            std::string mid = Utils::getLine("  Member ID: ");
            std::string cont = Utils::getLine("  Contact  : ");
            if (auth.loginMember(mid, cont, lib))
            {
                std::cout << "\n  [✓] Welcome back!\n";
                Utils::pause();
                return true;
            }
            else
            {
                std::cout << "\n  [!] Member ID or contact not found.\n";
                Utils::pause();
            }
        }
    }
}

// ════════════════════════════════════════════════════════════════════
// ADMIN MENU
// ════════════════════════════════════════════════════════════════════
void adminMenu(Library &lib)
{
    while (true)
    {
        system("clear");
        Utils::printHeader("Admin Menu");
        std::cout
            << "\n  ── Book Management ─────────────────\n"
            << "  [1]  Add Book\n"
            << "  [2]  Update Book\n"
            << "  [3]  Delete Book\n"
            << "  [4]  View All Books\n"
            << "\n  ── Member Management ───────────────\n"
            << "  [5]  Add Member\n"
            << "  [6]  View All Members\n"
            << "  [7]  View Member History\n"
            << "\n  ── Borrow & Return ─────────────────\n"
            << "  [8]  Issue Book\n"
            << "  [9]  Return Book\n"
            << "\n  ── Search ──────────────────────────\n"
            << "  [10] Search by ID\n"
            << "  [11] Search by Title\n"
            << "  [12] Search by Author\n"
            << "\n  ── Reports ─────────────────────────\n"
            << "  [13] Most Borrowed Books\n"
            << "  [14] Currently Issued Books\n"
            << "  [15] Overdue Report\n"
            << "  [16] Export Reports to CSV\n"
            << "\n  [0]  Logout\n\n";

        int ch = Utils::getInt("  Choice: ", 0, 16);
        system("clear");

        switch (ch)
        {
        case 0:
            return;
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.updateBook();
            break;
        case 3:
            lib.deleteBook();
            break;
        case 4:
            lib.viewAllBooks();
            break;
        case 5:
            lib.addMember();
            break;
        case 6:
            lib.viewAllMembers();
            break;
        case 7:
            lib.viewMemberHistory();
            break;
        case 8:
            lib.issueBook();
            break;
        case 9:
            lib.returnBook();
            break;
        case 10:
            lib.searchByID();
            break;
        case 11:
            lib.searchByTitle();
            break;
        case 12:
            lib.searchByAuthor();
            break;
        case 13:
            lib.reportMostBorrowed();
            break;
        case 14:
            lib.reportCurrentlyIssued();
            break;
        case 15:
            lib.reportOverdue();
            break;
        case 16:
            lib.exportReports();
            break;
        default:
            break;
        }
    }
}

// ════════════════════════════════════════════════════════════════════
// MEMBER MENU  (read-only access to search & view own history)
// ════════════════════════════════════════════════════════════════════
void memberMenu(Library &lib, const std::string & /*memberID*/)
{
    while (true)
    {
        system("clear");
        Utils::printHeader("Member Menu");
        std::cout
            << "\n  [1]  View All Books\n"
            << "  [2]  Search Book by Title\n"
            << "  [3]  Search Book by Author\n"
            << "  [4]  My Borrow History\n"
            << "  [0]  Logout\n\n";

        int ch = Utils::getInt("  Choice: ", 0, 4);
        system("clear");

        switch (ch)
        {
        case 0:
            return;
        case 1:
            lib.viewAllBooks();
            break;
        case 2:
            lib.searchByTitle();
            break;
        case 3:
            lib.searchByAuthor();
            break;
        case 4:
            lib.viewMemberHistory();
            break;
        default:
            break;
        }
    }
}