#include <bits/stdc++.h>
using namespace std;


int main(){
    srand(time(NULL));
    int N = 5 , M = 10 , K = 10;
    cout << N << " " << M << " " << K << endl;
    for(int i = 1; i <= N; ++i){
        cout << rand() % 10 << " " << rand() % 10 << " " << rand() % 10 << endl;
    }
    for(int i = 1; i <= M; ++i){
        int u = rand() % N + 1 , v = (u + rand() % N + 1) % N + 1;
        if(u < v)swap(u , v);
        if(u == v){
            if(u == N)--v;
            else ++u;
        }
        cout << u << " " << v << endl;
    }
}