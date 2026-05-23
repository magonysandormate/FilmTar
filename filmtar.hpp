/**
 * @file filmtar.hpp
 */
 
#ifndef FILMTAR_HPP
#define FILMTAR_HPP
 
#include "list.hpp"
#include "film.hpp"
#include <string>
 
/**
 * @class FilmTar
 * @brief Heterogén filmgyűjtemény tárolására és kezelésére szolgáló osztály.
 * A LinkedList adatszerkezeten keresztül Film mutatókat tárol,
 * amik mögött Csaladi vagy Dokumentum példányok állnak.
 * Az összes gyűjteményszintű műveletért ez az osztály felel.
 */
class FilmTar {
    LinkedList<Film*>* head;
    int size;

    friend std::ostream& operator<<(std::ostream& os, const FilmTar& ft);
public:
 
    /**
     * @brief FilmTar alapértelmezett konstruktora.
     * Üres gyűjteményt hoz létre (head = NULL, size = 0).
     */
    FilmTar();
 
    /**
     * @brief Új filmet fűz a lista végére.
     * @param f Mutató a hozzáadandó Film objektumra.
     *          A FilmTar nem veszi át az objektum tulajdonjogát.
     */
    void add(Film* f);
 
    /**
     * @brief Megkeresi és eltávolítja az adott azonosítójú filmet.
     * Kiveszi a filmet a láncolt listából, és felszabadítja
     * a Film objektumot és a listaelemet.
     * A size értékét eggyel csökkenti.
     * @param id Az eltávolítandó film egyedi azonosítója.
     */
    void removeById(int id);
 
    /**
     * @brief Cím alapján megkeresi az egyező filmeket.
     * Minden elemre meghívja a Film::matches() metódust,
     * és az egyező mutatókat átmásolja egy új, heap-en
     * allokált FilmTar objektumba (klónozás nélkül).
     * @param s A keresett cím vagy annak részlete.
     * @return Mutató az egyező filmeket tartalmazó új FilmTar-ra.
     *         A visszakapott objektum felszabadítása a hívó felelőssége.
     */
    FilmTar* findByTitle(const std::string& s) const;
 
    /**
     * @brief Visszaadja az adott indexű film mutatóját.
     * @param i A kért index (0-tól).
     * @return Mutató a megfelelő Film objektumra.
     * @throws std::out_of_range Ha az index érvénytelen.
     */
    Film* operator[](int i) const;
 
    /**
     * @brief CSV fájlból betölti a filmeket és visszaad egy feltöltött FilmTar-t.
     * Ha a fájl nem létezik, létrehozza, és üres FilmTar-t ad vissza.
     * Soronként beolvassa az adatokat, a típusazonosító alapján
     * (0: Csaladi, 1: Dokumentum) példányosítja a megfelelő leszármazottat,
     * és hozzáadja a gyűjteményhez.
     * @param file A CSV fájl elérési útja.
     * @return A feltöltött FilmTar objektum.
     */
    static FilmTar loadFromCSV(const std::string& file);
 
    /**
     * @brief Visszaadja a gyűjteményben tárolt filmek számát.
     * @return A filmek száma.
     */
    int getSize() const { return size; }
 
    /**
     * @brief Destruktor, felszabadítja a teljes láncolt listát és a Film objektumokat.
     */
    ~FilmTar();
};
 
/**
 * @brief Kiírja a FilmTar összes filmjét a megadott folyamra.
 * Minden elemre meghívja a film->print(os) metódust.
 * @param os A kimeneti folyam.
 * @param ft A kiírandó FilmTar objektum.
 * @return Referencia a kimeneti folyamra (láncolhatóság érdekében).
 */
std::ostream& operator<<(std::ostream& os, const FilmTar& ft);
 
#endif