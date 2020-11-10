#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const int maxn = 1e5 + 10;
ll DP[maxn];
vector<int> divisor[maxn];
vector<int> p[maxn];
bool vis[maxn];
int M;
inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}
inline ll gcd(ll x , ll y){
    return x == 0 ? y : gcd(y % x , x);
}
void init(){
    for(int i = 2; i < maxn; ++i){
        for(int j = i; j < maxn; j += i){
            divisor[j].push_back(i);
        }   
    }
    for(int i = 1; i < maxn; ++i)divisor[i].push_back(1);
    for(int i = 2; i < maxn; ++i){
        if(vis[i])continue;
        for(int j = i; j < maxn; j += i){
            vis[j] = 1;
            p[j].push_back(i);
        }
    }
}

ll f(int x , int y){
    int t = M / y , nx = x / y , sz = p[nx].size();
    ll ret = t;
    for(int mask = 1; mask < (1 << sz); ++mask){
        int v = t;
        for(int i = 0; i < sz; ++i){
            if(mask & (1 << i)){
                v /= p[nx][i];
            }
        }
        v *= __builtin_popcount(mask) & 1 ? -1 : 1;
        ret += v;
        if(ret >= MOD)ret -= MOD;
        if(ret < 0)ret += MOD;  
    }
    return ret;
}

int main(){
    init();
    cin >> M;
    ll ret = 0 , invM = qpow(M , MOD - 2);
    DP[1] = 1;
    for(int x = 2; x <= M; ++x){
        DP[x] = 1;
        sort(divisor[x].begin() , divisor[x].end());
        for(int y : divisor[x]){
            // find number of p , p in [1,M] st gcd(p , x) = y
            if(y == x){
                ll base = 1 - f(x , y) * invM % MOD;
                if(base < 0)base += MOD;
                base = qpow(base , MOD - 2);
                DP[x] *= base;
                DP[x] %= MOD;
            }
            else{
                DP[x] += invM * (f(x , y) * DP[y] % MOD) % MOD;
                if(DP[x] >= MOD)DP[x] -= MOD;
            }
        }
    }
    for(int i = 1; i <= M; ++i){
        ret += DP[i];
        if(ret >= MOD)ret -= MOD;
    }
    cout << ret * invM % MOD << endl;
}