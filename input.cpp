#include "input.hpp"
#include "csaladi.hpp"
#include "dokumentum.hpp"
#include <string>
#include <iostream>

//Egész számok beolvasását validála
int readInt(std::istream& is){
    int n;
    while (!(is >> n)) {
        is.clear();
        is.ignore(1000, '\n');
        std::cout << "Érvénytelen szám, próbáld újra: ";
    }
    return n;
}

//Karakterláncok beolvasását validála
std::string readString(std::istream& is){
    std::string s;
    while (getline(is, s) && s.empty()) {
        std::cout << "Nem lehet üres, próbáld újra: ";
    }
    return s;
}

//Bekéri a felhasználótól a filmekhez tartozó adatokat
Film* InputHandler::readFilm(std::istream& is){
    std::cout << "Típus (0 = Családi, 1 = Dokumentum): ";
    int tipus = readInt(is);

    std::cout << "ID: ";
    int id = readInt(is);

    std::cout << "Cím: ";
    is.ignore();
    std::string cim = readString(is);

    std::cout << "Hossz (perc): ";
    int hossz = readInt(is);

    std::cout << "Év: ";
    int ev = readInt(is);

    if (tipus == 0) {
        std::cout << "Korhatár: ";
        int korhatar = readInt(is);
        return new Csaladi(id, cim, hossz, ev, korhatar);
    } else {
        std::cout << "Leírás: ";
        is.ignore();
        std::string leiras = readString(is);
        return new Dokumentum(id, cim, hossz, ev, leiras);
    }
}