#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// observation:
// reverse at most log(M) times , we can build a layer graph
// when # transpose > log(M) , we want to first minimise the number of times 
// we transpose, then the number of times of traverse
const int INF = 1e9 + 10;
const int maxn = 2e5 + 10;
const int MOD = 998244353;
int N , M;
vector<array<int , 3>> g[maxn][25];
int dis[maxn][25];
bool vis[maxn][25];
vector<array<int , 4>> g2[maxn][3]; // (x , y , op2 , op1)
array<int , 2> dis2[maxn][3];
bool vis2[maxn][3];
ll p[maxn];

int main(){
    scanf("%d %d" , &N , &M);
    int L = ceil(log2(M));
    for(int i = 1; i <= M; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        for(int j = 1; j <= L; ++j){
            if(j & 1)g[u][j].push_back({v , j , 1});
            else g[v][j].push_back({u , j , 1});
        }
        g2[u][1].push_back({v , 1 , 0 , 1});
        g2[v][2].push_back({u , 2 , 0 , 1});
    }
    for(int i = 1; i <= N; ++i){
        g2[i][1].push_back({i , 2 , 1 , 0});
        g2[i][2].push_back({i , 1 , 1 , 0});
    }
    for(int j = 1; j < L; ++j){
        for(int i = 1; i <= N; ++i){
            g[i][j].push_back({i , j + 1 , 1 << (j - 1)});
        }
    }
    for(int j = 1; j <= L; ++j){
        for(int i = 1; i <= N; ++i){
            dis[i][j] = INF;
            vis[i][j] = 0;
        }
    }
    dis[1][1] = 0;
    priority_queue<array<int , 3> , vector<array<int , 3>> , greater<array<int , 3>>> q;
    q.push({dis[1][1] , 1 , 1});
    while(!q.empty()){
        array<int , 3> cur = q.top();
        q.pop();
        int w = cur[0] , x = cur[1] , y = cur[2];
        if(vis[x][y])continue;
        vis[x][y] = 1;
        for(array<int , 3>& e : g[x][y]){
            int nx = e[0] , ny = e[1] , nw = e[2];
            if(vis[nx][ny])continue;
            if(dis[nx][ny] > w + nw){
                dis[nx][ny] = w + nw;
                q.push({dis[nx][ny] , nx , ny});
            }
        }
    }
    int ans = INF;
    int found = 0;
    for(int j = 1; j <= L; ++j){
        if(vis[N][j]){
            found = 1;
            ans = min(ans , dis[N][j]);
        }
    }
    if(found){
        printf("%d\n" , ans % MOD);
        return 0;
    }
    // now we need to transpose more than logM
    for(int j = 1; j <= 2; ++j){
        for(int i = 1; i <= N; ++i){
            dis2[i][j] = {INF , INF};
            vis2[i][j] = 0;
        }
    }
    dis2[1][1] = {0 , 0};
    priority_queue<array<int , 4> , vector<array<int , 4>> , greater<array<int , 4>>> q2;
    q2.push({0 , 0 , 1 , 1});
    while(!q2.empty()){
        array<int , 4> cur = q2.top();
        q2.pop();
        int x = cur[2] , y = cur[3];
        array<int , 2> w = {cur[0] , cur[1]};
        if(vis2[x][y])continue;
        vis2[x][y] = 1;
        for(array<int , 4>& e : g2[x][y]){
            int nx = e[0] , ny = e[1];
            if(vis2[nx][ny])continue;
            array<int , 2> nw = {e[2] , e[3]};
            nw[0] += w[0];
            nw[1] += w[1];
            if(dis2[nx][ny] > nw){
                dis2[nx][ny] = nw;
                q2.push({dis2[nx][ny][0] , dis2[nx][ny][1] , nx , ny});
            }
        }
    }
    array<int , 2> ans2 = {INF , INF};
    for(int j = 1; j <= 2; ++j){
        ans2 = min(ans2 , dis2[N][j]);
    }
    p[0] = 1;
    for(int i = 1; i <= M; ++i)p[i] = p[i - 1] * 2 % MOD;
    ll v = (ans2[1] + p[ans2[0]] - 1 + MOD) % MOD;
    printf("%lld\n" , v);
}