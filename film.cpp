#include "film.hpp"
#include <string>
#include <iostream>

Film::Film(int id, const std::string& cim, int hossz, int ev) : id(id), cim(cim), hossz(hossz), ev(ev) {}

bool Film::matches(const std::string& s) const{
    std::string cimLower = cim;
    std::string sLower = s;

    for (size_t i = 0; i < cimLower.size(); i++)
        cimLower[i] = tolower(cimLower[i]);

    for (size_t i = 0; i < sLower.size(); i++)
        sLower[i] = tolower(sLower[i]);
        
    return cimLower.find(sLower) != std::string::npos;
}

bool Film::operator==(const Film& f) const{
    return id == f.id;
}

Film::~Film() {}