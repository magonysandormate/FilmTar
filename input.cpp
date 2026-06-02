#include "input.hpp"
#include "csaladi.hpp"
#include "dokumentum.hpp"
#include <string>
#include <iostream>
#include <limits>

int InputHandler::readInt(std::istream& is, std::ostream& os){
    int n;
    while (!(is >> n)) {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

Film* InputHandler::createFilm(int tipus, int id, const std::string& cim, int hossz, int ev, const std::string& extra) {
    if (tipus == 0){
        return new Csaladi(id, cim, hossz, ev, atoi(extra.c_str()));
    }
    return new Dokumentum(id, cim, hossz, ev, extra);
}

Film* InputHandler::readFilm(std::istream& is, std::ostream& os, int nextId) {
    os << "Tipus (0 = Csaladi, 1 = Dokumentum): ";
    int tipus = readInt(is, os);
    while (tipus != 0 && tipus != 1) {
        os << "Ervenytelen tipus (0 vagy 1): ";
        tipus = readInt(is, os);
    }
    os << "Cim: ";
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string cim = readString(is, os);
    os << "Hossz (perc): ";
    int hossz = readInt(is, os);
    while (hossz <= 0) {
        os << "A hossz pozitiv kell legyen: ";
        hossz = readInt(is, os);
    }
    os << "Kiadasi ev: ";
    int ev = readInt(is, os);

    std::string extra;
    if (tipus == 0) {
        os << "Korhatar (0-18): ";
        int korhatar = readInt(is, os);
        while (korhatar < 0 || korhatar > 18) {
            os << "Ervenytelen korhatar (0-18): ";
            korhatar = readInt(is, os);
        }
        extra = std::to_string(korhatar);
    } else {
        os << "Leiras: ";
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        extra = readString(is, os);
    }
    return createFilm(tipus, nextId, cim, hossz, ev, extra);
}