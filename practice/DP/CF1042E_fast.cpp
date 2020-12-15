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
void sub(ll& x , ll y){
    x -= y;
    if(x < 0)x += MOD;
}
const int INF = 1e9 + 10;
int N , M;
int R , C;
array<int , 3> cells[1005 * 1005];
ll DP[1005 * 1005] , dsum[1005 * 1005] , rqsum[1005 * 1005] , cqsum[1005 * 1005] , rsum[1005 * 1005] , csum[1005 * 1005];

int main(){
    scanf("%d %d" , &N , &M);
    int tot = 0;
    rep(i , 1 , N){
        rep(j , 1 , M){
            int x; 
            scanf("%d" , &x);
            cells[++tot] = {i , j , x};
        }
    }
    scanf("%d %d" , &R , &C);
    sort(cells + 1 , cells + 1 + tot , [&](array<int , 3>& lhs , array<int , 3>& rhs){
        return lhs[2] < rhs[2];
    });
    rep(i , 1 , tot){
        int l = 1 , r = i - 1 , j = 0;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(cells[mid][2] < cells[i][2]){
                j = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        /*rep(k , 1 , j){
            add(DP[i] , DP[k]);
            add(DP[i] , (cells[i][0] - cells[k][0]) * (cells[i][0] - cells[k][0]) % MOD);
            add(DP[i] , (cells[i][1] - cells[k][1]) * (cells[i][1] - cells[k][1]) % MOD);
        }*/
        add(DP[i] , dsum[j]);
        add(DP[i] , rqsum[j]);
        add(DP[i] , cqsum[j]);
        add(DP[i] , ((ll)cells[i][0] * cells[i][0] % MOD) * j % MOD);
        add(DP[i] , ((ll)cells[i][1] * cells[i][1] % MOD) * j % MOD);
        sub(DP[i] , 2ll * ((ll)cells[i][0] * rsum[j] % MOD) % MOD);
        sub(DP[i] , 2ll * ((ll)cells[i][1] * csum[j] % MOD) % MOD);
        DP[i] *= qpow(j , MOD - 2);
        DP[i] %= MOD;
        dsum[i] = dsum[i - 1];
        add(dsum[i] , DP[i]);
        rsum[i] = rsum[i - 1];
        add(rsum[i] , cells[i][0]);
        csum[i] = csum[i - 1];
        add(csum[i] , cells[i][1]);
        rqsum[i] = rqsum[i - 1];
        add(rqsum[i] , cells[i][0] * cells[i][0] % MOD);
        cqsum[i] = cqsum[i - 1];
        add(cqsum[i] , cells[i][1] * cells[i][1] % MOD);
    }
    rep(i , 1 , tot){
        if(cells[i][0] == R && cells[i][1] == C){
            printf("%lld\n" , DP[i]);
            return 0;
        }
    }
}