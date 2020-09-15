#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const ll INF = 1e12;
int N , M , S , R;
vector<vector<int>> g;
vector<vector<ll>> dis;
vector<vector<int>> stones;
vector<vector<int>> recipes;
vector<vector<bool>> vis;
vector<int> outcome;

ll solve(){
    scanf("%d %d %d %d" , &N , &M , &S , &R);
    g = vector<vector<int>> (N + 1);
    stones = vector<vector<int>> (N + 1);
    dis = vector<vector<ll>> (N + 1 , vector<ll> (S + 1 , INF));
    vis = vector<vector<bool>> (N + 1 , vector<bool> (S + 1 , 0));
    recipes = vector<vector<int>> (R);
    outcome = vector<int> (R);
    priority_queue<pair<ll , ii> , vector<pair<ll , ii>> , greater<pair<ll , ii>>> q;
    for(int i = 1; i <= M; ++i){
        int u , v; scanf("%d %d" , &u , &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= N; ++i){
        int sz; scanf("%d" , &sz);
        stones[i] = vector<int> (sz);
        for(int j = 0; j < sz; ++j){
            scanf("%d" , &stones[i][j]);
            dis[i][stones[i][j]] = 0;
            q.push(make_pair(0 , make_pair(i , stones[i][j])));
        }
    }
    for(int i = 0; i < R; ++i){
        int sz; scanf("%d" , &sz);
        recipes[i] = vector<int> (sz);
        for(int j = 0; j < sz; ++j){
            scanf("%d" , &recipes[i][j]);
        }
        scanf("%d" , &outcome[i]);
    }
    while(!q.empty()){
        auto cur = q.top();
        q.pop();
        int v = cur.y.x , c = cur.y.y;
        ll w = cur.x;
        if(vis[v][c])continue;
        vis[v][c] = 1;
        for(int u : g[v]){
            if(dis[u][c] > dis[v][c] + 1){
                dis[u][c] = dis[v][c] + 1;
                q.push(make_pair(dis[u][c] , make_pair(u , c)));
            }
        }
        for(int i = 0; i < R; ++i){
            if(find(recipes[i].begin() , recipes[i].end() , c) != recipes[i].end()){
                ll sum = 0;
                for(int j : recipes[i]){
                    sum += dis[v][j];
                }
                if(dis[v][outcome[i]] > sum){
                    dis[v][outcome[i]] = sum;
                    q.push(make_pair(dis[v][outcome[i]] , make_pair(v , outcome[i])));
                }
            }
        }
    }
    ll ans = INF;
    for(int i = 1; i <= N; ++i){
        ans = min(ans , dis[i][1]);
    }
    return ans >= INF ? -1 : ans;
}

int main(){
    int T; scanf("%d" , &T);
    for(int t = 1; t <= T; ++t){
        printf("Case #%d: %lld\n" , t , solve());
    }
}