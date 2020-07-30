#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 3e5 + 10;
const ll mod = 998244353;
ii P[maxn];
ll fac[maxn];
int N;

void init(){
    fac[0] = 1;
    for(int i = 1; i < maxn; ++i){
        fac[i] = fac[i - 1] * i % mod;
    }
}

int main(){
    init();
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d" , &P[i].x , &P[i].y);
    }
    ll ret = 0;
    ret = fac[N];
    map<int , int> cnt_x;
    for(int i = 1; i <= N; ++i){
        ++cnt_x[P[i].x];
    }
    ll val_x = 1;
    for(auto& e : cnt_x){
        val_x = val_x * fac[e.y] % mod;
    }
    ret = (ret - val_x + mod) % mod;
    map<int , int> cnt_y;
    for(int i = 1; i <= N; ++i){
        ++cnt_y[P[i].y];
    }
    ll val_y = 1;
    for(auto& e : cnt_y){
        val_y = val_y * fac[e.y] % mod;
    }
    ret = (ret - val_y + mod) % mod;
    sort(P + 1 , P + 1 + N);

    map<ii , int> cnt;
    for(int i = 1; i <= N; ++i){
        ++cnt[P[i]];
    }
    bool ok = 1;
    for(int i = 1; i < N; ++i){
        ok &= (P[i].x <= P[i + 1].x && P[i].y <= P[i + 1].y);
    }
    if(ok){
        ll val = 1;
        for(auto& e : cnt){
            val = val * fac[e.y] % mod;
        }
        ret = (ret + val) % mod;
    }

    printf("%lld\n" , ret);
}   
