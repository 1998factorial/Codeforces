#include <bits/stdc++.h>
using namespace std;

int main(){
    int N = 40 , M = 40;
    cout << N << " " << M << endl;
    srand(time(NULL));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            int x = rand() % 3;
            cout << 'C';
            //if(x == 0)cout << 'L';
            //if(x == 1)cout << 'W';
            //if(x == 2)cout << 'C';
        }
        cout << endl;
    }
}