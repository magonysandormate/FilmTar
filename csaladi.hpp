/**
 * @file csaladi.hpp
 */
 
#ifndef CSALADI_HPP
#define CSALADI_HPP
 
#include "film.hpp"
 
/**
 * @class Csaladi
 * @brief Korhatárral rendelkező családi filmek osztálya.
 *
 * A Film leszármazottja, az örökölt adatokon kívül
 * tárolja a korhatár értékét (0–18).
 */
class Csaladi : public Film {
    int korhatar;
public:
 
    /**
     * @brief Csaladi konstruktora az alapvető és a típusspecifikus adatokkal.
     * @param id       Egyedi azonosító.
     * @param cim      A film címe (nem üres).
     * @param hossz    Lejátszási idő percben (> 0).
     * @param ev       Kiadási év (legfeljebb az aktuális év).
     * @param korhatar Korhatár értéke (0 <= korhatar <= 18).
     */
    Csaladi(int id, const std::string& cim, int hossz, int ev, int korhatar);
 
    /**
     * @brief Jól olvasható formában kiírja a családi film adatait a megadott folyamra.
     * Formátum: [ID] | [TÍPUS] | Cím (Év) | [HOSSZ] perc | [KORHATÁR]
     * @param os A kimeneti folyam.
     */
    void print(std::ostream& os) const override;
 
    /**
     * @brief CSV formában elmenti a filmet a megadott folyamra.
     * Formátum: 0;ID;CÍM;HOSSZ;KIADÁSI_ÉV;KORHATÁR
     * @param os A kimeneti folyam.
     */
    void save(std::ostream& os) const override;

    /**
     * @brief Mély másolatot készít a Csaladi objektumról.
     * @return Mutató az újonnan allokált Csaladi példányra.
     */
    Csaladi* clone() const override;
 
    /**
     * @brief Visszaadja a családi film korhatárát.
     * @return A korhatár értéke (0–18).
     */
    int getKorhatar() const { return korhatar; }
 
    /**
     * @brief Destruktor.
     */
    ~Csaladi();
};
 
#endif