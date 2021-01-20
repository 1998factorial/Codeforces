#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int N = 2e5 , M = 2e5 , K = N / 2;
    cout << N << " " << M << " " << K << endl;
    for(int i = 1; i <= N; ++i){
        cout << rand() % M + 1 << " ";
    }
    cout << endl;
}