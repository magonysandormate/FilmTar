/**
 * @file teszt.cpp
 * @brief FilmTar rendszer tesztjei (gtest_lite).
 */

#include "gtest_lite.h"
#include "film.hpp"
#include "csaladi.hpp"
#include "dokumentum.hpp"
#include "filmtar.hpp"
#include "input.hpp"
#include <sstream>
#include <stdexcept>

int main() {

    // --- Getter-ek ---
    TEST(Film, GetterekCsaladi)
        Csaladi cs(10, "Toy Story", 81, 1995, 6);
        EXPECT_EQ(10, cs.getId());  EXPECT_EQ(81, cs.getHossz());
        EXPECT_EQ(1995, cs.getEv()); EXPECT_EQ(6, cs.getKorhatar());
        EXPECT_STREQ("Toy Story", cs.getCim().c_str());
    END

    TEST(Film, GetterekDokumentum)
        Dokumentum d(20, "Bolygónk", 50, 2006, "BBC");
        EXPECT_EQ(20, d.getId());  EXPECT_STREQ("BBC", d.getLeiras().c_str());
    END

    // --- matches ---
    TEST(Film, MatchesReszStringEsEsetek)
        Csaladi cs(1, "Toy Story", 81, 1995, 0);
        EXPECT_TRUE(cs.matches("Toy"));   EXPECT_TRUE(cs.matches("toy story"));
        EXPECT_TRUE(cs.matches(""));      EXPECT_FALSE(cs.matches("Matrix"));
    END

    // --- operator== ---
    TEST(Film, EgyenlosegIdAlapjan)
        Csaladi a(5,"A",90,2000,0); Csaladi b(5,"B",60,2010,6); Csaladi c(6,"A",90,2000,0);
        EXPECT_TRUE(a == b);  EXPECT_FALSE(a == c);
    END

    // --- polimorf print/save ---
    TEST(Film, PrintFormatum)
        Csaladi cs(1,"Toy Story",81,1995,6);
        std::ostringstream o; cs.print(o); std::string s = o.str();
        EXPECT_TRUE(s.find("Csaladi")!=std::string::npos);
        EXPECT_TRUE(s.find("81 perc")!=std::string::npos);
        EXPECT_TRUE(s.find("6+")!=std::string::npos);
    END

    TEST(Film, SaveCSVFormatum)
        Csaladi cs(1,"Toy Story",81,1995,6);
        std::ostringstream o; cs.save(o);
        EXPECT_TRUE(o.str().find("0;1;Toy Story;81;1995;6")!=std::string::npos);
        Dokumentum d(2,"Dok",50,2006,"BBC");
        std::ostringstream o2; d.save(o2);
        EXPECT_TRUE(o2.str().find("1;2;Dok;50;2006;BBC")!=std::string::npos);
    END

    /*// --- FilmTar add / getSize / operator[] ---
    TEST(FilmTar, AddEsIndex)
        FilmTar tar;
        EXPECT_EQ(0, tar.getSize());
        tar.add(new Csaladi(1,"A",90,2000,0));
        tar.add(new Dokumentum(2,"B",60,2010,"x"));
        EXPECT_EQ(2, tar.getSize());
        EXPECT_EQ(1, tar[0]->getId());
        EXPECT_EQ(2, tar[1]->getId());
        EXPECT_THROW(tar[5], std::out_of_range);
        EXPECT_THROW(tar[-1], std::out_of_range);
    END*/

    // --- removeById ---
    TEST(FilmTar, Remove)
        FilmTar tar;
        tar.add(new Csaladi(1,"A",90,2000,0));
        tar.add(new Csaladi(2,"B",90,2000,0));
        tar.add(new Csaladi(3,"C",90,2000,0));
        tar.removeById(2);
        EXPECT_EQ(2, tar.getSize());
        EXPECT_EQ(1, tar[0]->getId()); EXPECT_EQ(3, tar[1]->getId());
        tar.removeById(1);  EXPECT_EQ(1, tar.getSize());
        tar.removeById(3);  EXPECT_EQ(0, tar.getSize());
        EXPECT_NO_THROW(tar.removeById(999));
    END

    // --- findByTitle ---
    TEST(FilmTar, FindByTitle)
        FilmTar tar;
        tar.add(new Csaladi(1,"Toy Story",81,1995,0));
        tar.add(new Dokumentum(2,"Toy Story 2",92,1999,"x"));
        tar.add(new Csaladi(3,"Matrix",136,1999,16));
        FilmTar* r = tar.findByTitle("toy"); EXPECT_EQ(2, r->getSize()); delete r;
        FilmTar* r2 = tar.findByTitle("xyz"); EXPECT_EQ(0, r2->getSize()); delete r2;
        FilmTar* r3 = tar.findByTitle(""); EXPECT_EQ(3, r3->getSize()); delete r3;
    END

    // --- operator<< ---
    TEST(FilmTar, Kiiras)
        FilmTar tar;
        std::ostringstream o; o << tar; EXPECT_STREQ("", o.str().c_str());
        tar.add(new Csaladi(1,"Toy Story",81,1995,6));
        tar.add(new Dokumentum(2,"Dok",50,2006,"BBC"));
        std::ostringstream o2; o2 << tar;
        EXPECT_TRUE(o2.str().find("Csaladi")!=std::string::npos);
        EXPECT_TRUE(o2.str().find("Dokumentum")!=std::string::npos);
    END

    // --- CSV round-trip ---
    TEST(FilmTar, CSVRoundTrip)
        const std::string f = "ft_test.txt";
        { FilmTar tar; tar.add(new Csaladi(1,"Nemo",100,2003,3));
          tar.add(new Dokumentum(2,"BBC",55,2010,"Termeszet")); tar.saveToCSV(f); }
        FilmTar* t = FilmTar::loadFromCSV(f);
        EXPECT_EQ(2, t->getSize());
        EXPECT_STREQ("Nemo", (*t)[0]->getCim().c_str());
        Dokumentum* d = dynamic_cast<Dokumentum*>((*t)[1]);
        EXPECT_TRUE(d != NULL);
        if(d) EXPECT_STREQ("Termeszet", d->getLeiras().c_str());
        delete t;
        FilmTar* t2 = FilmTar::loadFromCSV("nem_letezo_xyz.txt");
        EXPECT_EQ(0, t2->getSize()); delete t2;
    END

    // --- polimorfizmus / dynamic_cast ---
    TEST(FilmTar, Polimorfizmus)
        FilmTar tar;
        tar.add(new Csaladi(1,"Mese",80,2000,6));
        tar.add(new Dokumentum(2,"Dok",55,2010,"x"));
        EXPECT_TRUE(dynamic_cast<Csaladi*>(tar[0]) != NULL);
        EXPECT_TRUE(dynamic_cast<Dokumentum*>(tar[1]) != NULL);
        EXPECT_TRUE(dynamic_cast<Dokumentum*>(tar[0]) == NULL);
    END

    // --- InputHandler ---
    TEST(InputHandler, BeolvasasValidacio)
        { std::istringstream is("0\nFilm\n90\n2000\n6\n"); std::ostringstream os;
          Film* f = InputHandler::readFilm(is, os, 10);
          EXPECT_EQ(10, f->getId()); EXPECT_EQ(6, dynamic_cast<Csaladi*>(f)->getKorhatar());
          delete f; }
          
        { std::istringstream is("9\n1\nDok\n45\n2015\nLeiras\n"); std::ostringstream os;
          Film* f = InputHandler::readFilm(is, os, 42);
          EXPECT_TRUE(dynamic_cast<Dokumentum*>(f) != NULL); 
          EXPECT_EQ(42, f->getId());
          delete f; }
          
        { std::istringstream is("0\nX\n-1\n90\n2000\n0\n"); std::ostringstream os;
          Film* f = InputHandler::readFilm(is, os, 1);
          EXPECT_EQ(90, f->getHossz()); delete f; }
    END

    // --- Auto-increment ID generálás és Másoló konstruktor ---
    TEST(FilmTar, AutoIncrementIdEsCopy)
        FilmTar tar;
        EXPECT_EQ(1, tar.getNextId());
        
        tar.add(new Csaladi(10,"A",90,2000,0));
        EXPECT_EQ(11, tar.getNextId());
        
        tar.add(new Dokumentum(5,"B",60,2010,"x"));
        EXPECT_EQ(11, tar.getNextId());
        
        tar.add(new Csaladi(20,"C",90,2000,0));
        EXPECT_EQ(21, tar.getNextId());
        
        // Másoló konstruktor tesztelése (át kell vennie a maxId-t)
        FilmTar masolat(tar);
        EXPECT_EQ(21, masolat.getNextId());
    END

    TEST(FilmTar, HatareseteIndex)
        FilmTar tar;
        tar.add(new Csaladi(1,"A",90,2000,0));
        bool dob1 = false, dob2 = false;
        try { tar[1];  } catch (const std::out_of_range&) { dob1 = true; }
        try { tar[-1]; } catch (const std::out_of_range&) { dob2 = true; }
        EXPECT_TRUE(dob1);
        EXPECT_TRUE(dob2);
    END

    TEST(FilmTar, RemoveNemLetezo)
        FilmTar tar;
        EXPECT_NO_THROW(tar.removeById(0));
    END

    TEST(Film, SaveCSVNegativHossz)
        const std::string f = "invalid_test.txt";
        { std::ofstream o(f.c_str());
        o << "0;99;Rossz Film;-500;2001;6\n"; }
        FilmTar* t = FilmTar::loadFromCSV(f);
        EXPECT_EQ(0, t->getSize());
        delete t;
    END

    TEST(FilmTar, MelyMasolas)
        FilmTar eredeti;
        eredeti.add(new Csaladi(1,"Toy Story",81,1995,0));
        FilmTar masolat(eredeti);
        eredeti.removeById(1);
        EXPECT_EQ(0, eredeti.getSize());
        EXPECT_EQ(1, masolat.getSize());
    END

    return 0;
}