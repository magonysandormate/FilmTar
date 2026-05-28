#include "input.hpp"
#include "csaladi.hpp"
#include "dokumentum.hpp"
#include <string>
#include <iostream>

int InputHandler::readInt(std::istream& is, std::ostream& os){
    int n;
    while (!(is >> n)) {
        is.clear();
        is.ignore(1000, '\n');
        os << "Ervenytelen szam, probalja ujra: ";
    }
    return n;
}

std::string InputHandler::readString(std::istream& is, std::ostream& os){
    std::string s;
    while (getline(is, s) && s.empty()) {
        os << "Nem lehet ures, probalja ujra: ";
    }
    return s;
}

Film* InputHandler::readFilm(std::istream& is, std::ostream& os, int nextId){
    os << "Tipus (0 = Csaladi, 1 = Dokumentum): ";
    int tipus = readInt(is, os);
    while (tipus != 0 && tipus != 1) {
        os << "Ervenytelen tipus (0 vagy 1): ";
        tipus = readInt(is, os);
    }
 
    int id = nextId;
 
    os << "Cim: ";
    is.ignore(1000, '\n');
    std::string cim = readString(is, os);
 
    os << "Hossz (perc): ";
    int hossz = readInt(is, os);
    while (hossz <= 0) {
        os << "A hossz pozitiv kell legyen: ";
        hossz = readInt(is, os);
    }
 
    os << "Kiadasi ev: ";
    int ev = readInt(is, os);
 
    if (tipus == 0) {
        os << "Korhatar (0-18): ";
        int korhatar = readInt(is, os);
        while (korhatar < 0 || korhatar > 18) {
            os << "Ervenytelen korhatar (0-18): ";
            korhatar = readInt(is, os);
        }
        return new Csaladi(id, cim, hossz, ev, korhatar);
    } else {
        os << "Leiras: ";
        is.ignore(1000, '\n');
        std::string leiras = readString(is, os);
        return new Dokumentum(id, cim, hossz, ev, leiras);
    }
}