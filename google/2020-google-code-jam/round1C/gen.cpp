#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int T = 5;
    cout << T << endl;
    for(int t = 1; t <= T; ++t){
        int N = 6 , D = rand() % 15 + 2;
        cout << N << " " << D << endl;
        for(int i = 1; i <= N; ++i){
            cout << rand() % 10 + 1 << " ";
        }
        cout << endl;
    }
}
