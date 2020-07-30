#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(1)
using namespace std;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
vector<int> g[maxn]; // graph
vector<int> *vec[maxn]; // vertices in my subtree
vector<ii> qs[maxn]; // query related to this vertex
map<string , int> cnt[maxn]; // store the # of occ of string on a depth of subtree
set<string> onlevel[maxn]; // store the set of strings on a depth of subtree
int sz[maxn];
int depth[maxn];
int ans[maxn];
int N , Q;
bool root[maxn];
string name[maxn];

void getsz(int v , int p , int d){
    sz[v] = 1;
    depth[v] = d;
    for(int u : g[v]){
        if(u != p){
            getsz(u , v , d + 1);
            sz[v] += sz[u];
        }
    }
}

void add(int v , int x){
    vec[v]->push_back(x);
    if(cnt[depth[x]][name[x]] == 0){
        onlevel[depth[x]].insert(name[x]);
    }
    ++cnt[depth[x]][name[x]];
}

void del(int v , int x){
    --cnt[depth[x]][name[x]];
    if(cnt[depth[x]][name[x]] <= 0){
        onlevel[depth[x]].erase(onlevel[depth[x]].find(name[x]));
    }
}

void DFS(int v , int p , bool keep){
    int mx = -1 , bigChild = -1;
    for(int u : g[v]){
        if(u != p && mx < sz[u]){
            mx = sz[u];
            bigChild = u;
        }
    }
    for(int u : g[v]){
        if(u != p && u != bigChild){
            DFS(u , v , 0);
        }
    }
    if(bigChild != -1){
        DFS(bigChild , v , 1);
        vec[v] = vec[bigChild];
    }
    else{
        vec[v] = new vector<int> ();
    }
    add(v , v);
    for(int u : g[v]){
        if(u != p && u != bigChild){
            for(int x : *vec[u]){
                add(v , x);
            }
        }
    }

    // answer query
    for(auto& e : qs[v]){
        if(depth[v] + e.x <= N)ans[e.y] = onlevel[depth[v] + e.x].size();
    }

    if(keep == 0){
        // do something about the counting / set
        for(int x : *vec[v]){
            del(v , x);
        }
    }
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        int x;
        name[i].resize(25);
        scanf("%s %d" , &name[i][0] , &x);
        if(x == 0){
            root[i] = 1;
        }        
        else{
            g[i].push_back(x);
            g[x].push_back(i);
        }
    }
    for(int i = 1; i <= N; ++i){
        if(root[i]){
            getsz(i , i , 1);
        }
    }
    scanf("%d" , &Q);
    for(int q = 1; q <= Q; ++q){
        int v , k; 
        scanf("%d %d" , &v , &k);
        qs[v].emplace_back(k , q);
    }
    for(int i = 1; i <= N; ++i){
        if(root[i]){
            DFS(i , i , 0);
        }
    }
    for(int i = 1; i <= Q; ++i){
        printf("%d\n" , ans[i]);
    }
}       