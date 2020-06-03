/*
    Constructive
    Easy to find that, we will use at most 3 different colors
    If graph is bipartite, we use at most 2 colors
    If not, we use 3.
    Construct using DFS
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
int t[maxn];
int N;
int ans[maxn];
vector<int> g[maxn];

int ret = 0;

void DFS(int v , int c){
    ans[v] = c;
    if(c == 2)ret = max(ret , 2);
    for(int u : g[v]){
        if(!ans[u]){
            if(c == 1)
                DFS(u , 2);
            if(c == 2)
                DFS(u , 1);
        }
    }
    if(g[v].size() == 2){
        if(ans[v] == ans[g[v][0]] || ans[v] == ans[g[v][1]]){
            ans[v] = 3;
            ret = max(ret , 3);
        }
    }
}

int main(){
    int q;
    scanf("%d" , &q);
    while(q--){
        ret = 0;
        scanf("%d" , &N);
        for(int i = 1; i <= N; ++i){
            scanf("%d" , &t[i]);
            g[i].clear();
            ans[i] = 0;
        }
        for(int i = 1; i <= N; ++i){
            if(i == 1){
                if(t[i] != t[N]){
                    g[i].push_back(N);
                    g[N].push_back(i);
                }
            }
            else{
                if(t[i] != t[i - 1]){
                    g[i].push_back(i - 1);
                    g[i - 1].push_back(i);
                }
            }
        }
        for(int i = 1; i <= N; ++i){
            if(!ans[i]){
                ret = max(ret , 1);
                DFS(i , 1);
            }
        }
        printf("%d\n" , ret);
        for(int i = 1; i <= N; ++i){
            printf("%d " , ans[i]);
        }printf("\n");
    }
}
