/*
    Graph , MST , rating 2300
    Goal is to find a spanning tree that has exactly (N - 1) / 2 black edges
    and (N - 1) / 2 edges , clearly , if N is even there is no such answer
    then , let black edge be 1 , white be 0. we find the MST. If sum of weight of MST is
    less than (N - 1) / 2 then we have no solution. Otherwise , we should try to replace
    some 1 edges to 0 edges until the number of black edges = (N - 1) / 2
    we can do this by iterating the edges, if the current edge is not in spanning tree and it is black,
    we should try to put it into our spanning tree, this action will create a cycle , so we will need to
    remove one white edge in the cycle , this is easy.
    we remove when the spanning tree total weight = (N - 1) / 2
    if we can not make it, there is no solution.
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;

const int maxn = 1e3 + 10;
int N , M;
int fa[maxn];
set<ii> g[maxn];
bool use[100005];

struct edge{
    int x , y , w;
    edge(){}
    edge(int x_ , int y_ , int w_) : x(x_) , y(y_) , w(w_) {}
} edges[100005];

int find(int x){ // unsion find + path compression
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x , int y){ //
    x = find(x);
    y = find(y);
    if(x != y)fa[x] = y;
}

void add(int id){
    g[edges[id].x].insert(make_pair(edges[id].y , id));
    g[edges[id].y].insert(make_pair(edges[id].x , id));
    use[id] = 1;
}

void remove(int id){
    // need to remove edges[id] from spanning tree g
    int x = edges[id].x , y = edges[id].y;
    g[x].erase(g[x].find(make_pair(y , id)));
    g[y].erase(g[y].find(make_pair(x , id)));

    use[id] = 0;
}

int check(int x , int y){ // get the one of the white edge between x and y in current spanning tree
    if(x == y)return -1;
    vector<bool> vis(N + 1);
    vector<int> pre(N + 1);
    queue<int> q;
    q.push(x);
    while(!q.empty()){
        int c = q.front(); q.pop();
        if(c == y)break;
        if(!vis[c]){
            vis[c] = 1;
            for(auto& e : g[c]){
                if(!vis[e.first]){
                    q.push(e.first);
                    pre[e.first] = e.second;
                }
            }
        }
    }
    int ny = y;
    while(pre[ny]){
        int eid = pre[ny];
        if(edges[eid].w == 0)return eid;
        ny = edges[eid].x + edges[eid].y - ny;
    }
    return -1;
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i)fa[i] = i;
    for(int i = 1; i <= M; ++i){
        int x , y; char c[5];
        scanf("%d %d %s" , &x , &y , c);
        int v = c[0] == 'S' ? 0 : 1;
        edges[i] = edge(x , y , v);
    }
    if(N % 2 == 0){
        printf("-1\n");
        return 0;
    }
    // use as many white edges as possible
    int nw = 0;
    for(int i = 1; i <= M; ++i){
        if(edges[i].w == 0){
            int x = edges[i].x , y = edges[i].y;
            if(find(x) != find(y)){
                ++nw;
                merge(x , y);
                add(i);
            }
        }
    }
    if(nw < (N - 1) / 2){
        printf("-1\n");
        return 0;
    }
    int nb = 0;
    for(int i = 1; i <= M; ++i){
        if(edges[i].w == 1){
            int x = edges[i].x , y = edges[i].y;
            if(find(x) != find(y)){
                ++nb;
                merge(x , y);
                add(i);
            }
        }
    }
    if(nb + nw < N - 1){
        printf("-1\n");
        return 0;
    }
    for(int i = 1; i <= M && nw > nb; ++i){
        // try to change used white edge to black edge
        if(!use[i] && edges[i].w == 1){
            int ret = check(edges[i].x , edges[i].y);
            if(ret != -1){
                remove(ret);
                add(i);
                ++nb;--nw;
            }
        }
    }
    if(nw == nb){
        printf("%d\n" , N - 1);
        for(int i = 1; i <= M; ++i){
            if(use[i]){
                printf("%d " , i);
            }
        }
    }
    else{
        printf("-1\n");
    }
}
