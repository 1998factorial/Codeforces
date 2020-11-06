#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int DP[1 << 16][16 * 16] , N , r[16] , b[16] , c[16];
// DP[s][i] = maximal deduction on b if we have set s of cards and 
// have a total deduction on r with i
int main(){
    int i , j , k , s1 = 0 , s2 = 0;
    cin >> N;
    for(i = 0; i < N; ++i){
        char t; cin >> t >> r[i] >> b[i];
        c[i] = t == 'R';
        s1 += r[i];
        s2 += b[i];
    }
    for(i = 0; i < (1 << N); ++i){
        for(j = 0; j < N * N; ++j){
            DP[i][j] = -1;
        }
    }
    DP[0][0] = 0;
    for(i = 0; i < (1 << N); ++i){
        for(j = 0; j < N * N; ++j){
            if(DP[i][j] == -1)continue;
            int nr = 0 , nb = 0;
            for(k = 0; k < N; ++k){
                if(i & (1 << k)){
                    nr += c[k];
                    nb += 1 - c[k];
                }
            }
            for(k = 0; k < N; ++k){
                if(i & (1 << k))continue;
                int ni = i | (1 << k);
                int sr = min(nr , r[k]) , sb = min(nb , b[k]);
                DP[ni][j + sr] = max(DP[ni][j + sr] , DP[i][j] + sb);
            }
        }
    }
    int ret = INF;
    for(i = 0; i < N * N; ++i){
        if(~DP[(1 << N) - 1][i]){
            ret = min(ret , N + max(s1 - i , s2 - DP[(1 << N) - 1][i]));
        }
    }
    cout << ret << endl;
}