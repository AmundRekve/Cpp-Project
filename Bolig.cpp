/**
 *   Filen inneholder Funkjonene til bolig klassen. 
 * 
 *   @file        Bolig.cpp
 *   @author      Amund Rekve
 *   @co-auther   Ole Marcus Markussen
 *   @co-auther   Stian Johnsen
 */

#include <iostream>     // For input og output som cin og cout
#include <fstream>      // For skriving til og fra filer
#include "Sone.h"       // Sone klassen, bruker Bolig Klassen
#include "Bolig.h"      // Bolig klassens header fil
#include "Enebolig.h"   // sub-klassen til Bolig klassen
#include "LesData3.h"   // For innlesning av ulike data typer
#include "Const.h"
using namespace std;    // For å slippe å bruke std:: for alle std funksjoner

//##############################################################################################

/**
 * Funksjonen setter oppdragsnummeret. 
 * Setter også enumen til korrekt verdi Basert på hva brukeren sender med. 
 * 
 * @param tp Typekode (0 for leilighet, 1 for enebolig).
 * @param nr Oppdragsnummer.
 */
Bolig::Bolig(int tp, int nr) {
    
    
    oppdragsnummer = nr; 

    if (tp == 0) { 
        type = LEILIGHET;
    }
    else {
        type = ENEBOLIG;
    }
}

//##############################################################################################

/**
 * Leser brukerinput for dato, byggeår, areal, antall soverom, pris og diverse adresser.
 */
void Bolig::lesData() {

    datoInnlagt=lesInt("Skriv inn dato innlagt (YYYYMMDD): ", DATOMIN , 99999999);
    
    byggeaar=lesInt("Skriv inn byggeår: ", AARMIN, AARMAX);
    
    bruttoareal=lesInt("Skriv inn bruttoareal: ",100,7000);
    
    antSoverom=lesInt("Skriv inn antall soverom:",1,15 );

    pris=lesInt("Skriv inn pris:",1000000,10000000);
    
    cout << "Skriv inn saksbehandler: ";
    getline(cin, saksbehandler);
    cout << "Skriv inn eierens navn: ";
    getline(cin, eierNavn);
    cout << "Skriv inn gateadresse: ";
    getline(cin, gateadresse);
    cout << "Skriv inn postadresse: ";
    getline(cin, postadresse);
    cout << "Skriv inn beskrivelse: ";
    getline(cin, beskrivelse);
}

//##############################################################################################

/**
 * Funkjonen oppretter et nytt bolig objekt fra den inleste dataen.
 *
 * @param inn Input-filstrøm med boligdata.
 */
void Bolig::lesFraFil(ifstream & inn) {
    
    inn.ignore();
    inn >> datoInnlagt;
    inn.ignore();
    inn >> byggeaar;
    inn.ignore();
    inn >> bruttoareal;
    inn.ignore();
    inn >> antSoverom;
    inn.ignore();
    inn >> pris;
    inn.ignore();
    
    getline(inn, eierNavn);
    getline(inn, saksbehandler);
    getline(inn, gateadresse);
    getline(inn, postadresse);
    getline(inn, beskrivelse);    
}

/**
 * Funkjonen returnerer oppdragsnummeret til bolig objektet som blir spurt.
 * 
 * @return  -  oppdragsnummeret til objektet.
 */
int Bolig::oppdragFinn(){
    return oppdragsnummer;  
}

//##############################################################################################

/**
 * Funkjonen skriver ut alle datamedlemene i objektet bolig.
 */
void Bolig::skrivData() const {
    cout << "\n*** BOLIG (" <<
    (type == ENEBOLIG ? "ENEBOLIG" : "LEILIGHET") << ") ***\n";
    cout << "Oppdragsnummer:  " << oppdragsnummer << "\n";
    cout << "Dato innlagt:    " << datoInnlagt << "\n";
    cout << "Byggeaar:        " << byggeaar << "\n";
    cout << "Bruttoareal:     " << bruttoareal << "\n";
    cout << "Soverom:         " << antSoverom << "\n";
    cout << "Pris:            " << pris << "\n";
    cout << "Saksbehandler:   " << saksbehandler << "\n";
    cout << "Eier:            " << eierNavn << "\n";
    cout << "Gateadresse:     " << gateadresse << "\n";
    cout << "Postadresse:     " << postadresse << "\n";
    cout << "Beskrivelse:     " << beskrivelse << "\n";

}

//##############################################################################################

/** 
 * Funkjonen skriver ut bolig objektet til en fil
 *
 * @param ut Utdata-filstrøm.
 */
void Bolig::skrivBoligerTilFil(ofstream & ut) {

    ut << "\tOppdragsnummer:      " << oppdragsnummer << "\n";
    ut << "\tBeskrivelse:         " << beskrivelse    << "\n";
    ut << "\tDato lagt inn:       " << datoInnlagt    << "\n";
    ut << "\tByggår:              " << byggeaar       << "\n";
    ut << "\tBrutto areal:        " << bruttoareal    << "\n";
    ut << "\tAntall soverom:      " << antSoverom     << "\n";
    ut << "\tSaksbehandler:       " << saksbehandler  << "\n";
    ut << "\tEier:                " << eierNavn       << "\n";
    ut << "\tAdresse:\n";
    ut << "\t\t"                  << gateadresse      << "\n";
    ut << "\t\t"                  << postadresse      << "\n";
}

/**
 * Skriver ut til fil.
 * 
 * @param ut Utfata-filstrøm.
 */
void Bolig::skrivTilFil(ofstream & ut) {

    if(type == LEILIGHET) {
        ut << "\n" << "0 ";
    }
    else {
        ut << "\n" << "1 ";
    }

    ut  << oppdragsnummer << " ";
    ut  << datoInnlagt;
    ut  << "\n" << byggeaar << " " 
        << bruttoareal << " " 
        << antSoverom << " " 
        << pris;
    ut  << "\n" << eierNavn;
    ut  << "\n" << saksbehandler;
    ut  << "\n" << gateadresse;
    ut  << "\n" << postadresse;
    ut  << "\n" << beskrivelse;
}