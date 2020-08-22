#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int maxn = 2e4 + 10;
inline ll qpow(ll x , ll n){
    ll ret = 1ll;
    while(n){
        if(n % 2)ret = ret * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ret;
}
ll A[maxn];
int N , K , Q;
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
    int len = P.size() , i , j , k;
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

vector<ll> multiply(const vector<ll>& aa , const vector<ll>& bb){
    int n = aa.size() , m = bb.size() , len = 1 , i;
    while(len < 2 * n || len < 2 * m)len <<= 1;//++L;
    vector<ll> a(len) , b(len);
    for(i = 0; i < n; ++i)a[i] = aa[i];
    for(i = 0; i < m; ++i)b[i] = bb[i];
    NTT(a , 1);
    NTT(b , 1);
    vector<ll> c(len);
    for(i = 0; i < len; ++i)c[i] = a[i] * b[i] % mod;
    NTT(c , -1);
    return c;
}

vector<ll> cal(int l , int r){
    if(l == r){
        vector<ll> ret;
        for(ll i : poly[l])ret.push_back(i);
        return ret;
    }
    int mid = (l + r) >> 1;
    return multiply(cal(l , mid) , cal(mid + 1 , r));
}

ll solve(int q){
    poly = vector<vector<ll>> ();
    for(int i = 1; i <= N; ++i){
        vector<ll> vi = {1ll , (ll)q - A[i]};
        poly.push_back(vi);
    }
    vector<ll> ret = cal(0 , N - 1);
    return (ret[K] % mod + mod) % mod;
}

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &A[i]);
    }
    scanf("%d" , &Q);
    while(Q--){
        int t; scanf("%d" , &t);
        if(t == 1){
            int q , i , d; scanf("%d %d %d" , &q , &i , &d);
            ll Ai = A[i];
            A[i] = d;
            printf("%lld\n" , solve(q));
            A[i] = Ai;
        }
        if(t == 2){
            int q , L , R , d; scanf("%d %d %d %d" , &q , &L , &R , &d);
            for(int i = L; i <= R; ++i)A[i] += d;
            printf("%lld\n" , solve(q));
            for(int i = L; i <= R; ++i)A[i] -= d;
        }
    }
}   