/**
 * @file main.cpp
 * @brief FilmTár konzolalkalmazás – interaktív főmenü.
 *
 * Menüpontok:
 *   1. Új film felvétele   (validált bekérés)
 *   2. Film törlése        (id alapján, megerősítéssel)
 *   3. Filmek listázása    (összes film)
 *   4. Film keresése       (cím-részlet alapján)
 *   0. Kilépés + mentés
 *
 * Az adatok fájlba mentése a kilépéskor és SIGINT/SIGTERM esetén is megtörténik.
 */

#include "filmtar.hpp"
#include "input.hpp"
#include <iostream>
#include <string>
#include <csignal>
#include <cstdlib>

#ifndef CPORTA

static const std::string ADATFAJL = "filmek.txt";
static FilmTar* globalTar = NULL;

// Mentés kilépéskor (atexit + signal handler)
static void mentes() {
    if (globalTar != NULL) {
        try {
            globalTar->saveToCSV(ADATFAJL);
            std::cout << "\nAdatok mentve: " << ADATFAJL << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Mentési hiba: " << e.what() << std::endl;
        }
    }
}

static void signalHandler(int) {
    mentes();
    globalTar = NULL;
    std::exit(0);
}


// Menü segédfüggvények
static void menuKiir() {
    std::cout << "\n=== FILMTAR ===\n"
              << "1. Uj film felvetele\n"
              << "2. Film torlese\n"
              << "3. Filmek listazasa\n"
              << "4. Film keresese cim alapjan\n"
              << "0. Kilepes (es mentes)\n"
              << "Valasztas: ";
}

static int bekerValasztas() {
    int v = 0;
    while (!(std::cin >> v)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Szam kell: ";
    }
    return v;
}

// Menüpontok implementációja
static void ujFilm(FilmTar& tar) {
    std::cout << "\n-- Uj film felvetele --\n";
    Film* f = InputHandler::readFilm(std::cin, std::cout, tar.getNextId());
    tar.add(f);
    std::cout << "Film hozzaadva (ID: " << f->getId() << ").\n";
}

static void filmTorol(FilmTar& tar) {
    std::cout << "\n-- Film torlese --\n";
    if (tar.getSize() == 0) {
        std::cout << "A tar ures.\n";
        return;
    }
    std::cout << "Torles ID alapjan (0 = vissza): ";
    int id = bekerValasztas();
    if (id == 0) return;

    bool talalt = false;
    for (int i = 0; i < tar.getSize(); i++) {
        if (tar[i]->getId() == id) {
            talalt = true;
            std::cout << "Torlendo film: ";
            tar[i]->print(std::cout);
            break;
        }
    }
    if (!talalt) {
        std::cout << "Nem talalhato ilyen ID-ju film.\n";
        return;
    }

    std::cout << "Biztosan torli? (i/n): ";
    char valasz;
    std::cin >> valasz;
    if (valasz == 'i' || valasz == 'I') {
        tar.removeById(id);
        std::cout << "Film torolve.\n";
    } else {
        std::cout << "Torles megszakitva.\n";
    }
}

static void filmekListaz(const FilmTar& tar) {
    std::cout << "\n-- Osszes film --\n";
    if (tar.getSize() == 0) {
        std::cout << "(Ures a tar.)\n";
        return;
    }
    std::cout << tar;
    std::cout << "Osszes: " << tar.getSize() << " film.\n";
}

static void filmKeres(const FilmTar& tar) {
    std::cout << "\n-- Film keresese --\n";
    std::cout << "Keresett cimreszlet (0 = vissza): ";
    std::cin.ignore(1000, '\n');
    std::string keresett;
    std::getline(std::cin, keresett);
    if (keresett == "0") return;

    FilmTar* talalatok = tar.findByTitle(keresett);
    if (talalatok->getSize() == 0) {
        std::cout << "Nincs talalat.\n";
    } else {
        std::cout << "Talalatok (" << talalatok->getSize() << "):\n";
        std::cout << *talalatok;
    }
    delete talalatok;
}

int main() {
    std::signal(SIGINT,  signalHandler);
    std::signal(SIGTERM, signalHandler);

    FilmTar* tar = FilmTar::loadFromCSV(ADATFAJL);
    globalTar = tar;

    std::atexit(mentes);

    std::cout << "FilmTar betoltve (" << tar->getSize() << " film).\n";

    int valasztas = -1;
    while (valasztas != 0) {
        menuKiir();
        valasztas = bekerValasztas();
        switch (valasztas) {
            case 1: ujFilm(*tar);        break;
            case 2: filmTorol(*tar);     break;
            case 3: filmekListaz(*tar);  break;
            case 4: filmKeres(*tar);     break;
            case 0:
                std::cout << "Kilep...\n";
                break;
            default:
                std::cout << "Ervenytelen valasztas.\n";
        }
    }

    globalTar = NULL;
    tar->saveToCSV(ADATFAJL);
    std::cout << "Adatok mentve: " << ADATFAJL << std::endl;
    delete tar;
    return 0;
}

#endif