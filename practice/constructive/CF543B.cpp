#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int N , M;
vector<int> g[3005];
int dis[3005][3005] , s1 , t1 , l1 , s2 , t2 , l2;

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    scanf("%d %d %d" , &s1 , &t1 , &l1);
    scanf("%d %d %d" , &s2 , &t2 , &l2);
    // goal is to find the maximal number of edges 
    // that appears in both the shorest path from s1 to t1
    // as well as the shortest path from s2 to t2
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            dis[i][j] = INF;
        }
    }
    for(int v = 1; v <= N; ++v){
        dis[v][v] = 0;
        queue<int> q;
        q.push(v);
        while(!q.empty()){
            int c = q.front();
            q.pop();
            for(int u : g[c]){
                if(dis[v][u] >= INF){
                    dis[v][u] = dis[v][c] + 1;
                    q.push(u);
                }
            }
        }
    }
    int ans = -1;
    // if they do not intersect
    if(dis[s1][t1] <= l1 && dis[s2][t2] <= l2){
        ans = max(ans , M - (dis[s1][t1] + dis[s2][t2]));
    }
    // if they intersect, we enumerate the simple path of intersection
    // as it looks like "H"
    // be careful here, as s1 can be in the same side as s2 or t2
    for(int y = 0; y < 2; ++y){
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= N; ++j){
                int d1 = dis[s1][i] + dis[i][j] + dis[j][t1];
                int d2 = dis[s2][i] + dis[i][j] + dis[j][t2];
                if(d1 <= l1 && d2 <= l2){
                    ans = max(ans , M - (d1 + d2 - dis[i][j]));
                }
            }
        }
        swap(s2 , t2);
    }
    printf("%d\n" , ans);
}
