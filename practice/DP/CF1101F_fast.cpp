#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 10;
const int maxn = 250003;
const int maxl = 1e9 + 10;
int a[403] , N , M;
int DP[403][403][403];

void solve(int L , int R , int x , int y , int k , int start){
    if(x >= y)return;
    int best = -1;
    int mid = (x + y) >> 1;
    DP[start][mid][k] = maxl;
    for(int i = L; i <= R && i <= mid; ++i){
        int val = max(DP[start][i][k - 1] , a[mid] - a[i]);
        if(val < DP[start][mid][k]){
            DP[start][mid][k] = val;
            best = i;
        }
    }
    //printf("DP[%d][%d][%d] = %d\n" , start , mid , k , DP[start][mid][k]);
    solve(L , best , x , mid , k , start);
    solve(best , R , mid + 1 , y , k , start);
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            for(int k = 0; k <= N; ++k){
                DP[i][j][k] = i == j ? 0 : maxl;
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = i; j <= N; ++j){
            DP[i][j][0] = a[j] - a[i];
        }
    }
    for(int k = 1; k <= N; ++k){    
        for(int i = 1; i <= N; ++i){
            solve(i , N , i , N + 1 , k , i);
        }
    }
    ll ans = 0;
    for(int i = 1; i <= M; ++i){
        int s , f , c , r;
        scanf("%d %d %d %d" , &s , &f , &c , &r);
        ans = max(ans , (ll)DP[s][f][r] * c);
    }
    printf("%lld\n" , ans);
}
