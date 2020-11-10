#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// TODO

const int maxn = 1e5 + 10;
vector<int> g[maxn];
int N;
ll mod;
ll DP[maxn][2];

void DFS(int v , int p){
    DP[v][1] = DP[v][0] = 1;
    for(int u : g[v]){
        if(u != p){
            DFS(u , v);
            DP[v][1] = (DP[v][1] * (DP[u][1] + DP[u][0]) % mod) % mod;
            DP[v][0] = (DP[v][0] * DP[u][0]) % mod;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> mod;
    for(int i = 1; i < N; ++i){
        int x , y; cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int start = 1;
    while(start <= N && g[start].size() > 1)++start;
    DFS(start , -1);
    cout << (DP[start][0] + DP[start][1] + N) % mod << endl;
}
