#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a , b) for(int i = a; i >= b; --i)
#define MOD 998244353
using namespace std;
typedef long long ll;
inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n >> 1);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}
void add(ll& x , ll y){
    x += y;
    if(x >= MOD)x -= MOD;
}
int N , M;
int R , C;
int a[1005][1005];
ll DP[1005][1005];
bool vis[1005][1005];

ll solve(int r , int c){
    if(vis[r][c]){
        return DP[r][c];
    }
    int k = 0;
    ll& ret = DP[r][c];
    vis[r][c] = 1;
    rep(i , 1 , N){
        rep(j , 1 , M){
            if(a[i][j] < a[r][c]){
                add(ret , solve(i , j));
                add(ret , (i - r) * (i - r) % MOD);
                add(ret , (j - c) * (j - c) % MOD);
                ++k;
            }
        }
    }
    ret *= qpow(k , MOD - 2);
    ret %= MOD;
    return ret;
}

int main(){
    scanf("%d %d" , &N , &M);
    rep(i , 1 , N){
        rep(j , 1 , M){
            scanf("%d" , &a[i][j]);
        }
    }
    scanf("%d %d" , &R , &C);
    solve(R , C);
    printf("%lld\n" , DP[R][C]);
}