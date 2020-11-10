#include <bits/stdc++.h>
using namespace std;

int main(){
    int mod = 1e2;
    srand(time(NULL));
    int N = 2;
    cout << N << endl;
    for(int i = 0; i < N; ++i){
        if(rand() % 2){
            cout << 'R' << " ";
        }
        else{
            cout << 'B' << " ";
        }
        cout << rand() % mod + 1 << " " << rand() % mod << endl;
    }
}