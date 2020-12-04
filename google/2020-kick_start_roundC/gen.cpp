#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int T = 10;
    cout << T << endl;
    for(int i = 1; i <= T; ++i){
        int N = 1000;
        for(int j = 1; j <= N; ++j){
            int p = rand() % 2;
            if(p % 2)cout << rand() % 100 + 1 << " ";
            else cout << - (rand() % 100 + 1) << " ";
        }
        cout << endl;
    }
}
