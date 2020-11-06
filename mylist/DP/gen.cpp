#include <bits/stdc++.h>
using namespace std;

int main(){
    int N = 1000 , K = 2;
    cout << N << " " << K << endl;
    for(int v = 100 , i = 1; i <= N; ++i){
        cout << v << " ";
        v += 100; 
    }
    cout << endl;
}
