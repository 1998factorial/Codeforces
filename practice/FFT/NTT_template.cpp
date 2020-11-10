#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
#define sz(a) a.size()
using namespace std;
typedef long long ll;

const ll mod = 998244353;

inline ll qpow(ll x , ll n){
    ll ret = 1ll;
    while(n){
        if(n % 2)ret = ret * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ret;
}
vector<vector<ll>> poly;

void change(vector<ll>& y , int len) {
    int i, j, k;
    for (i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        k = len / 2;
        while (j >= k) {
            j = j - k;
            k = k / 2;
        }
        if (j < k) j += k;
    }
}

void NTT(vector<ll>& P , int op){
    int len = sz(P) , i , j , k;
    change(P , len);
    for(i = 1; i < len; i <<= 1){
        ll gn = qpow(3ll , (mod - 1) / (i << 1));
        if(op == -1)gn = qpow(gn , mod - 2);
        for(j = 0; j < len; j += (i << 1)){
            ll g = 1;
            for(k = 0; k < i; ++k , g = g * gn % mod){
                ll x = P[j + k] , y = g * P[j + k + i] % mod;
                P[j + k] = (x + y) % mod;
                P[j + k + i] = (x - y + mod) % mod;
            }
        }
    }
    if(op == -1){
        ll inv = qpow(len , mod - 2);
        for(i = 0; i < len; ++i)P[i] = P[i] * inv % mod;
    }
}

vector<ll> multiply(vector<ll> aa , vector<ll> bb){
    int n = sz(aa) , m = sz(bb) , len = 1 , i;
    while(len < n + m)len <<= 1;
    vector<ll> a(len) , b(len);
    for(i = 0; i < n; ++i)a[i] = aa[i];
    for(i = 0; i < m; ++i)b[i] = bb[i];
    NTT(a , 1);
    NTT(b , 1);
    vector<ll> c(len);
    for(i = 0; i < len; ++i)c[i] = a[i] * b[i] % mod;
    NTT(c , -1);
    while(!c.empty() && c.back() == 0)c.pop_back();
    return c;
}

vector<ll> solve(int l , int r){
    vector<ll> ret;
    if(l == r){
        for(ll i : poly[l])ret.push_back(i);
        return ret;
    }
    int mid = (l + r) >> 1;
    ret = multiply(solve(l , mid) , solve(mid + 1 , r));
    return ret;
}

int N;
map<int , int> cnt;

int main(){
    int i;
    scanf("%d" , &N);
    for(i = 1; i <= N; ++i){
        int x; scanf("%d" , &x); ++cnt[x];
    }
    for(auto& e : cnt){
        vector<ll> vec(e.y + 1 , 1);
        poly.push_back(vec);
        ID{
            printf("for %d\n" , e.x);
            for(ll i : poly.back()){
                printf("%lld " , i);
            }
            printf("\n");
        }
    }
    vector<ll> ans = solve(0 , sz(poly) - 1);
    ID for(int i = 0; i < sz(ans); ++i){
        printf("ans[%d] = %lld\n" , i , ans[i]);
    }
    int id = sz(ans) / 2;
    printf("%lld\n" , ans[id]);
}