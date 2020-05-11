#include <bits/stdc++.h>
using namespace std;

/*
    N = 1 + 2 + .. + 2 ^ x
*/

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        long long N; cin >> N;
        vector<long long> a;
        a.push_back(1);
        long long val = 1;
        for(int i = 1;; ++i){
            if(val + (1ll << i) <= N){
                val += (1ll << i);
                a.push_back(1ll << i);
            }
            else{
                break;
            }
        }
        if(val < N){
            a.push_back(N - val);
        }
        sort(a.begin() , a.end());
        cout << a.size() - 1 << endl;
        for(int i = 1; i < a.size(); ++i){
            cout << a[i] - a[i - 1] << " ";
        }
        cout << endl;
    }
}
