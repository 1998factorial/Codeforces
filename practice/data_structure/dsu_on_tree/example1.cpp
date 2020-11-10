/*
    Given a tree, every vertex has color. 
    Query is how many vertices in subtree of vertex v are colored with color c?
    Now this is O(N ** 2)
    
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int N , M , K;
vector<int> g[maxn];
int sz[maxn];
int cnt[maxn];
int col[maxn];

void getsz(int v , int p){
    sz[v] = 1;
    for(int u : g[v]){
        if(p != u){
            getsz(v , u);
            sz[v] += sz[u];
        }
    }
}

void add(int v , int p , int x){
    cnt[col[v]] += x;
    for(int u : g[v]){
        if(u != p){
            add(u , v , x);
        }
    }
}

void DFS(int v , int p){
    add(v , p , 1);
    printf("tree rooted at %d\n" , v);
    for(int i = 1; i <= K; ++i){
        printf("cnt[%d] = %d " , i , cnt[i]);
    }
    printf("\n");
    add(v , p , -1);
    for(int u : g[v]){
        if(u != p){
            DFS(u , v);
        }
    }
}



int main(){
    cin >> N >> M >> K;
    for(int i = 1; i <= N; ++i){
        cin >> col[i];
    }
    for(int i = 1; i <= M; ++i){
        int x , y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    DFS(1 , 1);
}   