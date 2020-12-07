#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a , b) for(int i = a; i >= b; --i)
using namespace std;
typedef long long ll;
const ll INF = 1e18;
int N , K;
int sz[3005];
int a[3005][3005];
ll sum[3005][3005] , DP[3005 << 2][3005] , ret = 0;

// Key: in the optimal solution, there is at most one array that is taken partially
// all other arrays are taken completely

// T(N) = 2 * T(N / 2) + O(N * K / 2)
// T(N) = O(logN * N * K)

void zero_one_bag_DP(int l , int r , int id){
    rep(i , l , r){
        rrep(j , K , sz[i]){
            DP[id][j] = max(DP[id][j] , DP[id][j - sz[i]] + sum[i][sz[i]]);
        }
    }
}

void solve(int l , int r , int id){
    if(l == r){
        rep(j , 0 , sz[l]){
            ret = max(ret , DP[id][K - j] + sum[l][j]);
        }
    }
    else{
        int mid = (l + r) >> 1;
        // assume the partial taken array is on [mid + 1 , r]
        rep(i , 0 , K){
            DP[id << 1][i] = DP[id][i];
            DP[id << 1 | 1][i] = DP[id][i];
        }
        zero_one_bag_DP(l , mid , id << 1 | 1);
        // assume the partial taken array is on [l , mid]
        zero_one_bag_DP(mid + 1 , r , id << 1);
        solve(l , mid , id << 1);
        solve(mid + 1 , r , id << 1 | 1);
    }
}

int main(){
    scanf("%d %d" , &N , &K);
    rep(i , 1 , N){
        scanf("%d" , &sz[i]);
        rep(j , 1 , sz[i]){
            int x; scanf("%d" , &x);
            if(j <= K)a[i][j] = x , sum[i][j] = sum[i][j - 1] + x;
        }
        sz[i] = min(sz[i] , K);
    }
    solve(1 , N , 1);    
    printf("%lld\n" , ret);
}