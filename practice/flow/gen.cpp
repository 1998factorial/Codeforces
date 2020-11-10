#include <bits/stdc++.h>
using namespace std;

const int m = 1e9;
int main(){
    srand(time(NULL));
    int N = 100 , M = 100;
    cout << N << " " << M << endl;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(rand() % 2)cout << '#';
            else cout << '.';
        }
        cout << endl;
    }
}
