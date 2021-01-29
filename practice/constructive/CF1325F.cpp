#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
vector<int> g[maxn];
int N , M , dep[maxn] , cnt[maxn] , fa[maxn] , vis[maxn] , L;
// construct the DFS tree, if there is a back edge that
// links back from v to some u such that , dep[v] - dep[u] >= ceil(sqrt(N)) - 1
// then we have a cycle of ceil(sqrt(N)) vertices

// otherwise, all back edges go back to at most ceil(sqrt(N)) - 2
// if we use mod ceil(sqrt(N)) - 1 to divide vertices into groups
// we have ceil(N / (ceil(sqrt(N)) - 1)) >= ceil(sqrt(N))

void DFS(int v , int p , int d){
    vis[v] = 1;
    dep[v] = d;
    for(int nv : g[v]){
        if(vis[nv] && dep[v] - dep[nv] >= L){ // we find this cycle
            int x = v;
            vector<int> ans;
            while(x != nv){
                ans.push_back(x);
                x = fa[x];
            }
            ans.push_back(nv);
            printf("2\n");
            printf("%d\n" , (int)ans.size());
            for(int i : ans){
                printf("%d " , i);
            }
            printf("\n");
            exit(0);
        }
        else if(!vis[nv]){
            fa[nv] = v;
            DFS(nv , v , d + 1);
        }
    }
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }   
    L = ceil(sqrt(N)) - 1;
    DFS(1 , 1 , 1);
    // find independent set 
    for(int i = 1; i <= N; ++i){
        assert(ceil(N / (ceil(sqrt(N)) - 1)) >= ceil(sqrt(N)));
    }
    for(int i = 1; i <= N; ++i){
        ++cnt[dep[i] % L];
    }
    int mx = 0 , best = -1;
    for(int i = 0; i < L; ++i){
        if(mx < cnt[i]){
            mx = cnt[i];
            best = i;
        }
    }
    printf("1\n");
    vector<int> ans;
    for(int i = 1; i <= N; ++i){
        if(dep[i] % L == best % L){
            if(ans.size() >= L + 1)continue;
            ans.push_back(i);
        }
    }
    for(int i : ans){
        printf("%d " , i);
    }
    printf("\n");
}   