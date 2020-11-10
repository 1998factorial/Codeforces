#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
const int INF = 1e9 + 10;
int N;
int a[maxn];
int DP[maxn][65]; // DP[i][j] = maximal sequence ending at a[i] , where maximal value is j
int base = 31;

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j < 65; ++j){
            DP[i][j] = -INF;
        }
    }
    DP[1][base + a[1]] = a[1];
    for(int i = 2; i <= N; ++i){
        DP[i][base + a[i]] = max(DP[i][base + a[i]] + a[i] , a[i]);
        for(int j = -30; j <= 30; ++j){
            if(DP[i - 1][base + j] == -INF)continue;
            if(j > a[i]){
                DP[i][base + j] = max(DP[i][base + j] , DP[i - 1][base + j] + a[i]);
            }
            else{
                DP[i][base + a[i]] = max(DP[i - 1][base + j] + a[i] , DP[i][base + a[i]]);
            }
        }
    }
    int ans = -INF;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 65; ++j){
            if(DP[i][j] != -INF){
                ans = max(ans , DP[i][j] - (j - base));
            }
        }
    }
    printf("%d\n" , ans);
}
