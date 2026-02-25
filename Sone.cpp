/**
 * Inneholder funksjonene til Sone klassen, Ligger under Soner.
 * Sone håndterer oppretting, sletting og utskrift av bolig og enebolig oppdrag.
 *
 *   @file        Sone.cpp
 *   @author      Ole Marcus Markussen
 *   @co-auther   Stian Johnsen
 *   @co-auther   Amund Rekve
 */


#include <iostream>     // For input og output
#include <fstream>      // For filinnlesing og utskrift
#include "Sone.h"       // Deklarasjon av Sone-klassen
#include "Soner.h"      // Brukes for tilgang til global sone-datastruktur
#include "Bolig.h"      // Brukes for bolig-objekter
#include "Enebolig.h"   // Brukes for enebolig-objekter
#include "LesData3.h"   // For innlesning av diverse data
#include "Enum.h"       // For boligtype-enum
extern Soner gSoner;    // Global variabel for sonehåndtering
using namespace std;    // For å slippe std:: prefiks


//##############################################################################################


/**
 * Konstruktør som leser inn data for en sone fra fil.
 * Leser sonebeskrivelse, antall boliger, og for hver bolig
 * oppretter deretter riktig boligobjekt, og legger det til i vektoren.
 */
Sone::Sone(ifstream & inn, int soneNr) {

    Bolig* ny;

    int type;
    int antallBoliger;
    int oppdragNrMidl;

    soneNummer = soneNr;
    inn.ignore(); getline(inn, beskrivelse);
    inn >> antallBoliger;
    inn.ignore();

    if(antallBoliger != 0) {

        for(int i = 1; i <= antallBoliger; i++) {

            inn >> type;
            inn.ignore();
            inn >> oppdragNrMidl;


            if(type == 0) {
                ny = new Bolig(type, oppdragNrMidl);
                ny->lesFraFil(inn);
            }
            else {
                ny = new Enebolig(inn, type, oppdragNrMidl);
            }
            boliger.push_back(ny);
        }
    }
}


//##############################################################################################


/**
 * Konstruktør som oppretter en sone med et gitt nummer og beskrivelse.
 */
Sone::Sone(int snr, const string& beskrivelse)
    : soneNummer(snr), beskrivelse(beskrivelse) {
}


//##############################################################################################


/**
 * Finner og viser informasjon om et bestemt oppdrag.
 * 
 * @param onr Oppdragsnummeret som skal finnes.
 * @see Bolig::oppdragFinn()
 * @see Bolig::skrivData()
 */
void Sone::finnOppdrag(int onr){
    int oppdragsNummer;

    for(int i=0 ; i<boliger.size(); i++){

        oppdragsNummer = boliger[i]->oppdragFinn();
        if (onr==oppdragsNummer){

                boliger[i]->skrivData();
        }
    }
}


//##############################################################################################


/**
 * Oppretter et nytt bolig eller enebolig oppdrag i sonen.
 * Leser inn data fra bruker og legger til det nye oppdraget.
 * 
 * @see Bolig::lesData()
 * @see Enebolig::lesData()
 */
void Sone::nyBolig() {
    Bolig* ny;
    int tp = lesInt("Tast 1 for leilighet, 2 for enebolig", 1, 2) - 1;
    int oppNum = gSoner.returnerSisteNum();
    

    if (!tp) {
        ny = new Bolig(tp, oppNum);
        ny->lesData();
    }
    else {
        ny = new Enebolig(tp, oppNum);
        
    }

    boliger.push_back(ny);

    cout << "Ny bolig lagt til i sone " << soneNummer;
    cout << " med oppdragsnr " << oppNum << ".\n";
}


//##############################################################################################


/**
 * Sletter en bolig fra sonen basert på oppdragsnummer.
 * 
 * 
 * @param onr Oppdragsnummeret til boligen som skal slettes.
 * @see Bolig::oppdragFinn()
 */
void Sone::slettBolig(int onr){
    
    int oppdragsNummer;
    char svar;

    for(int i=0 ; i<boliger.size(); i++){

        oppdragsNummer = boliger[i]->oppdragFinn();

        if (onr==oppdragsNummer){

            svar=lesChar("Er du sikker på at du vil slette oppdraget? J/N");
            if(svar=='J'){

                delete boliger[i];
                boliger.erase(boliger.begin() + i);// Fjern pekeren fra vektoren
                i--;
                cout<<"bolig "<<onr<<"er slettet \n";
            }
        }
    }
}


//##############################################################################################


/**
 * Skriver ut all informasjon om sonen og tilhørende boliger.
 * Skriver ut soneinformasjon og kaller boligobjektenes utskriftsfunksjon.
 * Pauser etter hver femte bolig hvis det er flere oppdrag.
 */
void Sone::skrivAlleOppdrag() const {
    
    cout << "\n=== Informasjon om Sonen ===\n";
    cout << "Sonenummer:   " << soneNummer << "\n";
    cout << "Beskrivelse:  " << beskrivelse << "\n";
    cout << "Antall boliger: " << boliger.size() << "\n\n";

    if (boliger.empty()) {
        cout << "Ingen boliger i denne sonen.\n";
        return;
    }

    int count = 0;
    for (Bolig* Boligen : boliger) {

        Boligen->skrivData();
        cout << "\n";

        count++;
        if (count % 5 == 0 && count < boliger.size()) {
            string soppel;
            cout << "Trykk ENTER for å fortsette...";
            getline(cin, soppel);
            cin.ignore();
        }
    }
}


//##############################################################################################


/**
 * Skriver ut kun soneinformasjon.
 * 
 * @see Sone::skrivAlleOppdrag()
 */
void Sone::skrivKunSoneData() {

    cout << "Sonenummer:   " << soneNummer;
    cout << "\nBeskrivelse:    " << beskrivelse;
    cout << "\nAntall boliger: " << boliger.size() << "\n\n";
}


//##############################################################################################


/**
 * Skriver soneinformasjon og bolig oppdrag til fil.
 *
 * @param ut Output-stream for fil.
 * @param type Boligtype for filtrering.
 */
void Sone::skrivOppdragtilFil(ofstream & ut, Boligtype type) {

    ut << "Sonenummer:    " << soneNummer << "\n";
    ut << "Beskrivelse:   " << beskrivelse << "\n";

    for(int i = 0; i < boliger.size(); i++) {

        if(boliger.at(i)->returnerType() == type) {
            
            boliger.at(i)->skrivBoligerTilFil(ut);
        }
    }
    ut << "**************************************\n";
}


//##############################################################################################


/**
 * Skriver sone- og boliginformasjon til fil.
 * Format: sone-nummer, beskrivelse, antall boliger og data for hver bolig.
 *
 * @param ut Output-stream for fil.
 */
void Sone::skrivTilFil(ofstream & ut) {

    ut << "\n" << soneNummer << " " << beskrivelse;

    ut << "\n" << boliger.size();
    
    if(boliger.size() != 0) {
        for(int i = 0; i < boliger.size(); i++) {

            boliger.at(i)->skrivTilFil(ut);
        }
    }
}
