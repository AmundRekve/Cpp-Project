/**
 * Deklarerer klassen Bolig og alle dens verdier og funksjoner
 * 
 *   @file        Bolig.h
 *   @author      Amund Rekve
 *   @co-auther   Ole Marcus Markussen
 *   @co-auther   Stian Johnsen
 */

#ifndef BOLIG_H
#define BOLIG_H

#include "Enum.h" // brukes for globale enumer
#include <string> // brukes for std:string 
#include <fstream> // brukes for fil inlesning og utskriving

/**
* @class Bolig
* 
* Klassen håndterer alt som gjelder bolig objektet, fra inlesning, til utskriving.
* Brukes for the meste av klassen Sone, men sub klassen som Enebolig bruker den også.
*/
class Bolig {
private:
    int oppdragsnummer;
    int datoInnlagt;
    int byggeaar;
    int bruttoareal;
    int antSoverom;
    int pris;                   
    std::string saksbehandler;
    std::string eierNavn;
    std::string gateadresse;
    std::string postadresse;
    std::string beskrivelse;
    Boligtype type;
public:
    // Virtual De-Konstruktør for Bolig og Enebolig.
    virtual ~Bolig() {}
    // Konstruktør for Bolig.
    Bolig(int tp, int nr);
    // Leser inn data for bolig objektet
    void lesData();    
    // leser inn og oppretter bolig objekter fra fil
    void lesFraFil(std::ifstream & inn);
    // Returnerer oppdragsnummeret, brukes mest av andre klasser
    int oppdragFinn();    
    // Returnerer bolig typen
    Boligtype returnerType() { return type; };
    // Skriver ut alt om bolig objektet
    virtual void skrivData() const;
    // Skriver ut bolig objekter til fil 
    virtual void skrivBoligerTilFil(std::ofstream & ut);
    // Skriver bolig til fil
    virtual void skrivTilFil(std::ofstream & ut);
};

#endif // BOLIG_H

