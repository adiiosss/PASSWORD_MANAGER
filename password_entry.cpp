#include "password_entry.h"

/**
 * @brief function for password entry in programme
 *
 * This function has a passswrod, name and category for password management.
 */

namespace pm {
    password_entry::password_entry(std::string password, std::string name, std::string category) : password(password), name(name), category(category), login(""), site("") {
        // Konstruktor klasy password_entry. Inicjalizuje obiekt password_entry przyjmując trzy argumenty: password, name i category.
        // Wykorzystuje listę inicjalizacyjną, aby zainicjalizować zmienne składowe obiektu.
        // password - inicjalizuje zmienną składową password obiektem password przekazanym jako argument
        // name - inicjalizuje zmienną składową name obiektem name przekazanym jako argument
        // category - inicjalizuje zmienną składową category obiektem category przekazanym jako argument
        // login i site są inicjalizowane pustymi stringami ("")

    }

    void password_entry::set_login_and_site(const std::string login, const std::string site) {
        // Funkcja ustawiająca wartości dla zmiennych składowych login i site obiektu password_entry.
        // Przyjmuje dwa argumenty: login i site.
        // Ustawia wartość zmiennej składowej login na przekazany login.
        // Ustawia wartość zmiennej składowej site na przekazany site.
        this->login = login;
        this->site = site;
    }
}
