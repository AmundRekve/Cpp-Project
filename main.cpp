/**
 * Inneholder hovedprogram.
 * Mal kommer fra tildelte prosjektfiler.
 * 
 * @file    main.cpp
 * @author  Stian MJ
 */

#include <iostream>
#include "Kunder.h"
#include "Soner.h"
#include "global.h"
#include "LesData3.h"

using namespace std;

Kunder gKunder;         ///<  Globalt container-objekt med ALLE kundene.
Soner gSoner;           ///<  Globalt container-objekt med ALLE sonene.


/**
*  Hovedprogram.
*/
int main()  {

    char valg;

    //Leser inn til datastruktur fra fil
    gSoner.lesFraFil();
    gKunder.lesFraFil();

    skrivMeny();

    valg = lesKommando("Kommando: ");

    while(valg != 'Q') {
        switch(valg) {
            case 'K':           gKunder.subMeny();          break;
            case 'S': case 'O': gSoner.subMeny(valg);       break;
             default:           skrivMeny();                break;
        }
        valg = lesKommando("Kommando: ");
    }

    // Skriver til fil fra datastruktur
    gSoner.skrivTilFil();
    gKunder.skrivTilFil();
 
    cout << "\n\n";
    return 0;
}