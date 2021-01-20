#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int maxn = 3e5 + 10;
vector<int> g[maxn];
ll DP[maxn][3];

// 0 -> uncoloured , regardless of if there exist edge connecting v
// 1 -> coloured , regardless of if there exist edge connecting v
// 2 -> v is disconnected from all its child

int N;

ll sub(ll x , ll y){
    x -= y;
    if(x < 0)x += mod;
    return x;
}

ll add(ll x , ll y){
    x += y;
    if(x >= mod)x -= mod;
    return x;
}

ll mul(ll x , ll y){
    x *= y;
    x %= mod;
    return x;
}

void DFS(int v , int p){
    DP[v][0] = DP[v][1] = DP[v][2] = 1;
    for(int c : g[v]){
        if(c != p){
            DFS(c , v);
            // v is uncoloured
            // do not pick (v , c)
            ll v1 = sub(add(DP[c][0] , DP[c][1]) , DP[c][2]); // exists case, where c is coloured but isolated
            // pick (v , c)
            ll v2 = add(DP[c][0] , DP[c][1]); // both cases for c work
            DP[v][0] = mul(DP[v][0] , add(v1 , v2));
            // v is coloured
            // do not pick (v , c)
            v1 = sub(add(DP[c][0] , DP[c][1]) , DP[c][2]); // c is coloured and isolated
            // pick (v , c)
            v2 = DP[c][0]; // we can not colour c
            DP[v][1] = mul(DP[v][1] , add(v1 , v2));
            // v is isolated from its child
            DP[v][2] = mul(DP[v][2] , sub(add(DP[c][0] , DP[c][1]) , DP[c][2]));
        }
    }
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i < N; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    DFS(1 , 1);
    printf("%lld\n" , sub(add(DP[1][0] , DP[1][1]) , add(DP[1][2] , 1ll)));
}