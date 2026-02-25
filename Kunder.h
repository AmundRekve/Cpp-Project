/**
 * Deklarasjon for klassen Kunder
 * 
 * @file    Kunder.h
 * @author  Stian MJ
 */

#ifndef __KUNDER_H
#define __KUNDER_H

#include    <iostream>
#include    <list>
#include    "Kunde.h"
#include    "Soner.h"


/**
 * Hovedklasse for kunder, inneholder kunde pekere i en vector.
 */
class Kunder {
    private:
        int                 sisteKundeNr;
        std::list<Kunde*>   kunde;

    public:
        void endreKunde();          ///< Endrer kundens soner.
        Kunde* finnKunde(int nr);   ///< Returner Kunde* om kunde eksisterer.
        void lesFraFil();           ///< Leser fra fil ved program start.
        void nyKunde();             ///< Oppretter ny kunde
        void oversiktKunde();       ///< Skrive ut interesante boliger
        void skrivAltEnKunde();     ///< Skriver ut alt om en kune
        void skrivAlleKunder();     ///< Skriver ut alle kunder
        void skrivTilFil();         ///< Skriver til fil ved program slutt.
        void slettKunde();          ///< Sletter kunde.
        void sorterKunder();        ///< Sorterer listen kunde.
        void subMeny();             ///< Funksjonsvalg videreførst fra hovedmeny
};

#endif
