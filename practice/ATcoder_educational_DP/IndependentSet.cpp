#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 1e5 + 10;
int N;
ll DP[maxn][2];
vector<int> g[maxn];

void DFS(int v , int p){
    DP[v][0] = DP[v][1] = 1;
    for(int u : g[v]){
        if(u != p){
            DFS(u , v);
            DP[v][0] = (DP[v][0] * (DP[u][0] + DP[u][1]) % mod) % mod;
            DP[v][1] = DP[v][1] * DP[u][0] % mod;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    if(N == 1){
        cout << 2 << endl;
        return 0;
    }
    for(int i = 1; i <= N - 1; ++i){
        int x , y; cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int start = 1;
    for(; start <= N; ++start){
        if(g[start].size() == 1){
            break;
        }
    }
    DFS(start , -1);
    cout << (DP[start][0] + DP[start][1]) % mod << endl;
}
