#include "category_manager.h"

/**
 * @brief function for categories in programme
 *
 * This function has a commends for categories for password management.
 */

namespace pm {
    void category_manager::add_category(std::string category) {
        categories.insert(category); // Dodaje kategorię do zbioru kategorii
    }

    void category_manager::remove_category(std::string category) {
        categories.erase(category); // Usuwa kategorię ze zbioru kategorii
    }

    std::set<std::string> category_manager::get_categories() const {
        return categories; // Zwraca zbiór wszystkich kategorii
    }
}
