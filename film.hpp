/**
 * @file film.hpp
 */
 
#ifndef FILM_HPP
#define FILM_HPP
 
#include <iostream>
#include <string>
 
/**
 * @class Film
 * @brief Filmeket leíró absztrakt ősosztály.
 *
 * Tárolja minden filmtípusra vonatkozó közös adatokat.
 */
class Film {
    int id;
    std::string cim;
    int hossz;
    int ev;
public:
 
    /**
     * @brief Film konstruktora az alapvető adatokkal.
     * @param id   Egyedi azonosító (automatikusan generált).
     * @param cim  A film címe (nem üres).
     * @param hossz Lejátszási idő percben (> 0).
     * @param ev   Kiadási év (legfeljebb az aktuális év).
     */
    Film(int id, const std::string& cim, int hossz, int ev);
 
    /**
     * @brief Visszaadja, hogy a film címe tartalmazza-e a megadott részletes stringet.
     * Az összehasonlítás kis- és nagybetű független.
     * @param s A keresett részlet.
     * @return true, ha a cím tartalmazza s-t, egyébként false.
     */
    bool matches(const std::string& s) const;
 
    /**
     * @brief Kiírja a film adatait a megadott folyamra.
     * @param os A kimeneti folyam.
     */
    virtual void print(std::ostream& os) const = 0;
 
    /**
     * @brief CSV formában elmenti a filmet a megadott folyamra.
     * @param os A kimeneti folyam.
     */
    virtual void save(std::ostream& os) const = 0;

    /**
     * @brief Polimorf másoló metódus. Mély másolatot készít a leszármazott objektumról.
     * A visszaadott objektum felszabadítása a hívó felelőssége.
     * @return Mutató az újonnan allokált Film leszármazott példányra.
     */
    virtual Film* clone() const = 0;
 
    /**
     * @brief Két film egyenlőségét id alapján vizsgálja.
     * @param f A másik film.
     * @return true, ha azonos az id, egyébként false.
     */
    bool operator==(const Film& f) const;
 
    /**
     * @brief Visszaadja a film egyedi azonosítóját.
     * @return Az azonosító egész száma.
     */
    int getId() const { return id; };

    /**
     * @brief Visszaadja a film hosszát percben.
     * @return A hossz egész száma.
     */
    int getHossz() const { return hossz; }

    /**
     * @brief Visszaadja a film kiadási évét.
     * @return Az év egész száma.
     */
    int getEv() const { return ev; }
 
    /**
     * @brief Visszaadja a film címét.
     * @return A cím szövege.
     */
    const std::string& getCim() const { return cim; };
 
    /**
     * @brief Virtuális destruktor a helyes polimorf törlés biztosításához.
     */
    virtual ~Film();
};
 
#endif