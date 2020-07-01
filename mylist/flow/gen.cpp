#include <bits/stdc++.h>
using namespace std;

const int m = 1e9;
int main(){
    int N = 500;
    srand(time(NULL));
    cout << N << endl;
    for(int i = 1; i <= N; ++i){
        cout << rand() % m + 1 << " " << rand() % m + 1 << " " << rand() % m + 1 << endl;
    }
}
