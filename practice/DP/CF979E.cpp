#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
int c[55] , N , P;
ll DP[55][55][55][55];
ll p[55];

int main(){
    cin >> N >> P;
    p[0] = 1; 
    for(int i = 1; i <= N; ++i)p[i] = p[i - 1] * 2 % MOD;
    for(int i = 1; i <= N; ++i)cin >> c[i];
    if(c[1] == 0){
        DP[1][0][1][0] = 1;
    }
    if(c[1] == 1){
        DP[1][0][0][0] = 1;
    }
    if(c[1] == -1){
        DP[1][0][1][0] = 1;
        DP[1][0][0][0] = 1;
    }
    for(int i = 1; i < N; ++i){
        for(int we = 0; we <= i; ++we){
            for(int wo = 0; wo <= i; ++wo){
                for(int be = 0; be <= i; ++be){
                    int bo = i - be - wo - we;
                    if(bo < 0)continue;
                    if(c[i + 1] == -1){
                        // if c[i + 1] is 0
                        
                        DP[i + 1][we + 1][wo][be] += DP[i][we][wo][be] * (p[we + wo + be] * (bo > 0 ? p[bo - 1] : 0) % MOD) % MOD;
                        if(DP[i + 1][we + 1][wo][be] >= MOD)DP[i + 1][we + 1][wo][be] -= MOD;
                        
                        DP[i + 1][we][wo + 1][be] += DP[i][we][wo][be] * (p[we + wo + be] * (bo > 0 ? p[bo - 1] : 1) % MOD) % MOD;
                        if(DP[i + 1][we][wo + 1][be] >= MOD)DP[i + 1][we][wo + 1][be] -= MOD;
                        // if c[i + 1] is 1
                        
                        DP[i + 1][we][wo][be + 1] += DP[i][we][wo][be] * (p[we + be + bo] * (wo > 0 ? p[wo - 1] : 0) % MOD) % MOD;
                        if(DP[i + 1][we][wo][be + 1] >= MOD)DP[i + 1][we][wo][be + 1] -= MOD;
                        
                        DP[i + 1][we][wo][be] += DP[i][we][wo][be] * (p[we + be + bo] * (wo > 0 ? p[wo - 1] : 1) % MOD) % MOD;
                        if(DP[i + 1][we][wo][be] >= MOD)DP[i + 1][we][wo][be] -= MOD;
                    }
                    else{
                        if(c[i + 1] == 0){
                            DP[i + 1][we + 1][wo][be] += DP[i][we][wo][be] * (p[we + wo + be] * (bo > 0 ? p[bo - 1] : 0) % MOD) % MOD;
                            if(DP[i + 1][we + 1][wo][be] >= MOD)DP[i + 1][we + 1][wo][be] -= MOD;
                            
                            DP[i + 1][we][wo + 1][be] += DP[i][we][wo][be] * (p[we + wo + be] * (bo > 0 ? p[bo - 1] : 1) % MOD) % MOD;
                            if(DP[i + 1][we][wo + 1][be] >= MOD)DP[i + 1][we][wo + 1][be] -= MOD;
                        }
                        else{
                            DP[i + 1][we][wo][be + 1] += DP[i][we][wo][be] * (p[we + be + bo] * (wo > 0 ? p[wo - 1] : 0) % MOD) % MOD;
                            if(DP[i + 1][we][wo][be + 1] >= MOD)DP[i + 1][we][wo][be + 1] -= MOD;
                            
                            DP[i + 1][we][wo][be] += DP[i][we][wo][be] * (p[we + be + bo] * (wo > 0 ? p[wo - 1] : 1) % MOD) % MOD;
                            if(DP[i + 1][we][wo][be] >= MOD)DP[i + 1][we][wo][be] -= MOD;
                        }
                    }
                }
            }
        }
    }
    ll ret = 0;
    for(int we = 0; we <= N; ++we){
        for(int wo = 0; wo <= N; ++wo){
            for(int be = 0; be <= N; ++be){
                int bo = N - we - wo - be;
                if(bo < 0)continue;
                int parity = we * 2 + wo + be * 2 + bo;
                parity %= 2;
                if(parity == P){
                    ret += DP[N][we][wo][be];
                    if(ret >= MOD)ret -= MOD;
                }
            }
        }
    }
    cout << ret << endl;
}
