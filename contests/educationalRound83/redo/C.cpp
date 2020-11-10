#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N , K;

int main(){
    int t; cin >> t;
    while(t--){
        cin >> N >> K;
        vector<ll> a;
        for(int i = 1; i <= N; ++i){
            ll x; cin >> x;
            a.push_back(x);
        }
        unordered_map<ll , int> cnt;
        bool ok = 1;
        for(ll i : a){
            if(i == 0)continue;
            ll n = i;
            vector<int> num;
            while(n){
                num.push_back(n % K);
                n /= K;
            }
            for(int j = 0; j < num.size(); ++j){
                if(num[j] == 1)++cnt[j];
                else if(num[j] > 1)ok = 0;
            }
        }
        for(auto& e : cnt){
            if(e.second > 1){
                ok = 0;
            }
        }
        if(ok) cout << "YES\n";
        else cout << "NO\n";
    }
}
