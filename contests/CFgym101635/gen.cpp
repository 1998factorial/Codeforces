#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int N = 2 , M = 2 , sz = 3;
    cout << N << " " << M << endl;
    for(int i = 1; i <= N; ++i){
        cout << rand() % sz - sz / 2 << " " << rand() % sz - sz / 2 << endl;
    }
    for(int i = 1; i <= M; ++i){
        cout << rand() % sz - sz / 2 << " " << rand() % sz - sz / 2 << endl;
    }
    cout << rand() % sz - sz / 2 << " " << rand() % sz - sz / 2 << endl;
}