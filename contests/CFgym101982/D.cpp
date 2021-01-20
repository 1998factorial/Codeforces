#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000009;
ll DP[130][130][1005] , f[130];
int N , K;

void add(ll& a , ll b){
    a += b;
    if(a >= MOD)a -= MOD;
}

int main(){
    cin >> K >> N;
    f[0] = 1;
    for(int i = 1; i <= N; ++i)f[i] = f[i - 1] * 2 % K;
    DP[0][0][0] = 1;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j <= i; ++j){
            for(int k = 0; k < K; ++k){
                for(int d = 0; d < 2; ++d){
                    int nk = (k + f[i] * d) % K;
                    add(DP[i + 1][j + d][nk] , DP[i][j][k]);
                }
            }
        }
    }
    ll ret = 0;
    for(int j = 1; j <= N; ++j){
        add(ret , DP[N][j][0] * j % MOD);
    }
    cout << ret << endl;
}