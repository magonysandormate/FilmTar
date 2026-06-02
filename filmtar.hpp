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
    bool owner; ///true -> destruktor törli a Film* objektumokat
    int maxId;
    friend std::ostream& operator<<(std::ostream& os, const FilmTar& ft);
 
    FilmTar(bool owner);  ///belső konstruktor, nem tulajdonos tárakhoz
 
public:
    /**
     * @brief Alapértelmezett konstruktor. A tar tulajdonosa lesz a filmeknek.
     */
    FilmTar();

    /**
     * @brief Másoló konstruktor. Új tárolót hoz létre, ami nem lesz tulajdonosa a filmeknek.
     * Átveszi az eredeti tároló méretét és a számozáshoz szükséges legmagasabb ID azonosítót.
     * @param other A másolandó FilmTar objektum referenciája.
     */
    FilmTar(const FilmTar&);

    /**
     * @brief Értékadó operátor. Másolatot készít egy létező tárolóról.
     * Lemásolja a belső állapotot és az ID sorszámozás aktuális állását.
     * @param other A másolandó FilmTar objektum referenciája.
     * @return Referencia az aktuális (módosított) FilmTar objektumra.
     */
    FilmTar& operator=(const FilmTar&);
 
    /**
     * @brief Új filmet fűz a lista végére.
     * @param f Mutató a hozzáadandó Film objektumra.
     */
    void add(Film* f);
 
    /**
     * @brief Megkeresi és eltávolítja az adott azonosítójú filmet.
     * @param id Az eltávolítandó film egyedi azonosítója.
     */
    void removeById(int id);
 
    /**
     * @brief Cím alapján megkeresi az egyező filmeket.
     * A visszaadott FilmTar NEM tulajdonosa a mutatóknak (nem törli őket).
     * @param s A keresett cím vagy annak részlete.
     * @return Mutató az egyező filmeket tartalmazó új FilmTar-ra.
     */
    FilmTar* findByTitle(const std::string& s) const;
 
    /**
     * @brief Visszaadja az adott indexű film mutatóját.
     * @param i A kért index (0-tól).
     * @return Mutató a megfelelő Film objektumra.
     * @throws std::out_of_range Ha az index érvénytelen.
     */
    Film* operator[](int i);

    const Film* operator[](int i) const;
 
    /**
     * @brief CSV fájlból betölti a filmeket (heap-en allokált FilmTar).
     * @param file A CSV fájl elérési útja.
     * @return Mutató a feltöltött FilmTar objektumra.
     */
    static FilmTar* loadFromCSV(const std::string& file);
 
    /**
     * @brief CSV fájlba menti az összes filmet.
     * @param file A CSV fájl elérési útja.
     */
    void saveToCSV(const std::string& file) const;
 
    /**
     * @brief Visszaadja a gyűjteményben tárolt filmek számát.
     */
    int getSize() const { return size; }

    int getNextId() const { return maxId + 1; }
 
    /**
     * @brief Destruktor, felszabadítja a láncolt listát és (ha owner) a Film objektumokat.
     */
    ~FilmTar();
};
 
/**
 * @brief Globális inserter operátor a filmtár tartalmának kiírására.
 * Sorban meghívja a gyűjteményben lévő összes film saját print() függvényét.
 * @param os A kimeneti adatfolyam.
 * @param ft A kiírandó filmtár objektum.
 * @return Referencia a kimeneti adatfolyamra.
 */
std::ostream& operator<<(std::ostream& os, const FilmTar& ft);
 
#endif