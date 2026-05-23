/**
 * @file teszt.cpp
 * @brief Tesztprogram a FilmTar rendszer osztályainak együttműködéséhez.
 *
 * Bemutatja az összes főbb osztály kapcsolatát és az elvégzendő
 * műveletek vezérlési folyamatát.
 */

#include "film.hpp"
#include "csaladi.hpp"
#include "dokumentum.hpp"
#include "filmtar.hpp"
#include "input.hpp"
#include "list.hpp"
#include <iostream>
#include <string>

//Segédfüggvények a menühöz
/**
 * @brief Kiírja a főmenü opcióit a standard kimenetre.
 */
void menuKiir();

/**
 * @brief Beolvassa a felhasználó menüválasztását.
 * @return A kiválasztott menüpont sorszáma.
 */
int menuValaszt();

/**
 * @brief Új filmet kér be a felhasználótól és hozzáadja a gyűjteményhez.
 * @param tar   A gyűjtemény, amelybe az új film kerül.
 * @param input A bevitelt kezelő objektum.
 */
void ujFilmHozzaad(FilmTar& tar, InputHandler& input);

//Segédfüggvények implementációja (vázlat)
void menuKiir(){

}
 
int menuValaszt(){
    return 0;
}
 
void ujFilmHozzaad(FilmTar& tar, InputHandler& input){

}

int main() {
    const std::string fajl = "filmek.txt";
 
    // Gyűjtemény betöltése CSV fájlból
    FilmTar tar = FilmTar::loadFromCSV(fajl);
 
    // Beviteli kezelő példányosítása
    InputHandler input;
 
    // Néhány film kézi hozzáadása a kapcsolatok bemutatásához
    Csaladi* cs = new Csaladi(1, "Toy Story", 81, 1995, 6);
    Dokumentum* dok = new Dokumentum(2, "Bolygónk, a Föld", 50, 2006, "BBC természetfilm-sorozat");
 
    tar.add(cs);
    tar.add(dok);
 
    // Polimorf kiírás az operator<< segítségével
    std::cout << tar;
 
    // Keresés cím alapján
    FilmTar* talalatok = tar.findByTitle("Toy");
    std::cout << *talalatok;
    delete talalatok;
 
    // Indexelés operátorral
    Film* elso = tar[0];
    elso->print(std::cout);
 
    // Törlés azonosító alapján
    tar.removeById(1);
 
    // Főmenü vezérlési ciklus
    int valasztas = 0;
    do {
        menuKiir();
        valasztas = menuValaszt();
 
        switch (valasztas) {
            case 1:
                ujFilmHozzaad(tar, input);
                break;
            case 2: {
                std::string keresett;
                std::cin >> keresett;
                FilmTar* talalatok = tar.findByTitle(keresett);
                std::cout << *talalatok;
                delete talalatok;
                break;
            }
            case 3: {
                int id;
                std::cin >> id;
                tar.removeById(id);
                break;
            }
            case 4:
                std::cout << tar;
                break;
            case 0:
                break;
            default:
                std::cout << "Érvénytelen választás." << std::endl;
        }
    } while (valasztas != 0);
 
    return 0;
}