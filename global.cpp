/**
 * Innhold til hovedmeny funksjon
 * 
 * 
 * @file    gFunk.cpp
 * @author  Stian MJ
 */

#include <iostream>
#include "global.h"

using namespace std;

/**
 * Skriver ut hovedmeny.
 */
void skrivMeny() {
    cout << "--- HOVEDMENY ---\n";
    cout << " K N - Kunde Ny\n";
    cout << " K 1 <knr> - Skriv alt om en kunde\n";
    cout << " K A - Skriv alle kunder\n";
    cout << " K E <knr> - Endre kunde\n";
    cout << " K S <knr> - Slett kunde\n";
    cout << " K O <knr> - Kunde Oversikt\n";
    cout << " S N <snr> - Sone Ny\n";
    cout << " S 1 <snr> - Skriv alt om en sone\n";
    cout << " S A - Skriv alle soner\n";
    cout << " O N <snr> - Oppdrag Nytt\n";
    cout << " O 1 <onr> - Skriv alt om et oppdrag\n";
    cout << " O S <onr> - Slett oppdrag\n";
    cout << " Q - Avslutt\n\n";
}