#include <bits/stdc++.h>
using namespace std;

/*
    NIM game stair case, notice that coins at even distance are useless to game state
*/

const int maxn = 5e4 + 10;
int N , Q;
vector<int> g[maxn];
int ncoin[maxn];
int fa[maxn];
int dis[maxn];
int DP[maxn][2]; // 0 even dis , 1 odd dis
int tin[maxn] , tout[maxn];
int tot = 1;

void DFS(int v , int p , int d){
    dis[v] = d;
    DP[v][0] = ncoin[v];
    DP[v][1] = 0;
    tin[v] = tot++;
    for(int u : g[v]){
        if(u != p){
            DFS(u , v , d + 1);
            DP[v][0] ^= DP[u][1];
            DP[v][1] ^= DP[u][0];
        }
    }
    tout[v] = tot;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; ++i){
        cin >> ncoin[i];
    }
    for(int i = 1; i < N; ++i){
        int x , y; cin >> x >> y;
        fa[y] = x;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    DFS(1 , 1 , 0);
    cin >> Q;
    for(int q = 1; q <= Q; ++q){
        int x , y; cin >> x >> y;
        //check if cycle
        if(tin[x] <= tin[y] && tout[x] >= tout[y]){
            cout << "INVALID\n";
        }
        else{
            if((dis[y] + 1) % 2 == dis[x] % 2){
                if(DP[1][1])cout << "YES\n";
                else cout << "NO\n";
            }
            else{
                if(DP[1][1] ^ DP[x][0] ^ DP[x][1])cout << "YES\n";
                else cout << "NO\n";
            }
        }
    }
}
