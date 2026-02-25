/**
 * Deklarerer klassen Sone og alle dens verdier og funksjoner
 *
 *   @file        Sone.h
 *   @author      Ole Marcus Markussen
 *   @co-auther   Stian Johnsen
 *   @co-auther   Amund Rekve
 */


#pragma once

#ifndef SONE_H
#define SONE_H 


#include <string>      // For std::string
#include <vector>      // For bruk av vector
#include "Bolig.h"     // For Bolig Klassens Skriv og les
#include "Enebolig.h"  // For Enebolig Klassens skriv og les
#include "Enum.h"      // For Boligtype enumen


 /**
  * @class Sone
  *
  * Klassen Sone håndterer alle funksjoner knyttet til Bolig og Enebolig objektene.
  * Klassen er ansvarlig for oppretting, utskriving, inlesning og mye annet for Bolig objektene.
  */
class Sone {
private:

    int soneNummer;
    std::string beskrivelse;
    std::vector<Bolig*> boliger;  ///< Lagrer alle bolig og enebolig objektene

public:
    
    // Oppretter et sone objekt
    Sone(int snr, const std::string& beskrivelse);
    
    // Leser soneinformasjon fra fil.
    Sone(std::ifstream& inn, int soneNr);

    // Søker etter og viser oppdraget med gitt oppdragsnummer.
    void finnOppdrag(int onr);
    
    // Oppretter et nytt oppdrag i sonen.
    void nyBolig();
    
    // Sletter et oppdrag med angitt oppdragsnummer.
    void slettBolig(int onr);
    
    // Skriver ut all informasjon om sonen og dens oppdrag.
    void skrivAlleOppdrag() const;
    
    // Skriver ut kun soneinformasjonen.
    void skrivKunSoneData();
    
    // Skriver ut oppdrag av en bestemt boligtype til fil.
    void skrivOppdragtilFil(std::ofstream& ut, Boligtype type);
    
    // Skriver sone og oppdragsdata til fil.
    void skrivTilFil(std::ofstream& ut);

};

#endif // SONE_H


