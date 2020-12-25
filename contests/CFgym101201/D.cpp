#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
int N , K , t[305]; 
ll DP[305][305][2] , f[305];

// t[1] ... t[N]
// for last K - 1 elements
//N - (K - 1) + 1 = N - K + 2 ... N

void add(ll& x , ll y){
    x += y;
    if(x >= MOD)x -= MOD;
}

int main(){
    cin >> N >> K;
    f[0] = 1;
    for(int i = 1; i <= N; ++i)cin >> t[i] , f[i] = f[i - 1] * i % MOD;
    sort(t + 1 , t + 1 + N);
    ll ret = 0;
    for(int i = 1; i <= N; ++i){ // fix t[i]
        if(i >= N - K + 2){
            ll v = (ll)t[i] * (N - i + 1) % MOD; // contribution per permutation
            v = v * f[N] % MOD;
            add(ret , v);
            continue;
        }
        for(int j = 0; j <= N; ++j){
            for(int k = 0; k <= N; ++k){
                for(int l : {0 , 1}){
                    DP[j][k][l] = 0;
                }
            }
        }
        DP[0][0][0] = 1; // length = 0 , |B| = 0 , t[i] not present 
        int L = i - 1 , R = N - i;
        for(int j = 0; j < N; ++j){
            for(int k = 0; k <= j; ++k){
                for(int l : {0 , 1}){
                    if(DP[j][k][l] == 0)continue;
                    if(l == 0){
                        // put t[i] here
                        add(DP[j + 1][k][1] , DP[j][k][l]);
                        // put element from L
                        if(L - (j - k) >= 0)
                            add(DP[j + 1][k][0] , DP[j][k][l] * (L - (j - k)) % MOD);
                        // put element from R
                        if(R - k >= 0)
                            add(DP[j + 1][k + 1][0] , DP[j][k][l] * (R - k) % MOD);
                    }
                    else{
                        // if we have t[i] now, and we have k >= K - 1, we are done
                        if(k >= K - 1)continue;
                        // put element from L
                        if(L - (j - k - 1) >= 0)
                            add(DP[j + 1][k][l] , DP[j][k][l] * (L - (j - k - 1)) % MOD);
                        // put element from R
                        if(R - k >= 0)
                            add(DP[j + 1][k + 1][l] , DP[j][k][l] * (R - k) % MOD);
                    }
                }
            }
        }
        for(int j = K; j <= N; ++j){
            for(int k = K - 1; k <= j; ++k){
                ll v = (ll)t[i] * (N - (j - K + 1) + 1) % MOD; // contribution from t[i] , for length j
                v = v * DP[j][k][1] % MOD;
                v = v * f[N - j] % MOD;
                add(ret , v);
            }
        }
    }
    printf("%lld\n" , ret);
}