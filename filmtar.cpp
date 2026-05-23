#include "filmtar.hpp"
#include "csaladi.hpp"
#include "dokumentum.hpp"
#include <fstream>
#include <sstream>

FilmTar::FilmTar() : head(NULL), size(0) {}

void FilmTar::add(Film* f){
    if (head == NULL) {
        head = new LinkedList<Film*>(f);
    } else {
        LinkedList<Film*>* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new LinkedList<Film*>(f);
    }
    size++;
}

void FilmTar::removeById(int id){
    if (head == NULL) return;

    if (head->data->getId() == id) {
        LinkedList<Film*>* toDelete = head;
        head = head->next;
        toDelete->next = NULL;
        delete toDelete->data;
        delete toDelete;
        size--;
        return;
    }

    LinkedList<Film*>* current = head;
    while (current->next != NULL) {
        if (current->next->data->getId() == id) {
            LinkedList<Film*>* toDelete = current->next;
            current->next = toDelete->next;
            toDelete->next = NULL;
            delete toDelete->data;
            delete toDelete;
            size--;
            return;
        }
        current = current->next;
    }
}

FilmTar* FilmTar::findByTitle(const std::string& s) const{
    FilmTar* result = new FilmTar();
    LinkedList<Film*>* current = head;
    while (current != NULL) {
        if (current->data->matches(s)) {
            result->add(current->data);
        }
        current = current->next;
    }
    return result;
}

Film* FilmTar::operator[](int i) const{
    LinkedList<Film*>* current = head;
    for (int j = 0; j < i; j++) {
        if (current == NULL) return NULL;
        current = current->next;
    }
    return current->data;
}

std::ostream& operator<<(std::ostream& os, const FilmTar& ft){
    LinkedList<Film*>* current = ft.head;
    while (current != NULL) {
        current->data->print(os);
        current = current->next;
    }
    return os;
}

FilmTar FilmTar::loadFromCSV(const std::string& file) {
    FilmTar tar;
    std::ifstream f(file.c_str());

    if (!f.is_open()) {
        // Ha nem létezik, létrehozzuk és visszaadunk egy üres tárat
        std::ofstream letrehoz(file.c_str());
        return tar;
    }

    std::string sor;
    while (getline(f, sor)) {
        if (sor.empty()) continue;

        std::stringstream ss(sor);
        std::string token;

        // Típus
        getline(ss, token, ';');
        int tipus = atoi(token.c_str());

        // ID
        getline(ss, token, ';');
        int id = atoi(token.c_str());

        // Cím
        std::string cim;
        getline(ss, cim, ';');

        // Hossz
        getline(ss, token, ';');
        int hossz = atoi(token.c_str());

        // Év
        getline(ss, token, ';');
        int ev = atoi(token.c_str());

        if (tipus == 0) {
            // Korhatár
            getline(ss, token, ';');
            int korhatar = atoi(token.c_str());
            tar.add(new Csaladi(id, cim, hossz, ev, korhatar));
        } else {
            // Leírás (maradék az egész, hogy a ; is beleférjen)
            std::string leiras;
            getline(ss, leiras);
            tar.add(new Dokumentum(id, cim, hossz, ev, leiras));
        }
    }

    return tar;
}

FilmTar::~FilmTar(){
    LinkedList<Film*>* current = head;
    while (current != NULL) {
        LinkedList<Film*>* next = current->next;
        delete current->data;
        current->next = NULL;
        delete current;
        current = next;
    }
}