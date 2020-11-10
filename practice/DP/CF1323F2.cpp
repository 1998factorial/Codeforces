#include <bits/stdc++.h>
#define ID if(1)
using namespace std;
const int INF = 1e9;
int DP[4005][2005];
int N , M;
int l[2005] , s[2005] , c[4005];

int main(){
    int i , j , k;
    scanf("%d%d" , &N , &M);
    // reverse final cost = normal final cost
    // we need to find a non-decreasing sequence
    for(i = N; i >= 1; --i)scanf("%d" , &l[i]);
    for(i = N; i >= 1; --i)scanf("%d" , &s[i]);
    for(i = 1; i <= N + M; ++i)scanf("%d" , &c[i]);
    for(i = 1; i <= N + M; ++i){
        for(j = 1; j <= N; ++j){
            DP[i][j] = -INF;
        }
    }
    for(i = 1; i <= N; ++i){
        int mv = l[i]; // current maximal agg
        // we can get rid of the init step by doing DP in reverse order
        for(j = i; j >= 1; --j){
            DP[mv][j] = max(DP[mv][j] , DP[mv][j - 1] + c[mv] - s[i]);
        }
        for(j = mv; j <= N + M; ++j){
            for(k = i >> (j - mv); k >= 0; --k){
                DP[j + 1][k / 2] = max(DP[j + 1][k / 2] , DP[j][k] + (k / 2) * c[j + 1]);
            }
        }
    }
    int ans = 0;
    for(i = 1; i <= N + M; ++i){
        for(j = 0; j < 2; ++j){
            ans = max(ans , DP[i][j]);
        }
    }
    printf("%d\n" , ans);
}