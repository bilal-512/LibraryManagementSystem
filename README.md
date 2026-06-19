# TEYZIX CORE — Library Management System

A robust, terminal-based Library Management System written in modern **C++17**. The application provides distinct role-based views (Admin and Member), custom search operations, reporting features, and reliable data persistence utilizing delimiter-separated CSV files.

---

## 🚀 Features

### 👤 Role-Based Authentication
* **Admin Login**: Grants complete administrative control over library resources and configurations.
* **Member Login**: Offers read-only access for members to browse books, search the catalog, and view their individual borrow/return history.

### 📚 Book Management (Admin Only)
* Add new books to the catalog with auto-generated book IDs.
* Update book metadata (Title, Author, Category).
* Soft or hard delete books from active tracking.
* View catalog status in real-time.

### 👥 Member Management (Admin Only)
* Register new members and generate unique IDs.
* View registered members and active borrowing limits.
* View individual member transaction histories.

### 🔄 Borrow & Return (Admin Only)
* **Issue Book**: Link a book to a member, updating availability and recording timestamps.
* **Return Book**: Record return times and auto-calculate potential overdue fines.

### 🔍 Advanced Catalog Search (Admin & Member)
* Search books instantly by:
  * Book ID
  * Title (substring match)
  * Author (substring match)

### 📈 Reports & CSV Export (Admin Only)
* **Most Borrowed Books**: Identify popular books in the catalog.
* **Currently Issued Books**: List all outstanding loans.
* **Overdue Report**: Track books past their return deadlines.
* **Export Reports**: Save analytical reports straight to CSV format.

### 💾 Persistent CSV Storage
* Uses a high-performance pipe-delimited (`|`) format to load and save states.
* Saves data automatically to files in the `data/` directory when exiting the application.

---

## 📂 Project Structure

```text
LibraryManagementSystem/
├── CMakeLists.txt         # Project build definition
├── main.cpp               # App entry-point and console menus
├── include/               # Header definitions (.h)
│   ├── Auth.h             # Authentication helper class
│   ├── Book.h             # Book entity class
│   ├── FileManager.h      # CSV-based persistence manager
│   ├── Library.h          # Core system coordinator
│   ├── Member.h           # Member entity class
│   ├── Transaction.h      # Transaction logs representation
│   └── Utils.h            # Console input/output utilities
├── src/                   # Source files (.cpp)
│   ├── Auth.cpp
│   ├── Book.cpp
│   ├── FileManager.cpp
│   ├── Library.cpp
│   ├── Member.cpp
│   └── Transaction.cpp
├── data/                  # Persistent data directory
│   ├── books.csv          # Catalog records
│   ├── members.csv        # Registered library members
│   └── transactions.csv   # Issued/returned book transaction log
└── build/                 # Compiled executable & artifacts (ignored in git)
```

---

## 🛠️ Requirements & Setup

Ensure you have the following installed on your system:
* **Compiler**: GCC (v7.0+), Clang (v5.0+), or MSVC 2017+ (with C++17 support)
* **Build System**: [CMake](https://cmake.org/) (v3.12+)
* **Build Tools**: Make, Ninja, or Visual Studio Build Tools

### 🔨 Compilation

Compile the project from the root folder:

```bash
# 1. Create and move into a build directory
mkdir -p build
cd build

# 2. Configure project with CMake
cmake ..

# 3. Compile the executable
make
```

---

## 🏃 Running the Application

For the application to find and save its database correctly, run it from the project root directory or ensure the `data/` directory is present in your execution path:

```bash
# From the project root:
./build/LibrarySystem
```

---

## 🔑 Credentials

The application initializes with the following default authentication details:

| Role | Username / Identifier | Password / Validation |
| :--- | :--- | :--- |
| **Admin** | `admin` | `library@123` |
| **Member** | *Use any Member ID in database* (e.g. `M0001`) | *Use registered Contact Number* (e.g. `12345678`) |

---

## 📊 Data Format

Data is serialized to flat CSV files in the `data/` directory using a pipe (`|`) delimiter to support titles or authors that may contain commas:

* **Books (`data/books.csv`)**: `bookID|title|author|category|isAvailable|borrowCount`
* **Members (`data/members.csv`)**: `memberID|name|contact|activeBorrowCount|borrowHistory`
* **Transactions (`data/transactions.csv`)**: `transactionID|bookID|memberID|bookTitle|memberName|issueDate|returnDate|returned|fineAmount`

---

## 📝 License

This project is open-source. Feel free to clone, modify, and build upon it!
