/**
 * Deklarerer klassen Soner og alle dens verdier og funksjoner
 *
 *   @file        Soner.h
 *   @author      Ole Marcus Markussen
 *   @co-auther   Stian Johnsen
 *   @co-auther   Amund Rekve
 */

#ifndef SONER_H
#define SONER_H


#include <map>        // Brukes for lagring av Sone-objekter
#include <string>     // Brukes for std::string
#include "Sone.h"     // Inkluderer Sone klassen
#include "Enum.h"     // Brukes for boligtype enumen


 /**
  * @class Soner
  * 
  * Klassen Soner håndterer alle funksjoner knyttet til sone objektene.
  * Det eksisterer kun en Soner objekt når programmet kjører.
  */
class Soner {
private:

    std::map<int, Sone*> sonekart;  ///< Lagrer alle Sone objektene
    int sisteNum;                
    int antallSoner;        

public:

    // Skriver ut oppdrag/bolig for en gitt sone til fil.
    void oppdragSkrivTilFil(std::ofstream& ut, int soneNr, Boligtype type);

    // Leser soneinformasjon fra fil
    void lesFraFil();

    // Legger til en ny sone.
    bool leggTilSone(int snr, const std::string& beskrivelse);

    // Oppretter en ny sone basert på brukerinput.
    void nySone();

    // Oppretter ny bolig for en sone.
    void nyBolig();

    // Skriver ut informasjon om en spesifikk sone
    void skrivEnSone();

    // Skriver ut informasjon om en spesifikk bolig/oppdrag
    void skrivEnBolig();

    // Skriver soneinformasjon til fil.
    void skrivTilFil();

    // Skriver ut alle registrerte soner.
    void skrivAlleSoner();

    // Sjekker om en sone med gitt nummer finnes
    bool soneFinnes(int snr) const;

    // Sletter en valgt bolig/oppdrag.
    void slettEnBolig();

    // Håndterer submeny for videre kommandoer.
    void subMeny(char valg);

    // Returnerer true hvis sonekartet er tomt
    bool tomtMap() { return (sonekart.empty()); }

    // Returnerer siste brukte oppdragsnummer.
    int  returnerSisteNum() { return sisteNum; };
};

#endif // SONER_H