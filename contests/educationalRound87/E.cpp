/*
    Bipartite graph + Dynamic programming
    Each 2 is connected to either 1 or 3
    G is not bipartite / can not make N2 nodes from connected components to be 2 -> NO
    let DP[i][j] = can we have a total of j nodes to be labeled as 2 in first i components?
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e3 + 10;
int N , M;
int N1 , N2 , N3;
vector<int> g[maxn];
int DP[maxn][maxn]; // DP[i][j] = can we make total number of j using first i connected components?
// if -1 means we can not , if 0 means we use all the whites of the ith component
// if 1 means we use all the blacks of the ith component
vector<int> comp[maxn][2]; // group each connected component by blacks/whites
int tot;
int color[maxn];
int Bipartite;
int ans[maxn];

void show(){
    for(int i = 1; i <= tot; ++i){
        for(int j = 0; j < 2; ++j){
            printf("comp[%d][%d] ->  " , i , j);
            for(int k : comp[i][j]){
                printf("%d " , k);
            }
            puts("\n");
        }
    }
}

void DFS(int v , int c){
    color[v] = c;
    comp[tot][c].push_back(v);
    for(int u : g[v]){
        if(color[u] == -1){
            DFS(u , 1 - c);
        }
        else if(color[u] == color[v]){
            Bipartite = 0;
        }
    }
}

int main(){
    tot = 0;
    Bipartite = 1;
    scanf("%d %d" , &N , &M);
    scanf("%d %d %d" , &N1 , &N2 , &N3);
    for(int i = 1; i <= N; ++i)color[i] = -1;
    for(int i = 1; i <= M; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i = 1; i <= N; ++i){
        if(color[i] == -1){
            ++tot;
            DFS(i , 0);
        }
    }
    if(Bipartite == 0){
        printf("NO\n");
        return 0;
    }
    for(int i = 0; i <= tot; ++i){
        for(int j = 0; j <= N2; ++j){
            DP[i][j] = -1;
        }
    }
    DP[0][0] = 0;
    for(int i = 1; i <= tot; ++i){
        for(int j = 0; j <= N2; ++j){
            int sz1 = comp[i][0].size(); // white
            int sz2 = comp[i][1].size(); // black
            if(j - sz1 >= 0 && DP[i - 1][j - sz1] != -1){
                DP[i][j] = 0; // let whites be 2 , blacks be 1 or 3
            }
            if(j - sz2 >= 0 && DP[i - 1][j - sz2] != -1){
                DP[i][j] = 1; // let whites be 1 or 3 , blacks be 2
            }
        }
    }
    if(DP[tot][N2] == -1){
        printf("NO\n");
        return 0;
    }
    int sz = N2;
    for(int i = tot; i >= 1; --i){
        if(DP[i][sz] == 0){
            for(int j : comp[i][0]){
                ans[j] = 2;
            }
            for(int j : comp[i][1]){
                ans[j] = 1;
            }
            sz -= comp[i][0].size();
        }
        else if(DP[i][sz] == 1){
            for(int j : comp[i][0]){
                ans[j] = 1;
            }
            for(int j : comp[i][1]){
                ans[j] = 2;
            }
            sz -= comp[i][1].size();
        }
    }
    printf("YES\n");
    sz = 0;
    for(int i = 1; i <= N; ++i){
        if(ans[i] == 1)++sz;
        if(ans[i] == 1 && sz > N1){
            ans[i] = 3;
        }
        printf("%d" , ans[i]);
    }
    puts("\n");
}
