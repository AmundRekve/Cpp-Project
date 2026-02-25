/**
 * Deklarasjon for klassen Kunde
 * 
 * @file    Kunde.h
 * @author  Stian MJ
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Enum.h"
#include "Soner.h"

#ifndef __KUNDE_H
#define __KUNDE_H

 class Kunde {
    private:
        int                uniktNr, 
                           tlfNr;
        std::string        navn,
                           gateadresse,
                           postadresse,
                           mail;
        Boligtype          boligType;
        std::vector<int>   soneNummer;
    public:
        Kunde(int nr);                                  // Innlesing til nye kunder
        Kunde(std::ifstream & inn, int nr);             // Leser inn fra fil
        void endreKunde();                              // Endrer kunde
        bool finnSone(int valg);                        // Returnerer om en kunde eksisterer
        int hentUniktNr() { return uniktNr; }           // Returnerer unikt nummer/kundenummer
        void skrivKunde();                              // Skriver ut kunde informasjon
        void skrivOppdragtilFil(std::ofstream & ut);    // Skriver ut akutelle boliger/oppdrag for kunde til fil
        void skrivTilFil(std::ofstream & ut);           // Skriver ut til fil ved program slutt
        void sorterSoner();                             // Sorter sonene til kunden
 };
 
 #endif
 