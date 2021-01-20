#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const ll INF = 1e18 + 10;
int N , K , a[maxn];
int pos[maxn] , M = 0 , mp[maxn];
ll DP[maxn][102]; 
int cnt[105]; 
ll cost[maxn]; // # of inversions if we put j on pos[i]

ll cal(int l , int r){
    return cost[r] - cost[l - 1];
}

void solve(int l , int r , int x , int y , int k){
    if(l > r)return;
    int mid = (l + r) >> 1;
    int pos = -1;
    DP[mid][k] = DP[mid][k + 1];
    for(int i = max(1 , x); i <= min(y , mid); ++i){
        ll C = cal(i , mid) + (ll)(i - 1) * (mid - i + 1);
        if(DP[mid][k] < DP[i - 1][k + 1] + C){
            DP[mid][k] = DP[i - 1][k + 1] + C;
            pos = i;
        }
    }
    solve(l , mid - 1 , x , pos , k);
    solve(mid + 1 , r , pos , y , k);
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
                ans += cnt[j];
            }
            ++cnt[a[i]];
        }
    }
    for(int i = 0; i <= M; ++i){
        for(int j = 0; j <= K; ++j){
            DP[i][j] = -INF;
        }
    }
    int v = 0;
    for(int i = 1; i <= N; ++i){
        if(mp[i]){
            cost[mp[i]] += v;
        }
        else if(a[i] > K)++v;
    }
    v = 0;
    for(int i = N; i >= 1; --i){
        if(mp[i]){
            cost[mp[i]] += v;
        }
        else if(a[i] < K)++v;
    }
    for(int i = 1; i <= M; ++i){
        cost[i] += cost[i - 1];
    }
    for(int i = 1; i <= M; ++i){
        DP[i][K] = cost[i];
    }
    DP[0][K] = 0;
    for(int j = K - 1; j >= 1; --j){
        int v = 0;
        for(int i = 1; i <= M; ++i)cost[i] = 0;
        for(int i = 1; i <= N; ++i){
            if(mp[i]){
                cost[mp[i]] += v;
            }
            else if(a[i] > j)++v;
        }
        v = 0;
        for(int i = N; i >= 1; --i){
            if(mp[i]){
                cost[mp[i]] += v;
            }
            else if(a[i] < j)++v;
        }
        for(int i = 1; i <= M; ++i){
            cost[i] += cost[i - 1];
        }
        solve(1 , M , 1 , M , j);
    }
    if(DP[M][1] >= 0)ans += DP[M][1];
    printf("%lld\n" , ans);
}