#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const ll INF = 1e18 + 10;
int N , K , a[maxn];
int pos[maxn] , M = 0 , mp[maxn];
ll DP[maxn][105]; 
ll cnt[maxn][105]; 
ll cost[maxn][105]; // # of inversions if we put j on pos[i]
ll costsum[maxn][105];

ll cal(int l , int r , int k){
    return costsum[r][k] - costsum[l - 1][k];
}

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int i = 1; i <= N; ++i){    
        if(!a[i]){
            pos[++M] = i;
            mp[i] = M;
        }
    }
    ll ans = 0;
    for(int i = 1; i <= N; ++i){
        if(a[i]){
            for(int j = a[i] + 1; j <= K; ++j){
                ans += cnt[i - 1][j];
            }
            ++cnt[i][a[i]];
        }
        for(int j = 1; j <= K; ++j){
            cnt[i][j] += cnt[i - 1][j];
        }
    }
    for(int j = K; j >= 1; --j){ // place j    
        int v = 0;
        for(int i = 1; i <= N; ++i){
            if(mp[i]){
                cost[mp[i]][j] += v;
                //printf("cost[%d][%d] = %lld\n" , mp[i] , j , cost[mp[i]][j]);
            }
            else if(a[i] > j)++v;
        }
    }
    for(int j = K; j >= 1; --j){
        int v = 0;
        for(int i = N; i >= 1; --i){
            if(mp[i]){
                cost[mp[i]][j] += v;
            }
            else if(a[i] < j)++v;
        }
    }
    for(int i = 1; i <= M; ++i){
        for(int j = 1; j <= K; ++j){
            costsum[i][j] = costsum[i - 1][j] + cost[i][j];
        }
    }
    for(int i = 0; i <= M; ++i){
        for(int j = 0; j <= K; ++j){
            DP[i][j] = -INF;
        }
    }
    for(int i = 1; i <= M; ++i){
        DP[i][K] = costsum[i][K];
    }
    DP[0][K] = 0;
    for(int j = K - 1; j >= 1; --j){
        for(int i = 1; i <= N; ++i){
            DP[i][j] = max(DP[i][j] , DP[i][j + 1]);
            for(int k = i - 1; k >= 0; --k){
                DP[i][j] = max(DP[i][j] , DP[k][j + 1] + cal(k + 1 , i , j) + k);
            }
        }
    }
    if(DP[M][1] >= 0)ans += DP[M][1];
    printf("%lld\n" , ans);
}