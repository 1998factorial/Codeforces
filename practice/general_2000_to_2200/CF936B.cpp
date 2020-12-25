#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 2;
vector<int> g[maxn];
int N , s , M;
bool cycle = 0 , instack[maxn] , vis[maxn];
vector<int> out;
vector<vector<int>> pre;
int dis[maxn][2];
// Implementation
// cycle check
// BFS find the shortest win path if exists, else will MLE
// note that path length should not excceed 1e6
void BFS(){
    queue<array<int  , 2>> q;
    vector<vector<bool>> seen(N + 1 , vector<bool>(2));
    q.push({s , 0});
    while(!q.empty()){
        array<int , 2> cur = q.front();
        q.pop();
        int v = cur[0] , p = cur[1];
        if(out[v] == 0 && p)return;
        if(seen[v][p])continue;
        seen[v][p] = 1;
        for(int nv : g[v]){
            if(~pre[nv][1 - p])continue;
            pre[nv][1 - p] = v;
            dis[nv][1 - p] = dis[v][p] + 1;
            q.push({nv , 1 - p});
        }
    }
}

void DFS2(int v){ // check cycle
    vis[v] = 1;
    instack[v] = 1;
    for(int u : g[v]){
        if(vis[u]){
            if(instack[u])cycle = 1;
            return ;
        }
        DFS2(u);
    }   
    instack[v] = 0;
}

int main(){
    scanf("%d %d" , &N , &M);
    out.resize(N + 1 , 0);
    pre.resize(N + 1 , vector<int>(2 , -1));
    for(int i = 1; i <= N; ++i){
        int sz;scanf("%d" , &sz);
        out[i] += sz;
        set<int> v;
        for(int j = 1; j <= sz; ++j){
            int x;scanf("%d" , &x);
            v.insert(x);
        }
        for(int j : v){
            g[i].push_back(j);
        }
    }
    scanf("%d" , &s);
    // check if exists odd length path from s to some end point
    //DFS1(s , s , 0);
    BFS();
    int mn = 1e6;
    for(int i = 1; i <= N; ++i){
        if(out[i] == 0 && ~pre[i][1]){
            mn = min(mn , dis[i][1]);
        }
    }
    if(mn < 1000000)
    for(int i = 1; i <= N; ++i){
        if(out[i] == 0){
            if(~pre[i][1] && dis[i][1] == mn){
                printf("Win\n");
                // show path
                vector<int> path;
                int v = i , p = 1 , found = 1;
                path.push_back(v);
                while(~pre[v][p]){
                    if(v == s && p == 0)break;
                    path.push_back(pre[v][p]);
                    v = pre[v][p];
                    p = 1 - p;
                }
                reverse(path.begin() , path.end());
                if(found)for(int j : path){
                    printf("%d " , j);
                }
                printf("\n");
                return 0;
            }
        }
    }
    // cycle ? 
    DFS2(s);
    if(cycle){
        printf("Draw\n");
        return 0;
    }
    // no cycle , we lose
    printf("Lose\n");
}       