/**
 * @file list.hpp
 */
 
#ifndef LIST_HPP
#define LIST_HPP
 
#include <iostream>

class FilmTar;
std::ostream& operator<<(std::ostream& os, const FilmTar& ft);
 
/**
 * @class LinkedList
 * @brief Egyirányú, sablonos láncolt lista adatszerkezet.
 * Minden listaelem tárolja az adatát és mutatót a következő elemre.
 * Az utolsó elem next mutatója NULL.
 * @tparam T A listában tárolt elemek típusa.
 */
template <typename T>
class LinkedList {
    T data;
    LinkedList<T>* next;

    friend class FilmTar;
    friend std::ostream& operator<<(std::ostream& os, const FilmTar& ft);
public:
 
    /**
     * @brief LinkedList konstruktora egy adattal.
     * @param data Az elemben tárolandó adat.
     */
    LinkedList(const T& data);
 
    /**
     * @class Iterator
     * @brief Belső iterátor osztály a lista elemeinek bejárásához.
     * Lehetővé teszi a lista elemeinek elérését anélkül, hogy
     * a hívó közvetlenül kezelné a mutatókat.
     */
    class Iterator {
        LinkedList<T>* current;
    public:
        /**
         * @brief Iterator konstruktora egy listaelemre mutató pointerrel.
         * @param ptr Mutató az aktuális listaelemre.
         */
        Iterator(LinkedList<T>* ptr);
 
        /**
         * @brief Előre lépteti az iterátort a következő elemre.
         * @return Referencia az előreléptetett iterátorra.
         */
        Iterator& operator++();
 
        /**
         * @brief Visszaadja az aktuális elemben tárolt adatot.
         * @return Az aktuális adat.
         */
        T operator*();
 
        /**
         * @brief Két iterátor egyenlőtlenségét vizsgálja a belső mutató alapján.
         * @param other A másik iterátor.
         * @return true, ha a két iterátor különböző elemre mutat.
         */
        bool operator!=(const Iterator& other) const;
    };
 
    /**
     * @brief Visszaadja a lista első elemére mutató iterátort.
     * @return Az első elemre mutató Iterator objektum.
     */
    Iterator begin();
 
    /**
     * @brief Visszaadja a lista végét jelző (NULL) iterátort.
     * @return A lista végét jelző Iterator objektum.
     */
    Iterator end();
 
    /**
     * @brief Destruktor, felszabadítja az összes listaelemet.
     */
    ~LinkedList();
};

#include "list.tpp"
 
#endif