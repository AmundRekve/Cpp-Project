/**
 * Deklarerer subklassen Enebolig og alle dens verdier og funksjoner
 * 
 *   @file     Enebolig.h
 *   @author   Amund Rekve
 */

#ifndef ENEBOLIG_H
#define ENEBOLIG_H

#include "Bolig.h"

/**
 * Klasse for innlesing av Enebolig, arv fra Bolig
 */
class Enebolig : public Bolig {
private:
    int     tomtareal;
    bool    selveiet;
public:
    //Innlesing til filk
    Enebolig(std::ifstream & inn, int tp, int nr);
    //sender opp viktige verdier til bolig og leser egen data
    Enebolig(int tp, int nr);
    //leser egen data
    void lesData();
    // Skriv oppdrag til fil
    virtual void skrivBoligerTilFil(std::ofstream & ut);
    //skriver egen data
    void skrivData() const;
    // Skriv ut til ved program slutt
    virtual void skrivTilFil(std::ofstream & ut);
};

#endif // ENEBOLIG_H
