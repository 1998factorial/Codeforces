#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
#define mk make_pair
using namespace std;
typedef pair<int , int> ii;

const int maxn = 1e6 + 10;
vector<int> g[maxn];
vector<int> *vec[maxn];
set<ii> *freq[maxn]; // (number , -depth)
int sz[maxn];
int cnt[maxn];
int ans[maxn];
int depth[maxn];
int N;

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
    if( freq[v]->count(mk(cnt[depth[x]] , -depth[x])) ){
        freq[v]->erase(
            freq[v]->find(
                mk(cnt[depth[x]] , -depth[x])
            )
        );
    }
    ++cnt[depth[x]];
    freq[v]->insert(mk(cnt[depth[x]] , -depth[x]));
}


void DFS(int v , int p , int keep){
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
        freq[v] = freq[bigChild];
    }
    else{
        vec[v] = new vector<int> ();
        freq[v] = new set<ii> ();
    }
    add(v , v);
    // do something about the answer
    for(int u : g[v]){
        if(u != p && u != bigChild){
            for(int x : *vec[u]){
                // do something about answer
                add(v , x);                
            }
        }
    }

    // answer query here
    ID{
        printf("we are at tree rooted at %d\n" , v);
        for(int i = 0; i <= N; ++i){
            printf("cnt[%d] = %d\n" , i , cnt[i]);
        }
        printf("\n");
    }

    ans[v] = -freq[v]->rbegin()->second - depth[v];

    if(keep == 0){
        // do something about the cnt
        for(int x : *vec[v]){
            --cnt[depth[x]];
        }
    }
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i < N; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    getsz(1 , 1 , 1);
    DFS(1 , 1 , 1);
    for(int i = 1; i <= N; ++i){
        printf("%d\n" , ans[i]);
    }
}   