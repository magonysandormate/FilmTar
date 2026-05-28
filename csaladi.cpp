#include "csaladi.hpp"
#include <string>
#include <iostream>

Csaladi::Csaladi(int id, const std::string& cim, int hossz, int ev, int korhatar) : Film(id, cim, hossz, ev), korhatar(korhatar) {}

void Csaladi::print(std::ostream& os) const{
    os << getId() << " | Csaladi | " << getCim() << " (" << getEv() << ") | " << getHossz() << " perc | " << korhatar << "+" << std::endl;
}

void Csaladi::save(std::ostream& os) const{
    os << "0;" << getId() << ";" << getCim() << ";" << getHossz() << ";" << getEv() << ";" << korhatar << std::endl;
}

Csaladi::~Csaladi(){}