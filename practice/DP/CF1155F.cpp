// "It is guaranteed that each pair of cities have at least two paths 
// between them that don't share a single road"
// in the optimal configuration, consider path from u to v, if we remove a road in this path
// v should still be reachable from u, this property concides with the definition of biconnected component
// answer will be the minimal number of edges that we keep so that
// all N vertices are in one biconnected component
// this can be done quickly with DP
// how do we extend from our current biconnected component to so larger one?
// we can select x , y in current BCC , choose a path start from x ends at y,
// so that, no other vertices in this path belong to BCC 
#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int INF = 1e9;
int N , M;
vector<int> g[15];
int DP[1 << 14];
// min edges to put mask in some BCC
bool can[14][14][1 << 14]; 
// exists a path from x to y, using vertex in mask , and x , y not in mask ?
int lastv[14][14][1 << 14];
// last vertex in the path from x to y
int pre[1 << 14];
// previous mask
array<int , 2> endpoint[1 << 14];
// stores the endpoints for a path, x -> mask -> y

int main(){
    cin >> N >> M;
    for(int i = 1; i <= M; ++i){
        int u , v;
        cin >> u >> v;
        --u , --v;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for(int mask = 0; mask < 1 << N; ++mask){
        DP[mask] = INF;
    }
    for(int v = 0; v < N; ++v){
        for(int u = 0; u < N; ++u){
            for(int mask = 0; mask < 1 << N; ++mask){
                can[v][u][mask] = 0;
            }
        }
    }
    for(int v = 0; v < N; ++v){
        for(int u : g[v]){
            can[v][u][0] = 1;
            lastv[v][u][0] = v;
        }
    }
    for(int mask = 0; mask < 1 << N; ++mask){
        for(int x = 0; x < N; ++x){
            for(int y = 0; y < N; ++y){
                if(mask >> x & 1)continue;
                if(mask >> y & 1)continue;
                if(!can[x][y][mask])continue;
                if(x == y)continue; // we can not expand mask if x == y
                for(int ny : g[y]){
                    if(mask >> ny & 1)continue;
                    int nmask = mask | (1 << y);
                    if(lastv[x][y][mask] == ny)continue;
                    if(can[x][ny][nmask])continue;
                    can[x][ny][nmask] = 1;
                    lastv[x][ny][nmask] = y; // to avoid turning back using same vertex
                }
            }
        }
    }
    ID for(int x = 0; x < N; ++x){
        for(int y = 0; y < N; ++y){
            for(int mask = 0; mask < 1 << N; ++mask){
                if(can[x][y][mask])printf("good %d %d %d\n" , x , y , mask);
            }
        }
    }
    DP[1] = 0;
    for(int mask = 0; mask < 1 << N; ++mask){
        int cmask = ((1 << N) - 1) ^ mask;
        for(int addmask = cmask; addmask; addmask = (addmask - 1) & cmask){
            int nedges = __builtin_popcount(addmask) + 1;
            int nmask = addmask | mask;
            if(DP[mask] + nedges >= DP[nmask])continue;
            bool found = 0;
            for(int x = 0; x < N && !found; ++x){
                for(int y = 0; y < N && !found; ++y){
                    if((mask >> x & 1) && (mask >> y & 1)){
                        if(can[x][y][addmask]){
                            found = 1;
                            DP[nmask] = DP[mask] + nedges;
                            pre[nmask] = mask;
                            endpoint[nmask] = {x , y};
                        }
                    }
                }
            }
        }
    }
    ID for(int mask = 0; mask < 1 << N; ++mask)printf("DP[%d] = %d\n" , mask , DP[mask]);
    cout << DP[(1 << N) - 1] << endl;
    // show edges
    int mask = (1 << N) - 1;
    while(pre[mask]){
        //show mask ^ pre[mask];
        int cur = mask ^ pre[mask];
        int x = endpoint[mask][0] , y = endpoint[mask][1];
        while(cur){
            int ny = lastv[x][y][cur];
            cout << y + 1 << " " << ny + 1 << endl;
            cur ^= (1 << ny);
            y = ny;
        }
        cout << x + 1 << " " << y + 1 << endl;
        mask = pre[mask];
    }
}       