#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const ll mod = 998244353;
const int maxn = 3e5 + 10;
int N , K;
ll fac[maxn] , inv[maxn] , cnt[maxn * 3];

struct event{
    int l , r;
    event(){}
    event(int l_ , int r_) : l(l_) , r(r_) {}
    bool operator < (const event& rhs) const {
        return r < rhs.r;
    }
};

ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n >> 1);
    ret = ret * ret % mod;
    if(n & 1)ret = ret * x % mod;
    return ret;
}

ll C(int n , int r){
    if(n < 0 || r < 0 || r > n)return 0;
    return fac[n] * (inv[n - r] * inv[r] % mod) % mod;
}

void init(){
    fac[0] = 1;
    for(int i = 1; i < maxn; ++i)fac[i] = fac[i - 1] * i % mod;
    inv[0] = qpow(fac[0] , mod - 2);
    for(int i = 1; i < maxn; ++i)inv[i] = qpow(fac[i] , mod - 2);
}

int main(){
    init();
    scanf("%d %d" , &N , &K);
    vector<event> eves;
    vector<int> tmp;
    map<int , int> mp;
    int tot = 0;
    for(int i = 1; i <= N; ++i){
        int l , r;
        scanf("%d %d" , &l , &r);
        eves.emplace_back(l , r);
        tmp.push_back(l);
        tmp.push_back(r);
    }
    sort(tmp.begin() , tmp.end());
    for(int i : tmp){
        if(!mp[i])mp[i] = ++tot;
    }
    for(auto& e : eves){
        ++cnt[mp[e.l]]; --cnt[mp[e.r] + 1];
    }
    for(int i = 1; i <= tot; ++i){
        cnt[i] += cnt[i - 1];
    }
    ID for(int i = 1; i <= tot; ++i){
        printf("cnt[%d] = %lld\n" , i , cnt[i]);
    }
    sort(eves.begin() , eves.end());
    ll ret = 0;
    for(int i = 0 , j = 0; i < N; i = j){
        while(j < N && eves[i].r == eves[j].r)++j;
        int up = eves[j].r == eves[i].r ? j : j - 1;
        int dx = mp[eves[i].r];
        for(int k = i; k <= up; ++k){
            --cnt[dx];
            ret += C(cnt[dx] , K - 1);
            ret %= mod;
        }
    }
    printf("%lld\n" , ret);
}