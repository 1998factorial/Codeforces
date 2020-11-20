#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4e5 + 10;
const ll INF = 1e18;
int a[maxn] , N , cnt[maxn][20];
ll DP[1 << 20] , cost[20][20];
vector<int> pos[20];

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        --a[i];
        pos[a[i]].push_back(i);
        for(int j = 0; j < 20; ++j){
            cnt[i][j] = cnt[i - 1][j] + (a[i] == j);
        }
    }
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 20; ++j){
            if(i == j)continue;
            for(int k : pos[i]){
                cost[j][i] += cnt[k][j];
            }
        }
    }
    for(int i = 1; i < 1 << 20; ++i)DP[i] = INF;
    for(int mask = 0; mask < 1 << 20; ++mask){
        for(int i = 0; i < 20; ++i){
            if(mask & (1 << i))continue;
            ll sum = 0;
            for(int j = 0; j < 20; ++j){
                if(mask & (1 << j))sum += cost[j][i];
            }
            DP[mask ^ (1 << i)] = min(DP[mask ^ (1 << i)] , DP[mask] + sum);
        }
    }
    printf("%lld\n" , DP[(1 << 20) - 1]);
}