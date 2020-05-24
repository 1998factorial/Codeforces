#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int N , M;
vector<int> g[maxn];
int DP[maxn];
bool vis[maxn];

void DFS(int v , int p){
    DP[v] = 1;
    for(int u : g[v]){
        if(u != p){
            if(!DP[u]){
                DFS(u , v);
            }
            DP[v] = max(DP[v] , DP[u] + 1);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    for(int i = 1; i <= M; ++i){
        int x , y; cin >> x >> y;
        g[x].push_back(y);
    }
    for(int i = 1; i <= N; ++i){
        if(!DP[i])
            DFS(i , -1);
    }
    int ret = 0;
    for(int i = 1; i <= N; ++i){
        ret = max(ret , DP[i]);
    }
    cout << ret - 1 << endl;
}
