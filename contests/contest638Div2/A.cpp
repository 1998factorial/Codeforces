#include <bits/stdc++.h>
using namespace std;


int main(){
    int t; cin >> t;
    while(t--){
        int N; cin >> N;
        long long a = 1ll << N , s = 0;
        for(int i = 1; i <= N; ++i){
            s += (1ll << i);
        }
        for(int i = 1; i < N / 2; ++i){
            a += (1ll << i);
        }
        cout << a - (s - a) << endl;
    }
}
