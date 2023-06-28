/**
 * @file password_entry.cpp
 * @brief This file contains the implementation of the password_entry class.
 */

#ifndef PASSWORDMANAGER_PASSWORD_ENTRY_H
#define PASSWORDMANAGER_PASSWORD_ENTRY_H

#include <string>

namespace pm {

    /**
     * @class password_entry
     * @brief This class stores the password data.
     */

    class password_entry {
    public:
        /**
       * @brief Those variables store all password data
       */
        std::string password, name, category, site, login;

        /**
         * @brief Constructor of password entry class
         */
        password_entry(std::string password, std::string name, std::string category);
        /**
          * @brief Adds site and login data
          */
        void set_login_and_site(const std::string login, const std::string site);
    };

}

#endif
