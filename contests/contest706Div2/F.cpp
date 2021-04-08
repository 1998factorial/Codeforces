/*
    Definition of BFS tree: a spanning tree rooted at x, which 
    for all vertices v in the graph, the distance between v and x
    is the minimal distance from v to x in the original graph.
    (Which is just a BFS tree that you construct when BFS from x)

    f(x , y) = number of BFS spanning tree rooting at both x and y
    goal is to compute all f(x , y)
    N <= 400 , M <= 600 , 2.5 second
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int inf = 1e9;
int N , M , dis[405][405] , vis[405];
ll ans[405][405];
vector<int> g[405];

void add(ll& x , ll& y){
    x += y;
    if(x >= mod)x -= mod;
}

void sub(ll& x , ll& y){
    x -= y;
    if(x < 0)x += mod;
}

void mul(ll& x , ll y){
    x *= y;
    x %= mod;
}

void BFS(int s){
    for(int i = 1; i <= N; ++i){
        vis[i] = 0;
    }
    dis[s][s] = 1;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        if(vis[v])continue;
        vis[v] = 1;
        for(int nv : g[v]){
            if(dis[s][nv] > dis[s][v] + 1){
                dis[s][nv] = dis[s][v] + 1;
                q.push(nv);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            dis[i][j] = inf;
        }
    }
    for(int i = 1; i <= M; ++i){
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= N; ++i){
        BFS(i);
    }
    // dis[x][y] = number of vertices on the shortest path from
    // x to y (including x and y)
    for(int x = 1; x <= N; ++x){
        for(int y = x; y <= N; ++y){
            int nmust_on_path = 0;
            for(int z = 1; z <= N; ++z){
                if(dis[x][z] + dis[z][y] - 1 == dis[x][y]){
                    ++nmust_on_path;
                }
            }
            if(nmust_on_path > dis[x][y]){
                // for a spanning tree, we can only allow 
                // exactly one shortest path from x to y
                // in this case, we will not be able to 
                // construct a BFS tree
                continue;
            }
            // if we consider single source, 
            // the solution is easy
            // for 2 sources, we treat the shortest path 
            // between them as source
            ll v = 1;
            for(int z = 1; z <= N; ++z){
                ll c = 0;
                if(dis[x][z] + dis[z][y] - 1 != dis[x][y]){
                    // z is not on the path from x to y
                    for(int v : g[z]){
                        if(
                            dis[x][v] == dis[x][z] - 1 &&
                            dis[y][v] == dis[y][z] - 1
                        ){
                            // v is z's neighbour in previous layer
                            ++c;
                        }
                    }
                    mul(v , c);
                }
            }
            ans[x][y] = ans[y][x] = v;
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}