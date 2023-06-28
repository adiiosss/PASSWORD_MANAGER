/**
 * @file category_manager.cpp
 * @brief This file contains the implementation of the category_manager class.
 */

#ifndef PASSWORDMANAGER_CATEGORY_MANAGER_H
#define PASSWORDMANAGER_CATEGORY_MANAGER_H

#include <string>
#include <set>

namespace pm {

    /**
     * @class category_manager
     * @brief This class stores the categories.
     */

    class category_manager {
        /**
        * @brief This variable stores all categories present in file
        */
        std::set<std::string> categories;
    public:
        /**
         * @brief Creates category
         * @param category Category to create
         */
        void add_category(std::string category);
        /**
         * @brief removes category
         * @param category Category to remove
         */
        void remove_category(std::string category);
        /**
         * @brief returns all categories
         */
        std::set<std::string> get_categories() const;
    };

}

#endif