#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int maxn = 50005;
ll DP[maxn][505];
vector<int> g[maxn];
int N , K;
ll ans = 0;

void DFS(int v , int fa){
    DP[v][0] = 1;
    for(int u : g[v]){
        if(u == fa)continue;
        DFS(u , v);
        for(int i = 0; i < K - 1; ++i){
            ans += DP[u][i] * DP[v][K - i - 1]; 
        }
        for(int i = 0; i < K; ++i){
            DP[v][i + 1] += DP[u][i];
        }
    }
    ans += DP[v][K];
    ID for(int i = 1; i <= K; ++i){
        printf("DP[%d][%d] = %lld\n" , v , i , DP[v][i]);
    }
}

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i < N; ++i){
        int x , y;
        scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    DFS(1 , 1);
    printf("%lld\n" , ans);
}