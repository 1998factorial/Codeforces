#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const ll inf = 1e10;
const int maxn = 1e5 + 10;
int N , M , sx , sy , fx , fy , ncol = 0 , nrow = 0;
map<int , int> colmp , rowmp , colimp , rowimp;
array<int , 2> pt[maxn];
vector<array<int , 2>> g[maxn * 4];
ll dis[maxn * 4];
bool vis[maxn * 4];

// src : 0 , target : 1 , row : 2 ,..., nrow + 1
// col : nrow + 2 ,..., nrow + 1 + ncol

void dijstra(int lim){
    for(int i = 0; i <= lim; ++i){
        vis[i] = 0;
        dis[i] = inf; 
    }
    dis[0] = 0;
    priority_queue<array<ll , 2> , vector<array<ll , 2>> , greater<array<ll , 2>>> q;
    q.push({dis[0] , 0});
    while(!q.empty()){
        auto c = q.top();
        q.pop();
        ll d = c[0] , v = c[1];
        if(vis[v])continue;
        vis[v] = 1;
        for(auto& e : g[v]){
            int nv = e[0] , w = e[1];
            if(vis[nv])continue;
            if(dis[nv] > d + w){
                dis[nv] = d + w;
                q.push({dis[nv] , nv});
            }
        }
    }
}

void solve(){
    cin >> N >> M;
    cin >> sx >> sy >> fx >> fy;
    vector<int> tmp1 , tmp2;
    for(int i = 1; i <= M; ++i){
        cin >> pt[i][0] >> pt[i][1];
        tmp1.push_back(pt[i][0]);
        tmp2.push_back(pt[i][1]);
    }
    sort(tmp1.begin() , tmp1.end());
    sort(tmp2.begin() , tmp2.end());
    for(int i : tmp1){
        if(!rowmp[i]){
            rowmp[i] = ++nrow;
            rowimp[nrow] = i;
        }
    }
    for(int i : tmp2){
        if(!colmp[i]){
            colmp[i] = ++ncol;
            colimp[ncol] = i;
        }
    }
    int src = 0 , tg = 1;
    for(int i = 2; i <= nrow; ++i){
        int id = i + 1;
        g[id].push_back({id - 1 , rowimp[i] - rowimp[i - 1]});
        g[id - 1].push_back({id , rowimp[i] - rowimp[i - 1]});
    }
    for(int i = 2; i <= ncol; ++i){
        int id = nrow + i + 1;
        g[id].push_back({id - 1 , colimp[i] - colimp[i - 1]});
        g[id - 1].push_back({id , colimp[i] - colimp[i - 1]});
    }
    for(int i = 1; i <= nrow; ++i){
        int id = i + 1;
        g[src].push_back({id , abs(rowimp[i] - sx)});
    }
    for(int i = 1; i <= ncol; ++i){
        int id = nrow + i + 1;
        g[src].push_back({id , abs(colimp[i] - sy)});
    }
    for(int i = 1; i <= M; ++i){
        int row_id = rowmp[pt[i][0]] + 1;
        int col_id = colmp[pt[i][1]] + 1 + nrow;
        int v = ncol + nrow + 1 + i;
        int w = abs(fx - pt[i][0]) + abs(fy - pt[i][1]);
        g[v].push_back({row_id , 0});
        g[row_id].push_back({v , 0});
        g[v].push_back({col_id , 0});
        g[col_id].push_back({v , 0});
        g[row_id].push_back({tg , w});
        g[col_id].push_back({tg , w});
    }
    g[src].push_back({tg , abs(sx - fx) + abs(sy - fy)});
    dijstra(nrow + ncol + 1 + M);
    cout << dis[1] << endl;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    while(t--){
        solve();
    }
}