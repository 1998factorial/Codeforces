/*
    Power tree , rating 2500
    if there are k leafs then for each vertex , it can be represented by a vector of 0/1
    where x[i] = 1 means the ith leaf is in this vertex's subtree.
    So our goal is to find m linearly independent vectors , so that we can span any value
    combination of leaves. (with lowest cost)
    notice that each vector will look like (0..01...10...0) , [0] + [1] + [0].
    So , for each vertex we can get the range of leaves that are under it's control
    and we will get m of such ranges. so if we represent leaves l0(dummy leaf) ,
    l1 l2 ... lm as nodes on a graph,
    when choosing m linearly independent ranges , we will get a spanning tree.
    lowest cost comes with MST.
    After finding such MST , we try all edges , see if we can replace some edge in MST with this
    edge , if we can , then this edge (id by the vertex) will be in our answer.
*/
#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int C[maxn];
int N , L;
vector<int> g[maxn];
vector<int> leaves;
int tin[maxn] , tout[maxn] , t;
int fa[maxn];
int up[maxn][30] , DP[maxn][30];

struct edge{
    int x , y , w , id;
    edge(){}
    edge(int x_ , int y_ , int w_ , int id_) : x(x_) , y(y_) , w(w_) , id(id_) {}
    bool operator < (const edge& rhs) const {
        return w < rhs.w;
    }
};

vector<edge> edges;
vector<ii> mst[maxn];
bool use[maxn]; // means this vertex is in optimal solution
int tin2[maxn] , tout2[maxn];


void DFS(int v , int p){
    tin[v] = ++t;
    for(int u : g[v]){
        if(u != p){
            DFS(u , v);
        }
    }
    if(v != 1 && g[v].size() == 1){
        leaves.push_back(tin[v]); // get the DFS order number for each leaf
    }
    tout[v] = t;
}

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x , int y){
    x = find(x); y = find(y);
    if(x != y)fa[x] = y;
}

ll MST(){
    for(int i = 0; i <= N; ++i)fa[i] = i;
    sort(edges.begin() , edges.end());
    ll ret = 0;
    for(auto& e : edges){
        int x = e.x , y = e.y , w = e.w , id = e.id;
        if(find(x) != find(y)){
            merge(x , y);
            //mst.push_back(e);
            mst[x].emplace_back(y , w);
            mst[y].emplace_back(x , w);
            ret += w;
            use[id] = 1;
        }
    }
    return ret;
}


void DFS2(int v , int p , int cost){
    tin2[v] = ++t;
    up[v][0] = p;
    DP[v][0] = cost;
    for(int i = 1; i <= L; ++i){
        up[v][i] = up[up[v][i - 1]][i - 1];
        DP[v][i] = max(DP[v][i - 1] , DP[up[v][i - 1]][i - 1]);
    }
    if(ID)for(int i = 0; i <= L; ++i){
        printf("DP[%d][%d] = %d\n" , v , i , DP[v][i]);
    }
    for(auto& e : mst[v]){
        if(e.first != p){
            DFS2(e.first , v , e.second);
        }
    }
    tout2[v] = ++t;
}

bool isAncestor(int u , int v){
  return tin2[u] <= tin2[v] && tout2[u] >= tout2[v];
}

int findmax(int u , int v){ // return the maximal edge from u and v to their common ancestor
  int ans = 0;
  if(isAncestor(u , v)){
    //u is v's ancestor
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[v][i] , u)){
        ans = max(ans , DP[v][i]);
        v = up[v][i];
      }
    }
    ans = max(ans , DP[v][0]);
  }
  else if(isAncestor(v , u)){
    // v is u's ancestor
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[u][i] , v)){
        ans = max(ans , DP[u][i]);
        u = up[u][i];
      }
    }
    ans = max(ans , DP[u][0]);
  }
  else{
    int x = u , y = v;
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[x][i] , v)){
        ans = max(ans , DP[x][i]);
        x = up[x][i];
      }
    }
    ans = max(ans , DP[x][0]);
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[y][i] , u)){
        ans = max(ans , DP[y][i]);
        y = up[y][i];
      }
    }
    ans = max(ans , DP[y][0]);
  }
  return ans;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%d" , &C[i]);
    for(int i = 1; i < N; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    leaves.push_back(0); // dummy leaf
    t = 0;
    DFS(1 , 1);
    if(ID)
    for(int v = 1; v <= N; ++v){
        printf("tin[%d] = %d , tout[%d] = %d\n" , v , tin[v] , v , tout[v]);
    }
    sort(leaves.begin() , leaves.end());
    if(ID)for(int i : leaves) cout << i << endl;
    for(int v = 1; v <= N; ++v){
        // for each vertex, we need to get the range of leaves that it can cover
        // [leaves[l] , leaves[r]]
        // then we create edge : (l - 1 , r , C[v] , v)
        int l , r;
        // get l first
        // smallest j st tin[v] <= leaves[j]
        l = lower_bound(leaves.begin() , leaves.end() , tin[v]) - leaves.begin();
        if(ID)cout << "l for v = " << v << " is " << l << endl;
        // get r then
        // largest j st tout[v] >= leaves[j]
        r = lower_bound(leaves.begin() , leaves.end() , tout[v]) - leaves.begin();
        if(ID)cout << "r for v = " << v << " is " << r << endl;
        edges.emplace_back(l - 1 , r , C[v] , v);
        if(ID)cout << "adding " << l - 1 << " " << r << " " << C[v] << " " << v << endl;
    }
    // we run MST
    ll ret = MST();
    // get ans array
    L = ceil(log2(N));
    t = 0;
    DFS2(1 , 1 , 0);
    for(auto& e : edges){
        int x = e.x , y = e.y , w = e.w , id = e.id;
        if(!use[id]){
            ll val = findmax(x , y); // get the largest edge between x and y
            if(ID)cout << "w = " << w << "  " << val << endl;
            if(ret - val + w <= ret){
                use[id] = 1;
            }
        }
    }
    vector<int> ans;
    for(int i = 1; i <= N; ++i){
        if(use[i])ans.push_back(i);
    }
    printf("%lld %d\n" , ret , (int)ans.size());
    for(int i : ans){
        printf("%d " , i);
    }
}
