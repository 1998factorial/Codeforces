#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int N = 1000 , K = 1000;
    cout << N << " " << K << endl;
    for(int i = 1; i <= N; ++i){
        int sz = K + rand() % 10;
        cout << sz << " ";
        for(int j = 1; j <= sz; ++j){
            cout << rand() % 100 << " ";
        }
        cout << endl;
    }
}
