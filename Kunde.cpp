/**
* Innhold funksjoner objekt Kunde
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Kunde.h"
#include "LesData3.h"
#include "Soner.h"
#include "Kunder.h"
#include "Enum.h"
#include "Sone.h"
#include "Const.h"

extern Soner gSoner;

using namespace std;

/**
 * Innlesing til variabler i objekt.
 * 
 * 
 * @param   nr  medsendt siste kunde nr
 * @see     Soner::skrivAlleSoner()
 * @see     Soner::tomtMap()
 * @see     Kunde::finnSone(int valg)
 * @see     Kunde::sorterSoner()
 */
Kunde::Kunde(int nr) {
    
    int tall;
    int valg;
    
    uniktNr = nr;

    tlfNr = lesInt("Telefonnummer", TLFMIN, TLFMAX);

    cout << "\nNavn: ";
    getline(cin, navn);

    cout << "\nGate adresse: ";
    getline(cin, gateadresse);

    cout << "\nPost adresse: ";
    getline(cin, postadresse);

    cout << "\nMail: ";
    getline(cin, mail);

    // Setter bolig type
    tall = lesInt("Leilighet eller Enebolig ",1 , 2);
    if(tall == 1) {
        boligType = LEILIGHET;
    }
    else {
        boligType = ENEBOLIG;
    }

    // Skriver ut alle soner
    gSoner.skrivAlleSoner();

    // Sjekker om sonekartet er tomt
    if(!gSoner.tomtMap()) {
        cout << "\nVelg soner, trykk 0 for a avslutte: ";
        
        cin >> valg;
        
        // Om valg er null saa avslutt innlesing av soner
        while(valg != 0) {
        
            if(gSoner.soneFinnes(valg)) {

                // Sjekk om sone finnes
                if(!finnSone(valg)){
                    soneNummer.push_back(valg);

                    cout << "\nSone " << valg << " lagt til!";
                }
                else {
                    cout << "\nKan ikke registrere duplikat!\n";
                }
            }
            else {
                cout << "\n Sone eksisterer ikke!\n";
            }

            cout << "\nVelg soner, trykk 0 for a avslutte: ";
            
            cin >> valg;
            cin.ignore();

        }

        // Sorterer sone vector til valgt kunde
        sorterSoner();
    }
    else {
        cout << "\n\nIngen soner er registrert!\n\n";
    }
}

/**
 * Leser inn fra fil
 * 
 * @param   inn Innlesing filstrøm
 * @param   nr  Kundenummer
 */
Kunde::Kunde(ifstream & inn, int nr) {

    int type;
    int antallSoner;
    int soneNr;

    uniktNr = nr;

    inn >> tlfNr;
    inn.ignore();

    getline(inn, navn);
    getline(inn, gateadresse);
    getline(inn, postadresse);
    getline(inn, mail);
    
    inn >> type;
    if(type == 0) {
        boligType = LEILIGHET;
    }
    else {
        boligType = ENEBOLIG;
    }
    inn.ignore();

    inn >> antallSoner;
    inn.ignore();

    // Leser kun inn soner om kunden skal ha soner ut fra innfil
    if (antallSoner != 0) {
        for(int i = 0; i < antallSoner; i++) {

            inn >> soneNr;
            soneNummer.push_back(soneNr);
            inn.ignore();
        }
    }

    // Sorterer interesserte soner vector
    sort(soneNummer.begin(), soneNummer.end());
}


/**
 * Endrer paa registrerte soner til valgt kunde
 * 
 * @see Kunde::skrivKunde()
 * @see Kunde::finnSone(int valg)
 * @see Soner::soneFinnes(int snr) const
 * 
 */
void Kunde::endreKunde() {

    char valg;
    int soneValg;

    // Skriver ut aktuell info om kunde
    cout << "\nKunde " << uniktNr << ":"; 
    skrivKunde();

    // Skriver ut valg meny
    cout << "\n2 - Legg til sone(r)"            <<
            "\n1 - Fjern sone(r)"               <<
            "\n0 - Avslutt endring av kunde"    <<
            "\nValg: ";
    cin >> valg;

    // Saa lenge valg ikke er null -> endre paa kunde
    while(valg != '0') {
        
        // Swtich meny
        switch(valg) {
            
            // Legger til soner
            case '2':
                cout << "\nVelg soner som skal legges til: ";
                cin >> soneValg;
                // Finnes soner i sonekart
                if(gSoner.soneFinnes(soneValg)) {
                    // Finnes ikke sone i sone vector for kunde
                    if(!finnSone(soneValg)) {
                        
                        soneNummer.push_back(soneValg);

                        cout << "\nSone " << soneValg << " lagt til!\n";
                        
                        sorterSoner();
                    }
                    else {
                        cout << "\n Sonen er allerede lagt til!\n";
                    }
                }
                else {
                    cout << "\nSonen eksisterer ikke!\n";
                }
                break;
            
            // Fjerner soner
            case '1':
                cout << "\nVelg soner som skal fjernes: ";
                cin >> soneValg;
                // Finnes soner i sone sonekart
                if(gSoner.soneFinnes(soneValg)) {
                    // Finnes sone i sone vector for valgt kunde
                    if(finnSone(soneValg)) {
                        
                        soneNummer.erase(
                            remove( soneNummer.begin(),
                                    soneNummer.end(), 
                                    soneValg), 
                            soneNummer.end()
                        );

                        cout << "\nSone " << soneValg << " fjernet!\n";
                        sorterSoner();
                    }
                    else {
                        cout << "\nSonen er ikke lagt til kunde!\n";
                    }
                }
                else {
                    cout << "\nSonen eksisterer ikke!\n";
                }
                break;
            case '0':   break;
            
            default:
                cout << "\n2 - Legg til sone(r)"    <<
                        "\n1 - Fjern sone(r)"       <<
                        "\n0 - Avslutt endring av kunde";
                break;
        }
        cout << "\n2 - Legg til sone(r)"            <<
                "\n1 - Fjern sone(r)"               <<
                "\n0 - Avslutt endring av kunde"    <<
                "\nValg: ";
        
        cin >> valg;
    }
}

/**
 * Finner en kunde, itererer
 * 
 */
bool Kunde::finnSone(int valg) {
    
    // Sjekker om sone finnes for medsendt verdi
    if(find(soneNummer.begin(), soneNummer.end(), valg) == soneNummer.end()) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * Skriver ut informasjon om valgt kunde
 */
void Kunde::skrivKunde() {

    cout << "\n\tNavn:\t\t" << navn;
    cout << "\n\tTlfnr:\t\t" << tlfNr;
    cout << "\n\tMail:\t\t" << mail;
    cout << "\n\tGate:\t\t" << gateadresse;
    cout << "\n\tPost:\t\t" << postadresse;
    if(boligType == LEILIGHET) {
        cout << "\n\tBoligtype:\tLeilighet";
    }
    else {
        cout << "\n\tBoligtype:\tEnebolig";
    }
    cout << "\n\tSoner:\t\t";
    for(int i = 0; i < soneNummer.size(); i++) {
        cout << soneNummer.at(i) << " ";
    }
}

/**
 * Skriver ut oppdrag til fil
 * 
 * @param ut ut filstroem
 * 
 * @see Soner::oppdragSkrivTilFil(std::ofstream &ut, int soneNr, Boligtype type)
 */
void Kunde::skrivOppdragtilFil(ofstream & ut) {

    ut << "Kundenummer: " << uniktNr << "\n";
    ut << "Navn:        " << navn << "\n";
    if(boligType == LEILIGHET) {
        ut << "****************LEILIGHETER****************\n";
    }
    else {
        ut << "****************ENEBOLIGER****************\n";
    }

    // Går igjennom hver enkelt sone some er registrert for kunde
    for(int i = 0; i < soneNummer.size(); i++) {

        gSoner.oppdragSkrivTilFil(ut, soneNummer.at(i), boligType);
    }
}

/**
 * Skriver ut til fil
 * 
 * @param ut ut filstoem
 */
void Kunde::skrivTilFil(ofstream & ut) {

    ut << "\n" << uniktNr << " ";
    ut << to_string(tlfNr) << " ";
    ut << navn;
    ut << "\n" << gateadresse;
    ut << "\n" << postadresse;
    ut << "\n" << mail;
    
    if(boligType == LEILIGHET) {
        ut << "\n" << "0 ";
    }
    else {
        ut << "\n" << "1 ";
    }

    ut << soneNummer.size();

    if (soneNummer.size() != 0) {

        ut << "\n";
        
        for(int i = 0; i < soneNummer.size(); i++) {
            
            ut << soneNummer[i];

            if(i != soneNummer.size() - 1) {
                ut << " ";
            }
        }
    }
}

/**
 * Sorterer sone vector for kunde
 */
void Kunde::sorterSoner() {
    
    sort(soneNummer.begin(), soneNummer.end());
}