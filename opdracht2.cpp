#include <iostream>
#include <fstream>
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

int collatz(int nummer){
    int herhalingen = 0;
    while (nummer != 1){
        cout << nummer << endl;
        herhalingen += 1;
        if (nummer % 2 == 0){//even
            nummer /= 2;
        }else{//uneven
            nummer = nummer * 3 + 1;
        }
    }
    return herhalingen;
}

void addNumber(int getal, ofstream &uitvoer){
    int lengte;
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
        uitvoer.put(result + '0');
        getalCopy -= result * divide; 
    }
}


int main ( ) {

    infoblokje();

    ifstream invoer ("simpelinput.txt", ios::in);
    ofstream uitvoer ("testoutput.txt", ios::out);

    char karakter = '@';
    char vorigKarakter = 'a';
    int karakterCounter = 1;
    karakter = invoer.get();

    while (!invoer.eof()) {
        if (vorigKarakter == '\n') {
            uitvoer.put(vorigKarakter);
        }
        if (karakter == vorigKarakter) {
            karakterCounter++;
        } // if
        else {
            uitvoer.put(vorigKarakter);
            if (karakterCounter > 1) {
                //rekening gehouden met counter >= 10
                addNumber(karakterCounter, uitvoer);
            } // if
            karakterCounter = 1;
        } // else
        vorigKarakter = karakter;
        karakter = invoer.get();
    } // while

    invoer.close();
    uitvoer.close();


    return 0;
} // main