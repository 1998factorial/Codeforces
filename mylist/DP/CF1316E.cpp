#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int N , P , K;
int a[maxn] , s[maxn][7];
ll DP[1 << 7];

int main(){
    int i , j , mask , x;
    vector<int> id;
    scanf("%d%d%d" , &N , &P , &K);
    for(i = 1; i <= N; ++i){
        id.push_back(i);
        scanf("%d" , &a[i]);
    }
    sort(id.begin() , id.end() , [&](int x , int y){
        return a[x] > a[y];
    });
    for(i = 1; i <= N; ++i){
        for(j = 0; j < P; ++j){
            scanf("%d" , &s[i][j]);
        }
    }
    memset(DP , -1 , sizeof(DP));
    DP[0] = 0;
    for(j = 0; j < N; ++j){
        x = id[j];
        for(mask = (1 << P) - 1; mask >= 0; --mask){
            if(DP[mask] == -1)continue;
            for(i = 0; i < P; ++i){ // let x do ith pos
                if((mask & (1 << i)) == 0){
                    int nmask = mask | (1 << i);
                    ll v = DP[mask] + s[x][i];
                    DP[nmask] = max(DP[nmask] , v);
                }
            }
            int np = __builtin_popcount(mask);
            if(j + 1 - np <= K){
                // x can be audience
                DP[mask] = max(DP[mask] , DP[mask] + a[x]);
            }
        }
    }
    printf("%lld\n" , DP[(1 << P) - 1]);
}