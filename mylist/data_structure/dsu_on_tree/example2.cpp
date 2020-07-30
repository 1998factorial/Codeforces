/*
    Given a tree, every vertex has color. 
    Query is how many vertices in subtree of vertex v are colored with color c?

    we do all queries in O(NlogN) time instead of O(N ** 2)
*/
#include <bits/stdc++.h>
#define ID if(true)
using namespace std;

const int maxn = 1e5 + 10;
int N , M , K;
vector<int> g[maxn];
vector<int> *vec[maxn];
int sz[maxn];
int cnt[maxn];
int col[maxn];

void getsz(int v , int p){
    sz[v] = 1;
    for(int u : g[v]){
        if(p != u){
            getsz(u , v);
            sz[v] += sz[u];
        }
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
        vec[v] = new vector<int>();
    }
    vec[v]->push_back(v);
    ++cnt[col[v]];
    for(int u : g[v]){
        if(u != p && u != bigChild){
            for(int x : *vec[u]){
                ++cnt[col[x]];
                vec[v]->push_back(x);
            }
        }
    }
    ID{ // need to answer query related to v here
        printf("at tree rooted at %d\n" , v);
        for(int i = 1; i <= K; ++i){
            printf("cnt[%d] = %d " , i , cnt[i]);
        }
        printf("\n");
    }
    if(keep == 0){ // we only keep the bigChild
        for(int u : *vec[v]){
           --cnt[col[u]];
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
    getsz(1 , 1);
    DFS(1 , 1 , 0);
}   