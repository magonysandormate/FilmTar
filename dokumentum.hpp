/**
 * @file dokumentum.hpp
 */
 
#ifndef DOKUMENTUM_HPP
#define DOKUMENTUM_HPP
 
#include "film.hpp"
 
/**
 * @class Dokumentum
 * @brief Szöveges leírással rendelkező dokumentumfilmek osztálya.
 * A Film leszármazottja, az örökölt adatokon kívül
 * tárolja a dokumentumfilm rövid leírását.
 */
class Dokumentum : public Film {
    std::string leiras;
public:
 
    /**
     * @brief Dokumentum konstruktora az alapvető és a típusspecifikus adatokkal.
     * @param id     Egyedi azonosító.
     * @param cim    A film címe (nem üres).
     * @param hossz  Lejátszási idő percben (> 0).
     * @param ev     Kiadási év (legfeljebb az aktuális év).
     * @param leiras A dokumentumfilm rövid leírása (nem üres).
     */
    Dokumentum(int id, const std::string& cim, int hossz, int ev, const std::string& leiras);
 
    /**
     * @brief Jól olvasható formában kiírja a dokumentumfilm adatait a megadott folyamra.
     * Formátum: [ID] | [TÍPUS] | Cím (Év) | [HOSSZ] perc | [LEÍRÁS]
     * @param os A kimeneti folyam.
     */
    void print(std::ostream& os) const override;
 
    /**
     * @brief CSV formában elmenti a filmet a megadott folyamra.
     * Formátum: 1;ID;CÍM;HOSSZ;KIADÁSI_ÉV;LEÍRÁS
     * @param os A kimeneti folyam.
     */
    void save(std::ostream& os) const override;
 
    /**
     * @brief Visszaadja a dokumentumfilm leírását.
     * @return A leírást tartalmazó szöveg.
     */
    const std::string& getLeiras() const { return leiras; }
 
    /**
     * @brief Destruktor.
     */
    ~Dokumentum();
};
 
#endif