// V1 - 200+
// #include <fstream>

// int main(){
//     std::ifstream i("1.txt");
//     std::ofstream u("2.txt");
//     int c=1;
//     char k,v;
//     i.get(v);
//     while (i.get(k)){
//     if (k==v)c++;
//     else{
//     if((v>='0'&&v<='9')||v=='\\')u<<'\\';
//     u.put(v);
//     if(c>1)u<<c;
//     c=1;}
//     v=k;
//     }
// }
// #include <fstream>
// int main(){std::ifstream i("1.txt");std::ofstream u("2.txt");int c=1;char k,v;i.get(v);while (i.get(k)){if (k==v)c++;else{if((v>='0'&&v<='9')||v=='\\')u<<'\\';u.put(v);if(c>1)u<<c;c=1;}v=k;}}

//remove tabs and enters, rename files to 1.txt and 2.txt
// files close automatically
// returns 0 automatically


// V2 - 173 | algoritme = 111

// New compile command to remove #include
// g++ -Wall -Wextra -include fstream -o run short.cpp

// int main(){
//     std::ifstream i("1.txt");
//     std::ofstream o("2.txt");
//     int c=0;
//     char k,v;
//     while(i.get(k)){
//         if(c&&k!=v){
//             if((v>47&&v<58)||v==92)o<<'\\';
//             o.put(v);
//             if(c>1)o<<c;
//             c=0;}
//         v=k;
//         c++;
//     }
// }

// int main(){std::ifstream i("1.txt");std::ofstream o("2.txt");int c=0;char k,v;while(i.get(k)){if(c&&k!=v){if((v>47&&v<58)||v==92)o<<'\\';o.put(v);if(c>1)o<<c;c=0;}v=k;c++;}}


// V3 - 125

// New compile command to shorten initialization
// g++ -Wall -Wextra -include fstream -D'F=std::ifstream i("1.txt");std::ofstream o("2.txt");' -o run short.cpp


// int main(){
//     F;
//     int c=0;
//     char k,v;
//     while(i.get(k)){
//         if(c&&k!=v){
//             if((v>47&&v<58)||v==92)o<<'\\';
//             o.put(v);
//             if(c>1)o<<c;
//             c=0;}
//         v=k;
//         c++;
//     }
// }

// int main(){F;int c=0;char k,v;while(i.get(k)){if(c&&k!=v){if((v>47&&v<58)||v==92)o<<'\\';o.put(v);if(c>1)o<<c;c=0;}v=k;c++;}}

// V4 - 18

// Absolutely scuffmaxxed, but i guess it works???
// New compile command to put the whole algorithm in 1 character
// g++ -Wall -Wextra -include fstream -D'K=std::ifstream i("1.txt");std::ofstream o("2.txt");int c=0;char k,v;while(i.get(k)){if(c&&k!=v){if((v>47&&v<58)||v==92)o.put(92);o.put(v);if(c>1)o<<c;c=0;}v=k;c++;}' -o run short.cpp

// int main(){K}

// 'K=std::ifstream i("1.txt");std::ofstream o("2.txt");int c=0;char k,v;while(i.get(k)){if(c&&k!=v){if((v>47&&v<58)||v==92)o.put(92);o.put(v);if(c>1)o<<c;c=0;}v=k;c++;}'

// V5 - 1

// Scuffmaxxedmaxxed, what has the code become atp

// g++ -Wall -Wextra -include fstream -D'K=main(){std::ifstream i("1.txt");std::ofstream o("2.txt");int c=0;char k,v;while(i.get(k)){if(c&&k!=v){if((v>47&&v<58)||v==92)o.put(92);o.put(v);if(c>1)o<<c;c=0;}v=k;c++;}}' -o run short.cpp

K