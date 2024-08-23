#include <bits/stdc++.h>
using namespace std;

int main(){
    while(1){
        system("data.exe > in.txt");
        system("main.exe < in.txt > main.txt");
        double begin = clock();
        system("test.exe < in.txt > test.txt");
        double end = clock();
        if(system("fc main.txt test.txt")){
            cout << "WA!";
            break;
        }
        if(end-begin > 1000){
            cout << "TLE!";
            break;
        }
    }
}