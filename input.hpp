/**
 * @file input.hpp
 */
 
#ifndef INPUT_HPP
#define INPUT_HPP
 
#include "film.hpp"
#include <iostream>
#include <string>
 
/**
 * @class InputHandler
 * @brief A konzolos felhasználói bemenet beolvasásáért és validációjáért felelős osztály.
 * Hibás bemenet esetén hibaüzenetet jelenít meg, majd újra bekéri az adatot,
 * egészen addig, amíg érvényes értéket nem kap.
 */
class InputHandler {
public:
    /**
     * @brief Egész számot olvas és validál a megadott folyamról.
     * Addig ismétli a bekérést, amíg valós numerikus értéket nem kap.
     * @param is A bemeneti folyam.
     * @return A beolvasott egész szám.
     */
    static int readInt(std::istream& is, std::ostream& os);
 
    /**
     * @brief Szöveget olvas és validál a megadott folyamról.
     * Addig ismétli a bekérést, amíg nem üres stringet nem kap.
     * @param is A bemeneti folyam.
     * @return A beolvasott, nem üres szöveg.
     */
    static std::string readString(std::istream& is, std::ostream& os);

    /**
     * @brief Interaktívan beolvassa egy film adatait a megadott folyamról.
     * Bekéri a típust, majd az ahhoz szükséges összes adatmezőt validálással.
     * Heap-en allokált Film mutatót ad vissza, a visszakapott objektum
     * felszabadítása a hívó felelőssége.
     * @param is A bemeneti folyam.
     * @return Mutató az újonnan létrehozott Film objektumra.
     */
    static Film* readFilm(std::istream& is, std::ostream& os, int nextId);

    /**
     * @brief Típuskód alapján létrehoz egy Film leszármazott objektumot.
     * Heap-en allokált Film mutatót ad vissza, a visszakapott objektum
     * felszabadítása a hívó felelőssége.
     * @param tipus  A film típusa (0 = Csaladi, 1 = Dokumentum).
     * @param id     Egyedi azonosító.
     * @param cim    A film címe.
     * @param hossz  Lejátszási idő percben.
     * @param ev     Kiadási év.
     * @param extra  Típusfüggő adat: Csaladi esetén a korhatár stringként, Dokumentum esetén a leírás.
     * @return Mutató az újonnan létrehozott Film objektumra.
     */
    static Film* createFilm(int tipus, int id, const std::string& cim, int hossz, int ev, const std::string& extra);
};
 
#endif