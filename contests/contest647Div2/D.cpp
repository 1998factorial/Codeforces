#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
int N , M;
int p[maxn] , t[maxn] , mark[maxn] , cnt = 0;
vector<int> g[maxn] , order[maxn];
int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        int x , y;
        scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &t[i]);
        order[t[i]].push_back(i);
    }
    for(int i = 1; i <= N; ++i){
        for(int v : order[i]){
            p[++cnt] = v;
            mark[v] = cnt;
        }
        for(int v : order[i]){
            set<int> vis;
            for(int nv : g[v]){
                if(mark[nv]){
                    vis.insert(t[nv]);
                }
            }
            if(vis.size() != t[v] - 1){
                printf("-1\n");
                return 0;
            }
            if(!vis.empty() && *vis.rbegin() >= i){
                printf("-1\n");
                return 0;
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        printf("%d " , p[i]);
    }
}