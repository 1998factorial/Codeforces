#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9;

int main(){
    int N = 500 , K = 500;
    srand(time(NULL));
    cout << N << " " << K << endl;
    for(int i = 1; i <= N; ++i){
        cout << rand() % mod << " " << rand() % mod << endl;
    }
}
