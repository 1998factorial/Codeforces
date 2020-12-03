#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 10;
const int maxn = 250001;
const int maxl = 1e9 + 10;
int a[401] , s[maxn] , f[maxn] , c[maxn] , r[maxn] , N , M;
int DP[401][401][401];

int check(ll mid){
    // check if each bus routes can be finished if their tank starts with fuel = mid
    for(int i = 1; i <= M; ++i){
        if((ll)DP[s[i]][f[i]][r[i] + 1] * c[i] > mid)return 0;
    }
    return 1;
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            for(int k = 1; k <= N; ++k){
                DP[i][j][k] = i == j ? 0 : maxl;
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            DP[i][j][1] = a[j] - a[i];
        }
    }
    for(int k = 2; k <= N; ++k){
        for(int len = 2; len <= N; ++len){
            for(int i = 1; i + len - 1 <= N; ++i){
                int j = i + len - 1;
                for(int x = j; x >= i; --x){
                    DP[i][j][k] = min(DP[i][j][k] , max(DP[i][x][k - 1] , a[j] - a[x]));
                }
            }
        }
    }
    for(int i = 1; i <= M; ++i)scanf("%d %d %d %d" , &s[i] , &f[i] , &c[i] , &r[i]);
    ll l = 0 , r = INF , ans = INF;
    while(l <= r){
        ll mid = (l + r) >> 1;
        if(check(mid)){
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    printf("%lld\n" , ans);
}
