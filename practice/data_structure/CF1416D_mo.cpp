#include <bits/stdc++.h>
using namespace std;

const int maxn = 7e5 + 10;
const int maxq = 5e5 + 10;
const int maxm = 5e5 + 10;

array<int , 2> querys[maxq]; // (type , v / i) 
array<int , 2> edges[maxm]; // (u , v)
array<int , 2> tree[maxn << 2];
int p[maxn] , N , M , Q , tin[maxn] , tout[maxn] , tot;
int fa[maxn] , del[maxm];
vector<int> g[maxn];

void update(int pos , int l , int r , int id , array<int , 2> v){ // a max-tree that supports point update
    if(l > r || pos < l || pos > r)return;
    if(pos == l && r == pos){
        tree[id] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid){
        update(pos , l , mid , id << 1 , v);
    }
    else{
        update(pos , mid + 1 , r , id << 1 | 1 , v);
    }
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
}

array<int , 2> query(int l , int r , int x , int y , int id){ // range max query
    if(l > r || x > y || r < x || l > y){
        return {0 , 0};
    }
    if(l <= x && y <= r){
        return tree[id];
    }
    int mid = (x + y) >> 1;
    if(r <= mid){
        return query(l , r , x , mid , id << 1);
    }
    if(l > mid){
        return query(l , r , mid + 1 , y , id << 1 | 1);
    }
    return max(
        query(l , r , x , mid , id << 1) ,
        query(l , r , mid + 1 , y , id << 1 | 1)
    );
}

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x , int y){
    x = find(x);
    y = find(y);
    if(x != y){
        ++N;
        fa[N] = N;
        fa[x] = fa[y] = N;
        g[N].push_back(x);
        g[N].push_back(y);
    }
}

void DFS(int v){
    tin[v] = ++tot;
    for(int nv : g[v]){
        DFS(nv);
    }
    tout[v] = tot;
}

void init(){
    memset(p , 0 , sizeof(p));
    memset(tin , 0 , sizeof(tin));
    memset(tout , 0 , sizeof(tout));
    tot = 0;
    for(int i = 0; i < (maxn << 2); ++i){
        tree[i] = {0 , 0};
    }
}

void solve(){
    // goal is to process queries in reverse order 
    // and construct DSU tree
    // then we can use range max tree to answer query
    init();
    cin >> N >> M >> Q;
    for(int i = 1; i <= N; ++i){
        cin >> p[i];
    }
    for(int i = 1; i <= M; ++i){
        cin >> edges[i][0] >> edges[i][1];
    }
    for(int i = 1; i <= Q; ++i){
        cin >> querys[i][0] >> querys[i][1];
        if(querys[i][0] == 2){
            del[querys[i][1]] = 1;
        }
    }
    for(int i = 1; i <= N; ++i){
        fa[i] = i;
    }
    // we start with a forest where no edges are removed
    for(int i = 1; i <= M; ++i){
        if(!del[i]){
            merge(edges[i][0] , edges[i][1]);
        }
    }
    for(int i = Q; i >= 1; --i){
        if(querys[i][0] == 1){
            // find the current ancestor of the queried node
            // as it all nodes reachable are in this ancestor's
            // subtree
            querys[i][1] = find(querys[i][1]); 
        }
        else{
            // since we process query in reverse order,
            // remove = add
            int id = querys[i][1];
            merge(edges[id][0] , edges[id][1]);
        }
    }
    // now we have an oriented forest , DFS from each root
    // to express the forest in ranges
    for(int i = 1; i <= N; ++i){
        if(i == find(i)){
            DFS(i);
        }
    }
    for(int i = 1; i <= N; ++i){
        update(tin[i] , 1 , tot , 1 , {p[i] , tin[i]});
    }
    // now we process the now query
    for(int i = 1; i <= Q; ++i){
        if(querys[i][0] == 2)continue;
        int v = querys[i][1];
        array<int , 2> ret = query(tin[v] , tout[v] , 1 , tot , 1);
        if(ret[0] == 0){
            cout << 0 << endl;
        }
        else{
            cout << ret[0] << endl;
            int nv = ret[1];
            update(nv , 1 , tot , 1 , {0 , nv});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    while(t--){
        solve();
    }
}