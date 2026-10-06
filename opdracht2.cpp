#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

// Note: function vs varable names guidelines?

// Print een infoblokje op het scherm
void infoblokje( ) {
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

// Bereken de collatzserie voor een nummer
int collatz(int nummer){
    // Note: output moet laten zien bij welke herhaling int_max overschreden word
    
    int herhalingen = 0;
    while (nummer != 1){
        herhalingen += 1;
        if (nummer % 2 == 0){//even
            nummer /= 2;
        } // if
        else { // oneven
            if (nummer >= ((INT_MAX - 1)/ 3)+1){//Doing (x-1)/y + 1 makes the outcome ceil(x/y)
                return -1 * herhalingen;//Return a negative number when it isn't possible
            }
            nummer = nummer * 3 + 1;
        } // else
    } // while
    return herhalingen;
}

// Output de counter naar de uitvoerfile
void outputCounter( int counter, ofstream &output , int &outputFileSize) {
    if (counter >= 10) {
        outputCounter((counter/10), output, outputFileSize);
    } // if
    output.put('0' + (counter%10));
    outputFileSize++;
} // outputCounter

// Note: 
void outputData( int fileLines, int inputFileSize, 
                 int outputFileSize ) {
    int compressionRate = ((double)(outputFileSize)/(double)(inputFileSize))*100+0.5;
    cout << "Grootte invoerfile " << inputFileSize << " karakters."
         << endl;
    cout << "Grootte uitvoerfile: " << outputFileSize << " karakters."
         << endl;
    cout << "Compressie-ratio "
         << compressionRate << "%; " 
         << fileLines << " regels." << endl;
} // outputData

// Codeer de inputfile naar de outputfile
void encode( ifstream &input, ofstream &output ) {
    // Variabele voor het aantal herhaalde karakters
    int karakterCounter = 0;

    // Variabelen voor huidig en vorig karakter
    char karakter = input.get();
    char vorigKarakter = karakter;

    // Variable voor het getal waarvoor collatz moet worden berekend
    int collatzGetal = 0;

    // Variabele voor aantal herhalingen om collatz te berekenen
    int collatzHerhalingen = 0;

    // Variabelen voor bestandgrootte
    int inputFileSize = 0;
    // +1 voor de get die al gebruikt is // Note:
    // -1 voor de laatste get, die geen karakter vind maar wel nog +1 doet
    int outputFileSize = 0;

    // Variabele voor aantal regels in bestand
    int fileLines = 0;
    
    // Codeer-loop (+filesize, filelines en collatz)
    while (!input.eof()) {
        // File lines
        if (karakter == '\n') {
            fileLines++;
        } // if

        // Collatz
        if (karakter >= '0' && karakter <= '9') { // Getal - collatz
            collatzGetal *= 10;
            collatzGetal += karakter - '0';
        } // if
        else if (collatzGetal > 0) {
            collatzHerhalingen = collatz(collatzGetal);
            if (collatzHerhalingen <= -1) {
                cout << "Voor " << collatzGetal << 
                " wordt de waarde na " << collatzHerhalingen * -1 << " iteraties groter dan INT_MAX!" << endl;
            } // if
            else {
                cout << "Voor " << collatzGetal << " waren er " 
                << collatzHerhalingen << 
                " iteraties nodig om op 1 uit te komen!" << endl;
            } // else
            collatzGetal = 0;
        } // else if

        // Encode
        if (karakter == vorigKarakter && vorigKarakter != '\n') {
            karakterCounter++;
        } // if
        else {
            if (vorigKarakter == '\\' || (
                vorigKarakter >= '0' && vorigKarakter <= '9')) 
            { // Speciaal karakter
                output.put('\\');
                outputFileSize++;
            } // if
            output.put(vorigKarakter);
            outputFileSize++;
            if (karakterCounter > 1) {
                outputCounter(karakterCounter, output, outputFileSize);
            } // if
            karakterCounter = 1;
        } // else
        vorigKarakter = karakter;
        karakter = input.get();
        inputFileSize++;
    } // while

    // Voeg het laatste karakter toe aan de output
    output.put(vorigKarakter); // is altijd \n volgens aannames Note:
    outputFileSize += 1; // laatste karakter

    outputData(fileLines, inputFileSize, outputFileSize);
} // encode

// Decodeer de inputfile naar de outputfile
void decode( ifstream &input, ofstream &output ) {
    // lees volgende karakter
    // print n keer karakter
    char karakter = input.get();
    char vorigKarakter = karakter;

    // int inputFileSize = 0;
    // int outputFileSize = 0;

    int karakterCounter = -1;

    while (!input.eof()) {

        if (karakter >= '0' && karakter <= '9'){
            karakterCounter *= 10;
            karakterCounter += karakter - '0';
        }
        else if (karakterCounter > 0){
            for (int i = 0; i<karakterCounter; i++){
                output.put(vorigKarakter);
            }
            karakterCounter = 0;
            vorigKarakter = karakter;
        }else{
            if (karakterCounter >= 0){
               output.put(vorigKarakter); 
            }
            karakterCounter = 0;
            vorigKarakter = karakter;
        }
        
        karakter = input.get();
    }
} // decode


void testrun() {
    ifstream simpelinput ("simpelinput.txt", ios::in);
    ofstream simpeloutput ("simpeltestoutput.txt", ios::out);

    ifstream moeilijkinput ("moeilijkinput.txt", ios::in);
    ofstream moeilijkoutput ("moeilijktestoutput.txt", ios::out);

    cout << "----------< Encode Simpel >----------" << endl;
    encode(simpelinput, simpeloutput);

    cout << endl << endl << endl;
    cout << "----------< Encode Moeilijk >----------" << endl;
    encode(moeilijkinput, moeilijkoutput);

    simpelinput.close();
    simpeloutput.close();

    moeilijkinput.close();
    moeilijkoutput.close();

    ifstream simpelinputdecode ("simpeloutput.txt", ios::in);
    ofstream simpeloutputdecode ("simpeltestoutput.txt", ios::out);


    cout << "----------< Decode Simpel >----------" << endl;
    decode(simpelinputdecode, simpeloutputdecode);

    simpelinputdecode.close();
    simpeloutputdecode.close();
} // testrun



// main
int main ( ) {

    infoblokje();

    testrun();
    return 1;


    char antwoord = ' ';
    cout << "Wil je een bestand coderen(C) of decoderen(D)?" << endl;
    cin >> antwoord;
    // Check voor valide input? (c/C/d/D)

    string inputFile = "";
    string outputFile = "";

    cout << "Wat is de naam van de input file?" << endl << "> ";
    cin >> inputFile;

    cout << "Wat is de naam van de output file?" << endl << "> ";
    cin >> outputFile;

    ifstream input (inputFile, ios::in);
    ofstream output (outputFile, ios::out);

    // Coderen
    if (antwoord == 'c' || antwoord == 'C'){
        encode(input, output);
    } // if

    // Decoderen
    else if (antwoord == 'd' || antwoord == 'D'){
        cout << endl;
        // decode(input, output);
    } // else if

/*    
    int karakterCounter = 0;
    char karakter = invoer.get();
    char vorigKarakter = karakter;
    uitvoer.put(karakter);
    int collatzGetal = 0;
    int regels = 0;

    while (!invoer.eof()) {
        if (karakter == vorigKarakter) {
            karakterCounter++;
            if (karakter >= '0' && karakter <= '9'){ // Speciaal karakter
                collatzGetal *= 10;
                collatzGetal += karakter - '0';
            } // if
        } // if
        else {
            if (karakter == '\n'){
            regels++;
            } // if
            if (vorigKarakter == '\\') {
                uitvoer.put('\\');
            } // if
            if (karakterCounter > 1) {
                outputGetal(karakterCounter, uitvoer);
            } // if
            if (karakter >= '0' && karakter <= '9') { // Speciaal karakter
                collatzGetal *= 10;
                collatzGetal += karakter - '0';
                uitvoer.put('\\');
            } // if
            else if (collatzGetal > 0) {
                int herhalingen = collatz(collatzGetal);
                if (herhalingen == -1) {
                    cout << "Voor " << collatzGetal << " wordt de waarde groter dan INT_MAX!" << endl;
                } // if
                else {
                    cout << "Voor " << collatzGetal << " waren er " << herhalingen << " iteraties nodig om op 1 uit te komen!" << endl;
                } // if
                collatzGetal = 0;
            } // else if
            uitvoer.put(karakter);
            karakterCounter = 1;
        } // else
        vorigKarakter = karakter;
        karakter = invoer.get();
    } // while
*/

    input.close();
    output.close();



    return 0;
} // main