/*
    Graph, Euler cycle , 2200
    if all vertices have even degree, then the answer is just the euler cycle
    key: the number of odd degree vertices must be even (because the sum of the degree is even (each edge is counted twice))
    So, if we gather all odd degree vertices and link them to a super node "N + 1" then all degrees will be even and
    we will have an euler cycle
*/
#include <bits/stdc++.h>
using namespace std;

int N , M;
int g[205][205];
int deg[205];

void DFS(int v){
    for(int i = 1; i <= N + 1; ++i){
        if(g[v][i]){
            if(i != N + 1 && v != N + 1){
                cout << v << " " << i << endl;
            }
            --g[v][i]; --g[i][v];
            DFS(i);
        }
    }
}

int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> N >> M;
        memset(g , 0 , sizeof(g));
        memset(deg , 0 , sizeof(deg));
        for(int i = 1; i <= M; ++i){
            int x , y; cin >> x >> y;
            g[x][y] = g[y][x] = 1;
            ++deg[x]; ++deg[y];
        }
        int cnt = 0;
        for(int i = 1; i <= N; ++i){
            if(deg[i] & 1){
                ++cnt;
                ++g[i][N + 1]; ++g[N + 1][i];
            }
        }
        cout << N - cnt << endl;
        for(int i = 1; i <= N + 1; ++i){
            DFS(i);
        }
    }
}
