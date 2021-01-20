#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int INF = 1e9;
ll a[maxn];
vector<int> bits[65];
int N;
vector<int> g[maxn];
int dis[maxn];

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &a[i]);
    }
    for(int i = 0; i <= 62; ++i){
        for(int j = 1; j <= N; ++j){
            if(a[j] & (1ll << i)){
                bits[i].push_back(j);
            }
        }
        if(bits[i].size() >= 3){
            printf("3\n");
            return 0;
        }
    }
    int ret = INF;
    for(int i = 0; i <= 62; ++i){
        if(bits[i].size() < 2)continue;
        if(bits[i][0] > bits[i][1])swap(bits[i][0] , bits[i][1]);
        for(int j = 1; j <= N; ++j){
            g[j].clear();
            dis[j] = INF;
        }
        set<array<int , 2>> vis;
        vis.insert({bits[i][0] , bits[i][1]});
        for(int j = 0; j <= 62; ++j){
            if(j == i)continue;
            if(bits[j].size() < 2)continue;
            if(bits[j][0] > bits[j][1])swap(bits[j][0] , bits[j][1]);
            if(vis.find({bits[j][0] , bits[j][1]}) != vis.end())continue;
            g[bits[j][0]].push_back(bits[j][1]);
            g[bits[j][1]].push_back(bits[j][0]);
            vis.insert({bits[j][0] , bits[j][1]});
        }
        int u = bits[i][0] , v = bits[i][1];
        // find min distance from u to v
        dis[u] = 0;
        queue<int> q;
        q.push(u);
        while(!q.empty()){
            int cv = q.front();
            q.pop();
            for(int nv : g[cv]){
                if(dis[nv] == INF){
                    dis[nv] = dis[cv] + 1;
                    q.push({nv});
                }
            }
        }
        ret = min(ret , 1 + dis[v]);
    }
    printf("%d\n" , (ret >= INF ? -1 : ret));
}