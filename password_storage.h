/**
 * @file password_storage.cpp
 * @brief This file contains the implementation of the password_storage class.
 */

#ifndef PASSWORDMANAGER_PASSWORD_STORAGE_H
#define PASSWORDMANAGER_PASSWORD_STORAGE_H

#include <vector>
#include "password_entry.h"
#include "category_manager.h"
#include <string>

namespace pm {

/**
 * @class password_storage
 * @brief This class contains the main loop of the program and stores password entries.
 */

    class password_storage {
        /**
         * @brief This variable stores all password data
         */
        std::vector<password_entry> password_entries;
        /**
         * @brief This variable stores the category manager
         */
        pm::category_manager manager;
        /**
         * @brief This variable stores password of the current file
         */
        std::string pass;
        /**
         * @brief This variable stores the name of the current file
         */
        std::string file;

        /**
         * @brief Constructor of password storage
         * @param content Content without the first line of the current file
         * @param pass Password of file
         * @param file Name of file
         */
        explicit password_storage(std::string content, std::string pass, std::string file);  //explicit zastosować do jednoargumentowych konstruktorów klasy

        /**
         * @brief Updates contents of the current file
         */
        void update_file() const;
        /**
         * @brief Adds password
         */
        void add_password_command();
        /**
         * @brief Prints out all passwords
         */
        void search_password_command() const;
        /**
         * @brief Prints sorted password
         */
        void sort_password_command() const;
        /**
         * @brief Removes password
         */
        void remove_password_command();
        /**
         * @brief Edits password
         */
        void edit_password_command();
        /**
         * @brief Adds category
         */
        void add_category_command();
        /**
         * @brief Removes category
         */
        void remove_category_command();

    public:  //dwie statyczne metody
        /**
         * @brief Creates password storage from file
         * @param file File to operate on
         */
        static password_storage initialize(std::string file);
        /**
         * @brief Creates file as well as password storage
         * @param file File to operate on
         */
        static password_storage generate(std::string file);
    };

}

#endif
