#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 10; 
const int maxn = 2e5 + 10;
vector<array<ll , 2>> g[maxn];
int N , M;
ll a[maxn] , dis[maxn];
bool vis[maxn];

/*
    double weights in G
    create extra source, link it to each vertex in G with cost = a[i]
    run dijstra from source
    answer is <dis[i]>
    why? each dis[i] will contain exactly one e(source , j) == goes to watch a concert in j
*/

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        ll u , v , w;
        scanf("%lld %lld %lld" , &u , &v , &w);
        g[u].push_back({v , w * 2});
        g[v].push_back({u , w * 2});
    }
    for(int i = 1; i <= N; ++i){
        dis[i] = INF;
        scanf("%lld" , &a[i]);
        g[0].push_back({i , a[i]});
        g[i].push_back({0 , a[i]});
    }
    priority_queue<array<ll , 2> , vector<array<ll , 2>> , greater<array<ll , 2>>> q;
    q.push({dis[0] , 0});
    while(!q.empty()){
        auto cur = q.top();
        q.pop();
        ll v = cur[1];
        if(vis[v])continue;
        vis[v] = 1;
        for(auto& e : g[v]){
            ll nv = e[0] , w = e[1];
            if(vis[nv])continue;
            if(dis[nv] > dis[v] + w){
                dis[nv] = dis[v] + w;
                q.push({dis[nv] , nv});
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        printf("%lld " , dis[i]);
    }
    printf("\n");
}   