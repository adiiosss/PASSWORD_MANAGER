#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include "password_storage.h"
#include "cryptography.h"


/**
 * @brief function for commends in programme
 *
 * This function give the user commends to select for password management.
 */


namespace pm {

    password_storage password_storage::initialize(std::string a) {
        std::cout << "\nPodaj haslo do pliku:\n";
        std::string input;
        std::cin >> input;
        std::string hash = pm::generate_hash_from_password(input);
        hash.pop_back();
        std::ifstream file(a, std::ios::binary);
        std::string first_line;
        std::getline(file, first_line);
        char byte;
        std::string content; // cała zawartość pliku zostanie zapisana w zmiennej content
        while (file.get(byte)) {
            content = content + byte;
        }
        file.close();
        first_line.pop_back();

        if (hash == first_line) {
            std::cout << "Dobre haslo\n";
            content = pm::apply_xor_cypher(content, input); // odszyfrowanie zawartości pliku

            return password_storage(content, input, a); // utworzenie obiektu password_storage na podstawie odszyfrowanej zawartości
        }
        else {
            std::cout << "Zle haslo\n";
            return password_storage("", "", ""); // zwraca pusty obiekt password_storage, jeśli hasło jest niepoprawne
        }
    }


    password_storage password_storage::generate(std::string file) {
        std::cout << "\nPodaj haslo do nowego pliku:\n";
        std::string input = "";
        std::cin >> input;
        std::fstream file2(file, std::ios::out); // strumień, który dopisuje do pliku
        std::string hash = pm::generate_hash_from_password(input);

        file2 << hash; // zapisuje hash do pliku
        file2.close();

        return password_storage(initialize(file)); // inicjalizuje program na podstawie nowo utworzonego pliku
    }


    password_storage::password_storage(std::string content, std::string pass, std::string file) : password_entries(std::vector<password_entry>()),
        manager(category_manager()), pass(pass), file(file){
        if(pass == "")
        {
            return;
        }

        std::vector<std::vector<std::string>> rows;  //content jest w formacie: haslo nazwa kategori login(opcjonalnie) strona(opcjonalnie)
        std::istringstream iss(content);
        std::string line;

        //przechodzi przez kazda linie
        while (std::getline(iss, line, '\n')) {
            std::vector<std::string> words;
            std::istringstream lineStream(line);
            std::string word;

            //dodaje slowa do words w tym formacie (czyli np haslo to wrod[0] a nazwa to [1]: hasło nazwa kategoria login (opcjonalnie) strona (opcjonalnie)
            while (std::getline(lineStream, word, '\t')) {
                words.push_back(word);
            }

            //kazda nowa linia to nowe entry hasla wiec dodaje words do vectora wszystkich linii (czyli wszystkich rekordow hasel)
            rows.push_back(words);
        }


        //przechodzi przez wszystkie wiersze i generuje z nich obiekty password_entry oraz kategorie i dodaje je odpowiednio do password_entries i do category_managera
        for(auto vec : rows)
        {
            password_entry entry = password_entry(vec.at(0), vec.at(1), vec.at(2));
            manager.add_category(vec.at(2));
            if(vec.size() > 3)
                entry.set_login_and_site(vec.at(3), vec.at(4));
            password_entries.push_back(entry);
        }

        std::cout << "\nKomenda 'exit' wychodzi z programu\n";
        
        std::string input;
        do{
            std::cout << "\nWybierz jedna z komend - exit, search, sort, add, edit, remove, add_category, remove_category:   ";

            std::cin >> input;
            if(input == "exit")
                return;
            else if(input == "search")
                search_password_command();
            else if(input == "sort")
                sort_password_command();
            else if(input == "add")
                add_password_command();
            else if(input == "edit")
                edit_password_command();
            else if(input == "remove")
                remove_password_command();
            else if(input == "add_category")
                add_category_command();
            else if(input == "remove_category")
                remove_category_command();
            else
                std::cout << "Nie rozpoznano komendy, sprobuj ponownie:\n";

        } while (input != "exit");
    }

    void password_storage::update_file() const {
        std::fstream file2(file, std::ofstream::out | std::ofstream::trunc);
        file2 << pm::generate_hash_from_password(pass);
        std::string content = "";
        for(auto entry : password_entries)
        {
            content = content + entry.password + "\t" + entry.name + "\t" + entry.category;
            if(entry.login != "")
                content = content + "\t" + entry.site + "\t" + entry.login;
            content = content + "\n";
        }
        content = pm::apply_xor_cypher(content, pass);
        file2 << content;
        file2.close();
    }

    std::string random_passoword(const int size, const bool uppercase, const bool special)
    {
        std::string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
        std::string uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string specialCharacters = "!@#$%^&*()_+-=[]{}|;':,.<>?";
        std::string output = "";

        for (int i = 0; i < size; i++) {
            int type = rand() % 3; // Losuje liczbę od 0 do 2, aby wybrać typ znaku do dodania

            if (type == 0) {
                int letter = rand() % lowercaseLetters.size(); // Losuje indeks litery małej
                output = output + lowercaseLetters[letter]; // Dodaje wybraną małą literę do output
            } else if (type == 1 && uppercase) {
                int letter = rand() % uppercaseLetters.size(); // Losuje indeks wielkiej litery
                output = output + uppercaseLetters[letter]; // Dodaje wybraną wielką literę do output
            } else if (type == 2 && special) {
                int letter = rand() % specialCharacters.size(); // Losuje indeks znaku specjalnego
                output = output + specialCharacters[letter]; // Dodaje wybrany znak specjalny do output
            } else {
                int letter = rand() % lowercaseLetters.size(); // Losuje indeks litery małej
                output = output + lowercaseLetters[letter]; // Dodaje wybraną małą literę do output
            }
        }

        return output; // Zwraca wygenerowane losowe hasło
    }

    bool is_correct_number(const std::string& s) {
        try {
            int num = std::stoi(s); // Konwertuje ciąg znaków na liczbę całkowitą

            if (num < 5 || num > 30) // Sprawdza, czy liczba jest mniejsza niż 5 lub większa niż 30
                return false;
            else
                return true;
        } catch (const std::exception& e) { // Przechwytuje wyjątek, jeśli konwersja nie powiedzie się
            return false;
        }
    }


    void pm::password_storage::add_password_command() {
        std::cout << "\nDlugie losowe hasla sa bezpieczne, czy chcesz wygenerowac haslo?\n";
        std::cout << "(Wpisz Y jezeli tak, cos innego jezeli nie)\n";
        std::string input;
        std::cin >> input;
        std::string password;
        bool isGenerated = false;
        if(input == "Y")
        {
            isGenerated = true;
            int count;
            std::cout << "Ile znakow? (Podaj wartosc w przedziale 5-30)\n";
            do {
                std::cin >> input;
                if(!is_correct_number(input))
                {
                    std::cout << "Niepoprawna ilosc\n";
                }
                else
                {
                    count = std::stoi(input);
                    break;
                }
            } while (true);

            bool big_letters = false;

            std::cout << "\nCzy ma zawierac wielkie litery?\n";
            std::cout << "(Wpisz Y jezeli tak, cos innego jezeli nie)\n";
            std::cin >> input;
            if(input == "Y")
            {
                big_letters = true;
            }

            bool special_characters = false;

            std::cout << "\nCzy ma zawierac znaki specjalne?\n";
            std::cout << "(Wpisz Y jezeli tak, cos innego jezeli nie)\n";
            std::cin >> input;
            if(input == "Y")
            {
                special_characters = true;
            }
            do{
                password = random_passoword(count, big_letters, special_characters);
                std::cout << "\nWygenerowano haslo -  " << password << " - czy chcesz go uzyc?\n";
                std::cout << "(Wpisz Y jezeli tak, cos innego jezeli nie)\n";
                std::cin >> input;
            } while (input != "Y");

        }
        if(!isGenerated)
        {
            while(true) {
                std::cout << "\nPodaj haslo (Dlugosc w przedziale w przedziale 5-30)\n";
                std::cin >> input;
                if(input.length() > 30 || input.length() < 5)
                {
                    std::cout << "Niepoprawna dlugosc hasla\n";
                }
                else
                {
                    password = input;
                    break;
                }

            }
        }
        std::string name;
        std::cout << "\nPodaj nazwe hasla:\n";
        std::cin >> name;
        std::cout << "\nPodaj nazwe kategorii:\n";
        std::cin >> input;
        if(!manager.get_categories().contains(input))
        {
            std::cout << "Dodano nowa kategorie - " << input << "\n";
            manager.add_category(input);
        }

        std::string category = input;
        pm::password_entry entry = password_entry(password, name, category);
        std::cout << "\nCzy chcesz dodac strone www i login?\n";
        std::cout << "(Wpisz Y jezeli tak, cos innego jezeli nie)\n";
        std::cin >> input;
        std::string www;
        std::string login;
        if(input == "Y")
        {
            std::cout << "Podaj nazwe strony www:\n";
            std::cin >> www;
            std::cout << "\nPodaj login:\n";
            std::cin >> login;
            entry.set_login_and_site(login, www);
        }
        password_entries.push_back(entry);
        update_file();
    }

    void pm::password_storage::search_password_command() const {
        for(auto entry : password_entries)
        std::cout << entry.password << "\t" << entry.name << "\t" << entry.category << "\n";
    }

    void pm::password_storage::sort_password_command() const {
        for(auto entry : password_entries)
            std::cout << entry.password << "\t" << entry.name << "\t" << entry.category << "\n";
    }

    void pm::password_storage::remove_password_command() {
        std::cout << "\nPodaj nazwe hasla do usuniecia:\n";
        std::string input;
        std::cin >> input;
        auto newEnd = std::remove_if(password_entries.begin(), password_entries.end(), [input](pm::password_entry num) {
            return num.name == input;
        });
        password_entries.erase(newEnd, password_entries.end());

    }

    void pm::password_storage::edit_password_command() {
            //BRAK
    }

    void pm::password_storage::add_category_command() {
        // Wyświetlenie komunikatu proszącego użytkownika o podanie nazwy kategorii do dodania
        std::cout << "\nPodaj nazwe kategorii do dodania:\n";
        std::string input;
        std::cin >> input;  // Pobranie wprowadzonej nazwy kategorii z wejścia

        // Sprawdzenie, czy podana kategoria nie istnieje już w menedżerze kategorii
        if (!manager.get_categories().contains(input)) {
            // Wyświetlenie komunikatu informującego o dodaniu nowej kategorii
            std::cout << "Dodano nowa kategorie - " << input << "\n";
            // Dodanie nowej kategorii do menedżera kategorii
            manager.add_category(input);
        }

        manager.get_categories();
    }


    void pm::password_storage::remove_category_command() {
        std::cout << "\nPodaj nazwe kategorii do usuniecia:\n";
        std::string input;
        std::cin >> input;

        if(!manager.get_categories().contains(input))
        {
            std::cout << "Usunieto kategorie - " << input << "\n";
            manager.remove_category(input);
        }
    }

}