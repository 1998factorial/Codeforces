#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define mk make_pair
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;

const int maxn = 1e5 + 10;
vector<int> g[maxn];
vector<int> *vec[maxn];
set<ii> *freq[maxn];
int cnt[maxn]; // store the numbers of each color in subtree
int col[maxn];
int sz[maxn];
ll ans[maxn];
ll sum = 0;
int N;

void getsz(int v , int p){
    sz[v] = 1;
    for(int u : g[v]){
        if(u != p){
            getsz(u , v);
            sz[v] += sz[u];
        }
    }
}

void update(int v , int x){
    vec[v]->push_back(x);
    // do something about counting
    if( freq[v]->count(mk(cnt[col[x]] , col[x])) ){
        freq[v]->erase(
            freq[v]->find(
                mk(cnt[col[x]] , col[x])
            )
        );
    }
    ++cnt[col[x]];
    if(freq[v]->empty()){
        sum = col[x];
    }
    else{
        auto it = freq[v]->rbegin();
        if(it->first == cnt[col[x]]) sum += col[x];
        else if(it->first < cnt[col[x]]) sum = col[x];
    }
    freq[v]->insert(mk(cnt[col[x]] , col[x]));
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
        freq[v] = freq[bigChild];
    }
    else{
        vec[v] = new vector<int> ();
        freq[v] = new set<ii> ();
    }
    update(v , v);
    // do something here about counting
    for(int u : g[v]){
        if(u != p && u != bigChild){
            for(int x : *vec[u]){
               update(v , x);
            }
        }
    }

    ID{
        printf("at tree rooted at %d\n" , v);
        for(int i = 1; i <= N; ++i){
            printf("cnt[%d] = %d\n" , i , cnt[i]);
        }
        for(auto& e : *freq[v]){
            printf("(cnt = %d , col = %d)\n" , e.x , e.y);
        }
        printf("\n");
    }
    // answer query here
    ans[v] = sum;

    if(keep == 0){
        // pop out counting 
        for(int u : *vec[v]){
            --cnt[col[u]];
        }
    }
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%d" , &col[i]);
    for(int i = 1; i < N; ++i){
        int x , y; 
        scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    getsz(1 , 1);
    DFS(1 , 1 , 1);
    for(int i = 1; i <= N; ++i){
        printf("%lld " , ans[i]);
    }
    printf("\n");
}       