#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define FOR(i , a , b) for(int i = a; i <= (int)b; ++i)
#define FORE(e , mp) for(auto& e : mp)
#define sz(a) a.size()
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef long long ll;
const ll INF = 1e18;
// DP[i][j] = minimal number of bullet if we have cleared
// the first i waves, and we are standing at l[i + 1] with 
// j bullets in magzine
vector<map<ll , ll>> DP;
ll l[2005] , r[2005] , a[2005];
int N , K;

template<class T> 
void MIN(T& a , const T& b){
    if(a > b)a = b;
}

int main(){
    scanf("%d%d" , &N , &K);
    DP = vector<map<ll , ll>> (N + 2);
    FOR(i , 1 , N){
        scanf("%lld%lld%lld" , &l[i] , &r[i] , &a[i]);
    }   
    DP[0][K] = 0; // we have cleared 0 waves, we are at l[1] , with K bullets
    FOR(i , 0 , N){
        FORE(e , DP[i]){
            ll j = e.x;
            //ll dn = (a[i + 1] - j + K - 1) / K; // # of days needed to clear this wave
            ll dn = ceil(((double)a[i + 1] - j) / (double)K);
            if(l[i + 1] + dn <= r[i + 1]){
                // we do not reload
                ll nj = j + dn * K - a[i + 1];
                if(!DP[i + 1].count(nj)){
                    DP[i + 1][nj] = INF;
                }
                MIN(DP[i + 1][nj] , DP[i][j] + a[i + 1]);
                // we reload
                if(l[i + 1] + dn < r[i + 1] || (l[i + 1] + dn == r[i + 1] && i != N && r[i + 1] < l[i + 2])){
                    if(!DP[i + 1].count(K)){
                        DP[i + 1][K] = INF;
                    }
                    MIN(DP[i + 1][K] , DP[i][j] + dn * K + j);
                }
            }
        }
    }
    if(!sz(DP[N + 1])){
        printf("-1\n");
    }
    else{
        ll ret = INF;
        FORE(e , DP[N + 1]){
            MIN(ret , e.y);
        }
        printf("%lld\n" , ret);
    }
}

