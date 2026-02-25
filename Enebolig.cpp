/**
 *  Innhold funksjoner klasse Enebolig
 * 
 *   @file     Enebolig.cpp
 *   @author   Amund Rekve
 */

#include <iostream>
#include "Bolig.h"
#include "Enebolig.h"
#include "LesData3.h"
#include "Const.h"

using namespace std;

/**
 * Leser inn til Enebolig
 */
Enebolig::Enebolig(int tp, int nr) : Bolig(tp, nr) {
    lesData();
}

/**
 * Leser inn fra fil
 * 
 * @see Bolig::lesFraFil(std::ifstream &inn)
 */
Enebolig::Enebolig(std::ifstream & inn, int tp, int nr) : Bolig::Bolig(tp, nr) {

    Bolig::lesFraFil(inn);

    inn >> tomtareal;
    inn.ignore();
    inn >> selveiet;
    inn.ignore();
}

/**
 * Leser først inn data fra Bolig så egene datamedlemer
 * 
 * @see Bolig::lesData()
 */
void Enebolig::lesData(){

    Bolig::lesData(); //leser inn data til bolig først så egen data
    
    tomtareal = lesInt(" Tomtarealet til eneboligen\n", TOMTMIN, TOMTMAX);
    selveiet  = lesInt("Tast 1 for selveiet og 0 for ikke", 0, 1);
                                                //leser inn all data
}

/**
 * Skriver ut alt om valgt bolig
 * 
 * @see Bolig::skrivBoligerTilFil(std::ofstream &ut)
 * @param ut Utdata-filstrøm
 */
void Enebolig::skrivBoligerTilFil(ofstream & ut) {

    Bolig::skrivBoligerTilFil(ut);

    ut << "\tTomtareal:         " << tomtareal << "\n";
    ut << "\tSelveiet:          ";
    if(selveiet) {
        ut << "Ja\n";
    }
    else {
        ut << "Nei\n";
    }
}

/**
 * Sender først opp til Bolig sin skrivdata og så skriver den egen data
 * 
 * @see Bolig::skrivData(...);
 */

void Enebolig::skrivData() const {
    
    Bolig::skrivData();
    
    cout << "Tomtareal:       " << tomtareal << " kvm\n";
    cout << "Selveiet?:       " << (selveiet ? "Ja" : "Nei (festetomt)") << "\n";
}

/**
 * Skriver ut til fil ved program slutt
 * 
 * @see Bolig::skrivTilFil(std::ofstream &ut)
 */
void Enebolig::skrivTilFil(ofstream & ut) {

    Bolig::skrivTilFil(ut);

    ut << "\n" << tomtareal << " " << selveiet;
}