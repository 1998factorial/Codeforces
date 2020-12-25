#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
int N , K , t[305];
ll fac[305];
ll DP[305][305][2];

// for a length j permutation (j >= K), t[i] wants to be solved at the 
// j - K + 1 round, then we want the number of t[x] >= t[i] to be at least K - 1
// for a fixed t[i] , DP[j][k][l] = # of permutations of length j, with k elements 
// taken from the left of t[i], l => t[i] has been included. !l => t[i] not included

void add(ll& x , ll y){
    x += y;
    if(x >= MOD)x -= MOD;
}

int main(){
    scanf("%d %d" , &N , &K);
    rep(i , 1 , N)scanf("%d" , &t[i]);
    sort(t + 1 , t + 1 + N);
    fac[0] = 1;
    rep(i , 1 , N)fac[i] = fac[i - 1] * i % MOD;
    ll ret = 0;
    rep(i , 1 , N){
        if(i >= N - K + 2){
            add(ret , fac[N] * ((ll)(N - i + 1) * t[i] % MOD) % MOD);
        }
        else{
            rep(j , 0 , N){
                rep(k , 0 , N){
                    rep(l , 0 , 1){
                        DP[j][k][l] = 0;
                    }
                }
            }
            DP[0][0][0] = 1;
            ll L = i - 1 , R = N - i;
            rep(j , 0 , N - 1){
                rep(k , 0 , j){
                    rep(l , 0 , 1){
                        if(l == 0){
                            add(DP[j + 1][k][1] , DP[j][k][0]); // put t[i] here
                            if(L - (j - k) >= 0)add(DP[j + 1][k][0] , (L - (j - k)) * DP[j][k][0] % MOD); // put some question from left of t[i] 
                            if(R - k >= 0)add(DP[j + 1][k + 1][0] , (R - k) * DP[j][k][0] % MOD); // put some question from right of t[i]
                        }
                        else{
                            if(k >= K - 1)continue; // if we have at least K - 1 questions from left of t[i] , we are done
                            add(DP[j + 1][k + 1][1] , (R - k) * DP[j][k][1] % MOD); // question from right
                            add(DP[j + 1][k][1] , (L - (j - k - 1)) * DP[j][k][1] % MOD); // question from left, be aware, need to subtract 1 , as t[i] has been selected
                        }
                    }
                }
            }
            rep(j , K , N){
                rep(k , K - 1 , j){
                    ll v = DP[j][k][1] * (N - (j - K + 1) + 1) % MOD;
                    v = v * fac[N - j] % MOD;
                    v = v * t[i] % MOD;
                    add(ret , v);
                }
            }
        }
    }
    printf("%lld\n" , ret);
}