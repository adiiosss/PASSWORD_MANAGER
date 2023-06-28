#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "password_storage.h" // dostepnosc password_storage.h

/**
 * @brief Main function of the password manager program.
 *
 * This function allows the user to select or create a file for password management.
 */

int main() {

    std::cout << "\n==========| MENADZER HASEL |==========\n";

    std::cout << "\nWybierz plik! - wpisz nazwe pliku z obecnego folderu, pelna sciezke lub nazwe nowego pliku do stworzenia.\n" <<
              "\nWpisz 'exit', aby wyjsc z programu.\n" <<
              "\nPliki w obecnym folderze:\n";

    std::vector<std::string> files = std::vector<std::string>();
    for(auto entry : std::filesystem::directory_iterator("./")) { // Pobieranie wszystkich plików w bieżącym folderze
        if(!entry.is_directory())
            files.push_back(entry.path().filename().string()); // Dodawanie nazwy pliku do wektora files
    }
    for(auto file : files)
        std::cout << file << "\t"; // Wyświetlanie nazw plików w folderze
    std::cout << "\n";

    std::string input;
    std::cin >> input; // Wczytywanie wprowadzonego przez użytkownika tekstu do zmiennej input

    if(input == "exit")
        return 0; // Jeśli użytkownik wpisał "exit", program kończy działanie

    /**
     * Wybór lub tworzenie pliku
     */

    if(std::find(files.begin(), files.end(), input) != files.end()) { // Sprawdzanie, czy podany plik znajduje się na liście dostępnych plików
        std::cout << "\nWybrano plik " << input << " z obecnego folderu\n";
        pm::password_storage::initialize(input); // Inicjalizacja klasy password_storage, przekazując nazwę pliku jako argument
    }
    else {
        if(std::filesystem::exists(input) && !std::filesystem::is_directory(input)) { // Sprawdzanie, czy podana ścieżka prowadzi do istniejącego pliku (nie jest katalogiem)
            std::cout << "\nWybrano plik " << std::filesystem::path(input).filename().string() << " z folderu " << std::filesystem::path(input).parent_path().string() << "\\\n";
            pm::password_storage::initialize(input); // Inicjalizacja klasy password_storage, przekazując ścieżkę pliku jako argument
        }
        else {
            std::cout << "\nStworzono plik o nazwie " << input << "\n";
            pm::password_storage::generate(input); // Generowanie pliku za pomocą klasy password_storage, przekazując nazwę pliku jako argument
        }
    }

    return 0;
}
