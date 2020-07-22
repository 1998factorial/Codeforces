#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int t; t = 1000;
    cout << t << endl;
    while(t--){
        int N = 50 , M = 5;
        cout << N << " " << M << endl;
        for(int i = 1; i <= M; ++i){
            cout << rand() % 1000000 + 1 << " " << rand() % 1000000 + 1 << endl;
        }
    }
}