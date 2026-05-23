#include "dokumentum.hpp"
#include <string>
#include <iostream>

Dokumentum::Dokumentum(int id, const std::string& cim, int hossz, int ev, const std::string& leiras) : Film(id, cim, hossz, ev), leiras(leiras) {}

void Dokumentum::print(std::ostream& os) const{
    os << getId() << " | Dokumentum | " << getCim() << " (" << getEv() << ") | " << getHossz() << " perc | " << leiras << std::endl;
}

void Dokumentum::save(std::ostream& os) const{
    os << "1;" << getId() << ";" << getCim() << ";" << getHossz() << ";" << getEv() << ";" << leiras << std::endl;
}