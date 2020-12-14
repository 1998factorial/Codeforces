#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int maxn = 1e4;
const int INF = 1e9;
int N , M , G , R;
int dis[maxn][2000];
vector<int> d;

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 0; i < M; ++i){
        int x;
        scanf("%d" , &x);
        d.push_back(x);
    }
    scanf("%d %d" , &G , &R);
    sort(d.begin() , d.end());
    // run 0-1 BFS
    for(int v = 0; v < M; ++v){
        for(int t = 0; t < G + R; ++t){
            dis[v][t] = INF;
        }
    }
    dis[0][0] = 0;
    deque<array<int , 2>> q;
    q.push_front({0 , 0});
    while(!q.empty()){
        auto c = q.front();
        q.pop_front();
        int v = c[0] , t = c[1];
        if(t < G){
            int nv = (v + 1) % M;
            int pv = (v - 1 + M) % M;
            int tl = G - t , dn = d[nv] - d[v] , dp = d[v] - d[pv];
            if(dn <= tl && v < M - 1){
                int nt = (t + dn) % (G + R);
                if(dis[nv][nt] > dis[v][t]){
                    dis[nv][nt] = dis[v][t];
                    q.push_front({nv , nt});
                }
            }
            if(dp <= tl && v > 0){
                int nt = (t + dp) % (G + R);
                if(dis[pv][nt] > dis[v][t]){
                    dis[pv][nt] = dis[v][t];
                    q.push_front({pv , nt});
                }
            }
        }
        else{
            int nt = (t + 1) % (G + R);
            int w = (t == G + R - 1 ? 1 : 0);
            if(dis[v][nt] > dis[v][t] + w){
                dis[v][nt] = dis[v][t] + w;
                if(w)q.push_back({v , nt});
                else q.push_front({v , nt});
            }
        }
    }
    int ret = INF;
    for(int t = 0; t < G + R; ++t){
        ret = min(ret , dis[M - 1][t]);
    }
    if(ret == INF){
        printf("-1\n");
    }
    else{
        for(int t = 0; t < G + R; ++t){
            if(ret == dis[M - 1][t]){
                printf("%d\n" , ret * (G + R) + t);
                return 0;
            }
        }
    }
}