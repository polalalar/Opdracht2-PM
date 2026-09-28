#include <iostream>
#include <fstream>
#include <climits>
#include <filesystem>
#include <cmath>
using namespace std;

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

void addNumber(int getal, ofstream &uitvoer){
    int lengte = 0;
    int getalCopy = getal;
    while (getal > 0){
        lengte += 1;
        getal /= 10;
    }
    for (int i = 0; i < lengte; i++){
        int divide = 1;
        for(int j = 1; j < lengte - i; j++){
            divide *= 10;
        }
        int result = getalCopy / divide;
        uitvoer.put(result + '0');// '0' for ASCII
        getalCopy -= result * divide; 
    }
}

// Output een getal naar de uitvoerfile
void outputGetal( int getal, ofstream &uitvoer) {
    if (getal >= 10) {
        outputGetal((getal/10), uitvoer);
    } // if
    uitvoer.put('0' + (getal%10));
} // outputGetal

int main ( ) {

    infoblokje();

    ifstream invoer ("moeilijkinput.txt", ios::in);
    ofstream uitvoer ("testoutput.txt", ios::out);
    
    int karakterCounter = 0;
    char karakter = invoer.get();
    char vorigKarakter = karakter;
    uitvoer.put(karakter);
    int collatz_getal = 0;
    int regels = 0;

    while (!invoer.eof()) {
        if (karakter == vorigKarakter) {
            karakterCounter++;
            if (karakter >= '0' && karakter <= '9'){ // Speciaal karakter
                collatz_getal *= 10;
                collatz_getal += karakter - '0';
            }
        } // if
        else {
            if (karakter == '\n'){
            regels++;
            }
            if (vorigKarakter == '\\') {
                uitvoer.put('\\');
            } // if
            if (karakterCounter > 1) {
                outputGetal(karakterCounter, uitvoer);
            } // if
            if (karakter >= '0' && karakter <= '9'){ // Speciaal karakter
                collatz_getal *= 10;
                collatz_getal += karakter - '0';
                uitvoer.put('\\');
            } // if
            else if (collatz_getal > 0){
                int herhalingen = collatz(collatz_getal);
                if (herhalingen == -1){
                    cout << "Voor " << collatz_getal << " wordt de waarde groter dan INT_MAX!" << endl;
                }else{
                    cout << "Voor " << collatz_getal << " waren er " << herhalingen << " iteraties nodig om op 1 uit te komen!" << endl;
                }
                collatz_getal = 0;
            }
            uitvoer.put(karakter);
            karakterCounter = 1;
        } // else
        vorigKarakter = karakter;
        karakter = invoer.get();
    } // while
    invoer.close();
    uitvoer.close();

    int invoer_size = filesystem::file_size("moeilijkinput.txt");
    int uitvoer_size = filesystem::file_size("testoutput.txt");
    cout << "Groote invoerfile " << invoer_size << " karakters, ";
    cout << "uitvoerfile is " << uitvoer_size << " karakters, " << endl;
    int compressieRatio = ceil( (double) uitvoer_size/invoer_size * 100);
    
    cout << "compressie-ratio; " << compressieRatio << "% en " << regels << " regels;" << endl;



    return 0;
} // main