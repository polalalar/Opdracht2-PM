#include <iostream>
using namespace std;


int main () {
    int num = 4821;
    int length = 1;
    while ( num > 0 ) {
        length*=10;
        num /= 10;
    }
    for (int l=length; length>0; length/=10){
        cout << num/l << endl;
        num = num % l;
    }
}