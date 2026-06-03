#include "filmtar.hpp"
#include "csaladi.hpp"
#include "dokumentum.hpp"
#include "input.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

FilmTar::FilmTar() : head(NULL), size(0), owner(true), maxId(0) {}
FilmTar::FilmTar(bool own) : head(NULL), size(0), owner(own), maxId(0) {}

FilmTar::FilmTar(const FilmTar& other) : head(NULL), size(0), owner(true), maxId(other.maxId) {
    LinkedList<Film*>* current = other.head;
    while (current != NULL) {
        this->add(current->data->clone());
        current = current->next;
    }
}

FilmTar& FilmTar::operator=(const FilmTar& other) {
    if (this != &other) {
        LinkedList<Film*>* current = head;
        while (current != NULL) {
            LinkedList<Film*>* next = current->next;
            if (owner) delete current->data;
            delete current;
            current = next;
        }
        head = NULL;
        size = 0;
        owner = true;
        maxId = other.maxId;

        LinkedList<Film*>* src = other.head;
        while (src != NULL) {
            this->add(src->data->clone());
            src = src->next;
        }
    }
    return *this;
}

void FilmTar::add(Film* f){
    if (head == NULL) {
        head = new LinkedList<Film*>(f);
    } else {
        LinkedList<Film*>* current = head;
        while (current->next != NULL) current = current->next;
        current->next = new LinkedList<Film*>(f);
    }
    size++;

    if(f->getId() > maxId){
        maxId = f->getId();
    }
}

void FilmTar::removeById(int id){
    if (head == NULL) return;
    if (head->data->getId() == id) {
        LinkedList<Film*>* toDelete = head;
        head = head->next;
        toDelete->next = NULL;
        if (owner) delete toDelete->data;
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
            if (owner) delete toDelete->data;
            delete toDelete;
            size--;
            return;
        }
        current = current->next;
    }
}

FilmTar* FilmTar::findByTitle(const std::string& s) const{
    FilmTar* result = new FilmTar(false); // nem tulajdonos
    LinkedList<Film*>* current = head;
    while (current != NULL) {
        if (current->data->matches(s)) result->add(current->data);
        current = current->next;
    }
    return result;
}

const Film* FilmTar::operator[](int i) const {
    if (i < 0 || i >= size) throw std::out_of_range("Index out of range");
    LinkedList<Film*>* current = head;
    for (int j = 0; j < i; j++) current = current->next;
    return current->data;
}

Film* FilmTar::operator[](int i) {
    if (i < 0 || i >= size) throw std::out_of_range("Index out of range");
    LinkedList<Film*>* current = head;
    for (int j = 0; j < i; j++) current = current->next;
    return current->data;
}

std::ostream& operator<<(std::ostream& os, const FilmTar& ft) {
    if (ft.head == NULL) return os;
    for (auto it = ft.head->begin(); it != ft.head->end(); ++it)
        (*it)->print(os);
    return os;
}

FilmTar* FilmTar::loadFromCSV(const std::string& file) {
    FilmTar* tar = new FilmTar();
    std::ifstream f(file.c_str());
    if (!f.is_open()) {
        std::cerr << "Figyelmezetes: '" << file << "' nem talalhato, ures tarral indul." << std::endl;
        return tar;
    }
    std::string sor;
    while (getline(f, sor)) {
        if (sor.empty()) continue;
        std::stringstream ss(sor);
        std::string token;
        getline(ss, token, ';'); int tipus = atoi(token.c_str());
        getline(ss, token, ';'); int id = atoi(token.c_str());
        std::string cim; getline(ss, cim, ';');
        getline(ss, token, ';'); int hossz = atoi(token.c_str());
        getline(ss, token, ';'); int ev = atoi(token.c_str());
        std::string extra;
        if(tipus == 0){
            getline(ss, token, ';');
            extra = token;
        } else{
            getline(ss, extra);
        }

        // hossz validáció
        if (hossz <= 0) {
            std::cerr << "Figyelmezetes: ervénytelen hossz (" << hossz
                    << ") a(z) '" << cim << "' filmnel, kihagyva." << std::endl;
            continue;
        }

        // korhatar validáció Csaladi esetén
        if (tipus == 0) {
            int k = atoi(extra.c_str());
            if (k < 0 || k > 18) {
                std::cerr << "Figyelmezetes: ervénytelen korhatar (" << k
                        << ") a(z) '" << cim << "' filmnel, kihagyva." << std::endl;
                continue;
            }
        }

        tar->add(InputHandler::createFilm(tipus, id, cim, hossz, ev, extra));
    }

    return tar;
}

void FilmTar::saveToCSV(const std::string& file) const {
    std::ofstream f(file.c_str());
    if (!f.is_open()) throw std::runtime_error("Nem sikerult megnyitni a fajlt menteshez.");
    if (head != NULL){
        for(auto it = head->begin(); it != head->end(); ++it){
            (*it)->save(f);
        }
    }
}

FilmTar::~FilmTar(){
    LinkedList<Film*>* current = head;
    while (current != NULL) {
        LinkedList<Film*>* next = current->next;
        if (owner) delete current->data;
        current->next = NULL;
        delete current;
        current = next;
    }
}