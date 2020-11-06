#include <bits/stdc++.h>
#define ID if(1)
using namespace std;

const int maxn = 1e6 + 10;
vector<int> g[maxn];
int N , K , depth[maxn] , back[maxn] , mind[maxn] , ans[maxn];

void DFS1(int v , int d){
    depth[v] = d;
    for(int u : g[v]){
        DFS1(u , d + 1);
    }
}

void DFS2(int v){
    mind[v] = N;
    if(g[v].size() == 0){
        mind[v] = depth[v];
        back[v] = 1;
    }
    else{
        for(int u : g[v]){
            DFS2(u);
            mind[v] = min(mind[v] , mind[u]);
            if(mind[u] - depth[v] <= K){
                back[v] += back[u];
            }
        }
    }
}

void DFS3(int v){
    if(g[v].size() == 0){
        ans[v] = back[v];
    }
    else{
        ans[v] = back[v];
        for(int u : g[v]){
            DFS3(u);
            if(mind[u] - depth[v] <= K){
                ans[v] = max(ans[v] , back[v] - back[u] + ans[u]);
            }
            else{
                ans[v] = max(ans[v] , back[v] + ans[u]);
            }
        }
    }
}

int main(){
    scanf("%d%d" , &N , &K);
    for(int i = 2; i <= N; ++i){
        int p; scanf("%d" , &p);
        g[p].push_back(i);
    }
    DFS1(1 , 0);
    DFS2(1);
    DFS3(1);
    printf("%d\n" , ans[1]);
}