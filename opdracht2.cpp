#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

// Note: function vs varable names guidelines?

// Print een infoblokje op het scherm
void infoblokje( ) {
    cout << "Makers        | Jens van der Linden | Thijmen Rosenbrand"
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
    int herhalingen = 0;
    while (nummer != 1){
        herhalingen += 1;
        if (nummer % 2 == 0){//even
            nummer /= 2;
        } // if
        else { // oneven
            if (nummer >= ((INT_MAX - 1)/ 3)+1){//Doing (x-1)/y + 1 makes the outcome ceil(x/y)
                return -1;
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
    cout << "Grootte invoerfile " << inputFileSize << " karakters."
         << endl;
    cout << "Grootte uitvoerfile: " << outputFileSize << " karakters."
         << endl;
    int compresionRate = (outputFileSize*100)/(inputFileSize*100)*100;
    
    cout << "Compressie-ratio " << compresionRate << "%; " 
         << fileLines << " regels." << endl;
} // outputData

// Codeer de inputfile naar de outputfile
void encode( ifstream &input, ofstream &output ) {
    // Note: comments
    int karakterCounter = 0;
    char karakter = input.get();
    char vorigKarakter = karakter;


    int collatzGetal = 0;

    int inputFileSize = 1;
    int outputFileSize = 0;
    int fileLines = 0;
    

    while (!input.eof()) {
        if (karakter == '\n') {
            fileLines++;
        } // if
        if (karakter == vorigKarakter) {
            karakterCounter++;
            if (karakter >= '0' && karakter <= '9'){ // Getal
                collatzGetal *= 10;
                collatzGetal += karakter - '0';
            } // if
        } // if
        else {
            if (vorigKarakter == '\\') { // Backslash
                output.put('\\');
                outputFileSize++;
            } // if
            if (karakter >= '0' && karakter <= '9') { // Getal
                collatzGetal *= 10;
                collatzGetal += karakter - '0';
                output.put('\\');
                outputFileSize++;
            } // if
            output.put(vorigKarakter);
            if (karakterCounter > 1) {
                outputCounter(karakterCounter, output, outputFileSize);
            } // if
            outputFileSize++;
            karakterCounter = 1;
        } // else
        vorigKarakter = karakter;
        karakter = input.get();
        inputFileSize++;
    } // while
    output.put(vorigKarakter);
    outputFileSize += 2; // last character + EOF char
    
    inputFileSize -= fileLines;
    outputFileSize -= fileLines;
    fileLines++;

    outputData(fileLines, inputFileSize, outputFileSize);
} // encode

// // Decodeer de inputfile naar de outputfile
// void decode( ifstream &input, ofstream &output ) {
//     // lees volgende karakter
//     // print n keer karakter
// } // decode

// main
int main ( ) {

    infoblokje();

    char antwoord = ' ';
    cout << "Wil je een bestand coderen(C) of decoderen(D)?" << endl;
    cin >> antwoord;
    // Check voor valide input? (c/C/d/D)

    string inputFile = "";
    string outputFile = "";

    inputFile = "simpelinput.txt";
    outputFile = "testoutput.txt";

    // cout << "Wat is de naam van de input file?" << endl << "> ";
    // cin >> inputFile;

    // cout << "Wat is de naam van de output file?" << endl << "> ";
    // cin >> outputFile;

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