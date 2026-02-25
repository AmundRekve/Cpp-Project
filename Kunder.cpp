/**
 * Definisjon funksjoner for Kunder
 * 
 * @file    Kunder.cpp
 * @author  Stian MJ
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Kunder.h"
#include "Kunde.h"
#include "Const.h"
#include "LesData3.h"

using namespace std;

/**
 * Endrer registrerte soner en kunde er interessert i.
 * 
 * @see Kunde::endreKunde()
 */
void Kunder::endreKunde() {

    int nr;

    cin >> nr;

    // Sjekker om kunde eksisterer
    if(finnKunde(nr)) {

        finnKunde(nr)->endreKunde();
    }
    else {
        cout << "\n\nKunde eksisterer ikke!\n\n";
    }    
}

/**
 * Finner kunde i list ut fra medsendt verdi
 * 
 * @see Kunde::hentUniktNr()
 */
Kunde* Kunder::finnKunde(int nr) {

    // Itererer seg gjennom alle pekere til nr medsendt variabel stemmer.
    auto it = find_if(kunde.begin(), kunde.end(),
        [nr] (const auto & val) { return(val->hentUniktNr() == nr); } );
    
    // Om ikke slutt av liste er naadd, saa return peker.
    if(it != kunde.end()) {
        return *it;
    }
    else {
        return nullptr;
    }
}

/**
 * Innlesing fra fil til objekt Kunder
 * 
 * @see Kunde::Kunde(std::ifstream &inn, int nr)
 * @see Kunde::sorterKunder()
 */
void Kunder::lesFraFil() {

    ifstream innfil("KUNDER.DTA"); 

    if(innfil) {

        int kundeNr;

        innfil >> sisteKundeNr;
        innfil.ignore();

        // Leser inn kunder ut fra sisteKundeNr
        for(int i = 1; i <= sisteKundeNr; i++) {

            innfil >> kundeNr;

            innfil.ignore();
            
            Kunde* midlKunde;

            midlKunde = new Kunde(innfil, kundeNr);

            kunde.push_back(midlKunde);
        }

        cout << "\n\nInnlesing av 'KUNDER.DTA' vellykket!\n\n";
    }
    else {
        cout << "\n\nFilen 'KUNDER.DTA' fungerer ikke";
    }

    innfil.close();

    sorterKunder();
}

/**
 * Oppretter ny objekt i list kunde
 * 
 * @see Kunde::Kunde(int nr)
 * @see Kunder::sorterKunde()
 */
void Kunder::nyKunde() {

    if(sisteKundeNr < KUNDEMAX) {

        // Hvis innlesing fra fil feiler, saa initieres verdien.
        if (!sisteKundeNr) {
            sisteKundeNr = 0;
        }

        sisteKundeNr++;

        Kunde* nyKundeMidl = new Kunde(sisteKundeNr);

        kunde.push_back(nyKundeMidl);

        sorterKunder();
    }
    else {
        cout << "\n\nMaks antall kunder registrert!\n\n";
    }
}

/**
 * Skriver ut alle boliger i kundens interesser
 * 
 * @see Kunde::skrivOppdragtilFil(std::ofstream &ut)
 */
void Kunder::oversiktKunde() {

    int     valg;
    string  filnavn;
    cin >> valg;

    // Om kunden eksisterer
    if(finnKunde(valg)) {

        filnavn = "K" + to_string(valg) + ".DTA";
        
        ofstream utfil(filnavn);

        finnKunde(valg)->skrivOppdragtilFil(utfil);

        utfil.close();

        cout << "\n\nUtskrift av '" << filnavn << "' vellykket!\n\n";
    }
    else {
        cout << "\n\nKunde eksisterer ikke!\n\n";
    }
}

/**
 * Skriver ut alt om en valgt kunde
 * 
 * @see Kunder::finnKunde(int nr)
 * @see Kunde::skrivKunde()
 */
void Kunder::skrivAltEnKunde() {
    
    int nr;

    cin >> nr;

    if(finnKunde(nr)) {
        
        cout << "\nKundenummer: " << nr;
        finnKunde(nr)->skrivKunde();
    }
    else {
        cout << "\nKundenummer eksisterer ikke!";
    }
}

/**
 * Skriver ut alle kunder
 * 
 * @see Kunde::hentUniktNr()
 * @see Kunde::skrivKunde()
 */
void Kunder::skrivAlleKunder() {

    int i = 1;

    // Itererer seg igjennom alle kunder
    for(const auto & val : kunde) {
        
        cout << "\nKundenummer: " << val->hentUniktNr();
        val->skrivKunde();
        
        // Bruker bekrefter videre utskrift for hver 10'ende utskrift
        if(!(i++ % 10)) {
            cout << "\n\nTrykk ENTER for å fortsette\n\n";
            cin.ignore();
        }
    }
}

/**
 * Skriver kunder objekt til fil.
 * 
 * @see Kunde::skrivTilFil(std::ofstream &ut)
 */
void Kunder::skrivTilFil() {
    
    ofstream utfil("KUNDER.DTA");

    if(utfil) {
        
        utfil << sisteKundeNr;

        // Gaar igjennom hver kunde
        for(const auto & val : kunde) {
            val->skrivTilFil(utfil);
        }

        cout << "\n\nUtskrift av 'KUNDER.DTA' vellykket!\n\n";
    }
    else {
        cout << "\nKUNDER.DTA eksisterer ikke!";
    }

    utfil.close();
}

/**
 * Sletter en valgt kunde fra list kunde
 * 
 * @see Kunder::finnKunde(int nr)
 * @see Kunde::hentUniktNr()
 * @see Kunde::skrivKunde()
 */
void Kunder::slettKunde() {
    
    int     nr;
    char    valg;

    Kunde* funnet;

    cin >> nr;

    // Sjekker om kunde eksisterer
    if(finnKunde(nr)) {
        
        finnKunde(nr)->skrivKunde();

        valg =  lesChar(
                    "\nEr du sikker paa at du vil slette folgende kunde [j/N]: "
                );

        if (valg == 'J') {

            // Setter iterator for sletting av valgt kunde
            auto it = find_if(kunde.begin(), kunde.end(),
                [nr](const auto & val) { return(val->hentUniktNr() == nr); });
                
                if (it != kunde.end()) {
                    kunde.erase(it);
                }
        }
    }
    else {
        cout << "\n\nKunden eksistrerer ikke!\n\n";
    }
}

/**
 * Sorter listen kunde
 * 
 * @see Kunde::hentUniktNr()
 */
void Kunder::sorterKunder() {

    kunde.sort([](Kunde* a, Kunde* b) {
        return a->hentUniktNr() < b->hentUniktNr();
        }
    );
}

/**
 * Submeny for funksjonsvalg.
 * 
 * @see Kunde::nyKunde()
 * @see Kunde::skrivAltEnKunde()
 * @see Kunde::skrivAlleKunder()
 * @see Kunde::endreKunde()
 * @see Kunde::slettKunde()
 * @see Kunde::oversiktKunde()
 */
void Kunder::subMeny() {

    int valg;

    valg = lesKommando("");
    cin.ignore();

    switch(valg) {
        case 'N': nyKunde();                        break;
        case '1': skrivAltEnKunde();                break;
        case 'A': skrivAlleKunder();                break;
        case 'E': endreKunde();                     break;
        case 'S': slettKunde();                     break;
        case 'O': oversiktKunde();                  break;
        default: cout << "\nUgyldig subKommando!";  break;
    }
    cout << "\n\n";
}