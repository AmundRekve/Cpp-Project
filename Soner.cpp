/**
 *   Filen inneholder funksjonene til Soner klassen.
 *
 *   @file        Soner.cpp
 *   @author      Ole Marcus Markussen
 *   @co-auther   Stian Johnsen
 *   @co-auther   Amund Rekve
 */


#include "Soner.h"      // Header for Soner klassen
#include <iostream>     // For input og output (cin, cout)
#include <map>          // For bruk av map
#include <fstream>      // For filinnlesing og utskrift
#include "LesData3.h"   // For innlesning av data
#include "Sone.h"       // Sone klassen, brukt i Soner
#include "Enum.h"       // For enum typer
#include "Const.h"      // For konstanter
using namespace std;    // For å slippe std:: prefiks


//##############################################################################################


/**
 * Utskrift av oppdrag, medsendt variabel bestemmer map peker.
 * 
 * @see Sone::skrivOppdragtilFil(std::ofstream &ut, Boligtype type)
 */
void Soner::oppdragSkrivTilFil(ofstream & ut, int soneNr, Boligtype type) {

    sonekart[soneNr]->skrivOppdragtilFil(ut, type);
}


//##############################################################################################


/**
 * Leser fra fil ved program start
 * 
 * @see Sone(std::ifstream &inn, int soneNr)
 */
void Soner::lesFraFil() {

    int soneNr;
    int oppnum;

    Sone* midlSone;

    ifstream innfil("SONER.DTA", std::ios::in | std::ios::binary);
    
    // Om fil er noe
    if(innfil) {
        
        innfil >> oppnum;
        innfil.ignore();
        innfil >> antallSoner;
        innfil.ignore();

        sisteNum = oppnum;

        for(int i = 1; i <= antallSoner; i++) {

            innfil >> soneNr;

            midlSone = new Sone(innfil, soneNr);

            sonekart[soneNr] = midlSone;
        }

        cout << "\n\nInnlesing av 'SONER.DTA' vellykket!\n\n";
    }
    else {
        cout << "\n\nKunne ikke aapne SONER.DTA!!\n";
    }
    innfil.close();
}


//##############################################################################################


/**
 * Legger til en ny sone i datastrukturen.
 * Returnerer false hvis sone med samme nummer allerede finnes.
 *
 * @param snr Sonenummer.
 * @param beskrivelse Kort beskrivelse av sonen.
 * @return true hvis sonen ble lagt til, false ellers.
 */
bool Soner::leggTilSone(int snr, const string& beskrivelse) {
    
    // Sjekk om sonenummeret allerede finnes
    if (sonekart.find(snr) != sonekart.end()) {
        return false; // Fantes fra før
    }

    // Opprett ny Sone og legg den inn i sonekart
    Sone* ny = new Sone(snr, beskrivelse);
    sonekart[snr] = ny;
    return true;
}


//##############################################################################################


/**
 *  Oppretter en helt ny sone basert på brukerens input.
 * 
 * @see Soner::leggTilSone(int snr, const std::string &beskrivelse)
 */
void Soner::nySone() {
    
    int snr;
    string beskrivelse;

    cin >> snr;
    cin.ignore();

    // Skriv en beskrivelse av sonen
    cout << "Oppgi kort beskrivelse av sonen: ";
    getline(cin, beskrivelse);

    // Prøver å legge til sonen
    if (leggTilSone(snr, beskrivelse)) {
        cout << "Sone med nummer " << snr << " ble lagt til.\n";
        antallSoner++;
    }
    else {
        cout << "FEIL: Sone med nummer " << snr << " finnes allerede!\n";
    }
}


//##############################################################################################


/**
 * Oppretter et nytt bolig/oppdrag for en sone.
 *
 * @see Soner::soneFinnes(int) const
 * @see Sone::nyBolig()
 */
void Soner::nyBolig() {
    
    int snr;

    //Midl til innlesing av fil fungerer.
    if (!sisteNum) {
        sisteNum = 0;
    }

    // Sjekker om max antall oppdrag er registrert
    if(sisteNum < OPPDRAGMAX) {

        cin >> snr;
        cin.ignore();

        if(!sonekart.empty()) {
            if(soneFinnes(snr)) {
                sisteNum++;
                sonekart.at(snr)->nyBolig();

            }
            else {
                cout << "Sonen eksisterer ikke!";
            }
        }
        else {
            cout << "Sonekart er tomt!";
        }
    }
    else {
        cout << "\n\nMaks antall oppdrag registrert!\n\n";
    }
}


//##############################################################################################


/**
 *  Skriver ut alt om en sone til brukeren basert på dems sone nummer valg.
 * 
 * @see Sone::skrivAlleOppdrag() const
 */
void Soner::skrivEnSone() {

    int snr;

    cin >> snr;

    auto it = sonekart.find(snr);
    if (it == sonekart.end()) {
        // Sonen ble funnet
        cout << "Feil: Ingen sone med nummer " << snr << " funnet.\n";
        return;
    }

    Sone* sone = it->second;
    sone->skrivAlleOppdrag();
}


//##############################################################################################


/**
 * Skriver ut en bolig
 * 
 * @see Sone::finnOppdrag(int onr)
 */
void Soner::skrivEnBolig() {

    int onr;
    Sone* sonene;

    cin >> onr;

    for(const auto& pair : sonekart){
        sonene = pair.second;
        
        sonene->finnOppdrag(onr);
    }
}


//##############################################################################################


/**
 * Skriver ut til fil ved program slutt.
 * 
 * @see Sone::skrivTilFil(std::ofstream &ut)
 */
void Soner::skrivTilFil() {

    Sone* midlSone;

    ofstream utfil("SONER.DTA");

    if(utfil) {
        utfil << sisteNum << " " << antallSoner;

        for(const auto & val : sonekart) {
            
            midlSone = val.second;

            midlSone->skrivTilFil(utfil);
        }

        cout << "\n\nUtskrift av 'SONER.DTA' vellykket!\n\n";
    }
    else {
        cout << "\nSONER.DTA eksisterer ikke!\n";
    }
    utfil.close();
}


//##############################################################################################


/**
 * Skriver ut alle soner.
 * 
 * @see Sone::skrivKunSoneData()
 */
void Soner::skrivAlleSoner() {
    
    cout << "\n";

    if (sonekart.empty()) {
        cout << "Ingen soner er registrert enna.\n";
        return;
    }

    for (const auto& pair : sonekart) {

        Sone* sone = pair.second;

        sone->skrivKunSoneData();
        cout << "\n";
    }
}


//##############################################################################################


/**
 * Sjekker om sonen finnes for en kunde, tilkall med gSoner fra main
 * 
 */
bool Soner::soneFinnes(int snr) const {
    return (sonekart.find(snr) != sonekart.end());
}


//##############################################################################################


/**
 * Sletter en bolig/oppdrag
 * 
 * @see Sone::slettBolig(int onr)
 */
void Soner::slettEnBolig(){
    
    int onr;
    Sone* sonene;

    cin >> onr;

    for(const auto& pair : sonekart){
        sonene = pair.second;
        
        sonene->slettBolig(onr);
    }
}


//##############################################################################################


/**
 * Submeny for videre navigering til funksjoner fra hovedmeny
 */
void Soner::subMeny(char valg) {
    
    switch(valg) {
        case 'S':
            valg = lesKommando("");
            switch(valg) {
                case 'N': nySone();                         break;
                case '1': skrivEnSone();                    break;
                case 'A': skrivAlleSoner();                 break;
                default: cout << "\nUgyldig subKommando!";  break;
            }
            break;
        case 'O':
            valg = lesKommando("");
            switch(valg) {
                case 'N': nyBolig();                        break;
                case '1': skrivEnBolig();                   break;
                case 'S': slettEnBolig();                   break;
            default: cout << "\nUgyldig subKommando!";  break;
            }
            break;
    cout << "\n\n";
    default: break;
    }
}