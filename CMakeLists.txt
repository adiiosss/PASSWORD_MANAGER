cmake_minimum_required(VERSION 3.24.2)
project(PASSWORD_MANAGER)

set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordManager
        main.cpp
        password_entry.cpp
        password_entry.h
        category_manager.cpp
        category_manager.h
        password_storage.cpp
        password_storage.h
        cryptography.h
        )