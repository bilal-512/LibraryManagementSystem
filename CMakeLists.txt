cmake_minimum_required(VERSION 3.12)
project(LibrarySystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(LibrarySystem
    main.cpp
    src/Auth.cpp
    src/Book.cpp
    src/Member.cpp
    src/Transaction.cpp
    src/FileManager.cpp
    src/Library.cpp
)
