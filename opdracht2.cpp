#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

// Opdracht 2 - Programmeermethoden - (De)coderen
// Makers: Jens van der Linden & Thijmen Rosenbrand
// Studentnummers: s5205212 & s5225752
// Compiled met: g++ 13.3.0
// Versie: 1.0
// Laatste wijziging op: 10-10-2026

// Print een infoblokje op het scherm
void infoblokje() {
    cout << "--------------------------------------------------------"
         << endl
         << "Makers        | Jens van der Linden | Thijmen Rosenbrand"
         << endl 
         << "--------------------------------------------------------"
         << endl
         << "Studentnummer |      s5205212       |     s5225752      "
         << endl
         << "--------------------------------------------------------"
         << endl
         << "Aankomstjaar  |        2026         |       2026        "
         << endl
         << "--------------------------------------------------------"
         << endl;
    cout << "Laatste wijziging : 21-09-2026." << endl;
    cout << "Opgave 2 - Programeermethoden - DeCoderen." 
         << endl;
    cout << "--------------------------------------------------------"
         << endl;
    cout << "Functionaliteit van programma" << endl;
    cout << endl << endl;
} // infoblokje

// Berekent het aantal nodige herhalingen voor een nummer om via het 
// collatz vermoeden op 1 uit te komen of groter dan INT_MAX te worden
int collatz(int nummer) {
    // Aantal stappen/herhalingen van het vermoeden
    int herhalingen = 0;

    while (nummer != 1) {
        herhalingen += 1;
        if (nummer % 2 == 0) { // even
            nummer /= 2;
        } // if
        else { // oneven
            // Om omhoog af te ronden na delen wordt (x-1)/y + 1
            // gebruikt.
            // Het omgekeerde van ((num * 3) + 1) is ((num - 1) / 3)
            // Dit wordt gedaan, omdat num anders groter wordt dan
            // INT_MAX, wat voor problemen zorgt.
            if (nummer >= (((INT_MAX - 1) - 1) / 3) + 1) { // te groot
                // Negatief getal als het groter wordt dan INT_MAX.
                return -1 * herhalingen;
            } // if
            nummer = nummer * 3 + 1;
        } // else
    } // while
    return herhalingen;
} // collatz

// Returnt of iets een getal is volgens ASCII.
bool isCijfer(char karakter) {
    return karakter >= '0' && karakter <= '9';
} // isCijfer

// Output een nummer naar de uitvoerfile
// Updatet ook de filegrootte
void outputGetal(int getal, ofstream &output, int &outputFileGrootte) {
    if (getal >= 10) {
        outputGetal((getal/10), output, outputFileGrootte);
    } // if
    output.put('0' + (getal%10));
    outputFileGrootte++;
} // outputGetal

// Print data over de compressie:
// Grootte invoer- & uitvoerfile + compressie-ratio
void outputData(int fileLines, int inputFileGrootte, 
                int outputFileGrootte) {
    // Berekening in doubles om fouten in afronding te voorkomen
    int compressieRatio = ((double)(outputFileGrootte)/
                           (double)(inputFileGrootte)
                           )*100+0.5;
    cout << "Grootte invoerfile " << inputFileGrootte << " karakters."
         << endl;
    cout << "Grootte uitvoerfile: " << outputFileGrootte << " karakters."
         << endl;
    cout << "Compressie-ratio "
         << compressieRatio << "%; " 
         << fileLines << " regels." << endl;
} // outputData

// Codeer de inputfile naar de outputfile
void codeer( ifstream &input, ofstream &output ) {
    // Variabele voor het aantal herhaalde karakters
    int karakterCounter = 0;

    // Variabelen voor huidig en vorig karakter
    char karakter = input.get();
    char vorigKarakter = karakter;

    // Variable voor het getal waarvoor collatz moet worden berekend
    int collatzGetal = 0;

    // Variabele voor aantal herhalingen om collatz te berekenen
    int collatzHerhalingen = 0;

    // Variabelen voor bestandgrootte van input-/outputfile
    int inputFileGrootte = 0;
    int outputFileGrootte = 0;

    // Variabele voor aantal regels in bestand
    int fileLines = 0;
    
    // Codeer-loop (+fileGrootte, filelines en collatz)
    while (!input.eof()) {
        // File lines
        if (karakter == '\n') {
            fileLines++;
        } // if

        // Collatz
        if (isCijfer(karakter)) {
            collatzGetal *= 10;
            collatzGetal += karakter - '0';
        } // if
        else if (collatzGetal > 0) {
            collatzHerhalingen = collatz(collatzGetal);
            if (collatzHerhalingen <= -1) {
                cout << "Voor " << collatzGetal << 
                " wordt de waarde na " << collatzHerhalingen * -1 << 
                " iteraties groter dan INT_MAX!" << endl;
            } // if
            else {
                cout << "Voor " << collatzGetal << " waren er " 
                << collatzHerhalingen << 
                " iteraties nodig om op 1 uit te komen!" << endl;
            } // else
            collatzGetal = 0;
        } // else if

        // Codeer
        if (karakter == vorigKarakter && vorigKarakter != '\n') {
            karakterCounter++;
        } // if
        else {
            if (vorigKarakter == '\\' || isCijfer(vorigKarakter)) {
                output.put('\\');
                outputFileGrootte++;
            } // if
            output.put(vorigKarakter);
            outputFileGrootte++;
            if (karakterCounter > 1) {
                outputGetal(karakterCounter, output, outputFileGrootte);
                karakterCounter = 1;
            } // if
        } // else
        vorigKarakter = karakter;
        karakter = input.get();
        inputFileGrootte++;
    } // while

    // Voeg het laatste karakter toe aan de output
    output.put('\n'); // is altijd \n volgens uitleg opdracht
    outputFileGrootte += 1; // laatste karakter

    outputData(fileLines, inputFileGrootte, outputFileGrootte);
} // codeer

// Decodeer de inputfile naar de outputfile
void decodeer(ifstream &input, ofstream &output) {
    // Variabelen voor huidig en vorig karakter
    char karakter = input.get();
    char vorigKarakter = '\n';

    // Variabele voor het aantal herhalende karakters (t31 => 31)
    // Als deze kleiner is dan 0, wordt er niets geprint
    int karakterCounter = 0;

    // Variabele voor wanneer er 2 backslashes zijn
    bool dubbelSlash = false;

    // Decodeer-loop
    while (!input.eof()) {

        // Note: kan weg?
        //condition zodat als het karakter een getal is de if gedaan wordt,
        //Mits het of geen \\ is of dat er geen dubbelSlash is.
        //Als het \5 is, dan moet de 5 geprint worden en niet als zoveel keer \.

        // Lees cijfer als herhaling van vorig karakter ipv karakter
        if (isCijfer(karakter) && 
            ((vorigKarakter != '\\') || dubbelSlash) ) {
            // Eerste cijfer
            if (karakterCounter == -1) {
                karakterCounter = karakter - '0';
            } // if
            else {
                karakterCounter = karakterCounter*10 + karakter - '0';
            } // else
        } // if
        else {
            // Reset voor het volgende karakter
            if (karakterCounter == -1) {
                karakterCounter = 1;
            } // if

            // Note: relevant?
            // Dit is nodig voor als er \5 staat de \ niet geprint wordt maar de 5 wel.
            if (vorigKarakter == '\\' && karakter != '\\') {
                if (dubbelSlash) {
                   dubbelSlash = false;

                   // Vorige \ is al geprint, dus print deze niet
                   karakterCounter--; 
                } // if
                else {
                    // Print de \ niet
                    // Het volgende karakter moet een cijfer zijn dat
                    // gelezen moet worden als karakter ipv herhaling
                    karakterCounter = -1;
               } // else
            } // if

            // Note: relevant?
            //Voor het geval dat er \\\5 staat dan leest het 2x een dubbel slash,
            //De eerste keer dat er een dubbel staat moet dat een \ neerzetten,
            //En daarna een 5 erbij omdat er \5 staat.

            if (vorigKarakter == '\\' && karakter == '\\') {
                if (dubbelSlash) {
                    dubbelSlash = false;

                    // Vorige \ is al geprint, dus print deze niet
                    karakterCounter--;
                } // if
                else {
                    dubbelSlash = true;
                } // else
            } // if

            // Output het eerdere karakter "karakterCounter" keer.
            for (int i=0; i < karakterCounter; i++) {
                output.put(vorigKarakter);
            } // for
            
            // Geeft aan dat het vorige karakter geen getal was
            karakterCounter = -1;

            // Niet doen bij getallen die herhaling aangeven (1e if)
            vorigKarakter = karakter;
        } // else
        karakter = input.get();
    } // while

    // Voeg het laatste karakter toe aan de output
    output.put(vorigKarakter); // is altijd \n volgens uitleg opdracht    
} // decodeer

// main
int main () {
    // Variabele voor coderen of decoderen
    char antwoord = ' ';

    // Variabelen voor naam input- & outputfile
    string inputFile = "";
    string outputFile = "";

    // Print het infoblokje
    infoblokje();
    
    cout << "Wil je een bestand coderen(C) of decoderen(D)?" << endl;
    cin >> antwoord;

    cout << "Wat is de naam van de input file?" << endl << "> ";
    cin >> inputFile;

    cout << "Wat is de naam van de output file?" << endl << "> ";
    cin >> outputFile;

    // Maak fstream voor input en output
    ifstream input (inputFile, ios::in);
    ofstream output (outputFile, ios::out);

    // Coderen
    if (antwoord == 'c' || antwoord == 'C') {
        codeer(input, output);
        cout << "Succes, de file is gecodeerd!" << endl;
    } // if

    // Decoderen
    else if (antwoord == 'd' || antwoord == 'D') {
        decodeer(input, output);
        cout << "Succes, de file is gedecodeerd!" << endl;
    } // else if

    // Foute input
    else {
        cout << "Dit is geen valide antwoord! (gebruik 'C' of 'D')" 
             << endl;
    } // else

    // Sluit de input/outputfile
    input.close();
    output.close();

    return 0;
} // main