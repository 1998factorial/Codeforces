#include <bits/stdc++.h>
using namespace std;

const int m = 1e9;
int main(){
    srand(time(NULL));
    int N1 = 10 , N2 = 10 , M = 2000;
    cout << N1 << " " << N2 << " " << M << endl;
    for(int i = 1; i <= M; ++i){
        cout << i % 10 + 1 << " " << rand() % N2 + 1 << endl;
    }
}
