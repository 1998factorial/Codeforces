/*
    data structure , rating 2700
    Key : maxflow = mincut
    Observe that mincut is a cut that will seperate A[1] from B[N]
    So , it will cut some A[x] -> A[x + 1] and some B[y] -> B[y + 1]
    If we let F[x][y] = the cut that cuts some A[x] -> A[x + 1] and some B[y] -> B[y + 1]
    then F[x][y] = F1[x] + F2[y] + F3[x][y]
    where F3[x][y] is the sum of edges going from i to j , where i <= x and j > y.
    Observe that F2[y] is fixed , F3[x][y] is also fixed for all x and y
    Only F1[x] changes. If we let Best[x] = F2[y] + F3[x][y] for some y , such that
    F1[x] + Best[x] is minimal , since , Best[x] stays fixed , we can precompute all
    Best[x]. Assume we have Best[1...N] , we can build a range tree over [1..N] , that
    stores the minimal F1[x] + Best[x] , and support point update & range query , we can
    answer all Q querys in time O((Q + N) * logN) time.
    Now , the goal is to compute Best[x]. Best[x] = F2[y] + F3[x][y] , F2[y] seems easy ,
    F3[x][y] does not seem easy , so , we try to sweep on ascending order for x , and
    try to find smallest F2[y] + F3[x][y] at current x. Now , suppose , we have values
    for all F3[x - 1][y] for all 0 <= y < N. if there is an edge from A[x] to B[j] with cap = c.
    then for all F3[x][k] for all k < j , F3[x][k] >= F3[x - 1][k] + c. So we can build a range tree
    on y , that supports range update and range min query. (stores F2[y] + F3[x][y])
*/
#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;

const ll INF = 1e18;
const int maxn = 2e5 + 10;
ll F1[maxn] , F2[maxn] , Best[maxn];
vector<ii> g[maxn];
int N , M , Q;

struct min_lazy_tree{

    struct node{
        ll val , lazy;
        node(){}
        node(ll v , ll z) : val(v) , lazy(z) {}
    };

    node tree[maxn << 2];

    void push_down(int l , int r , int id){
        if(l > r)return;
        if(tree[id].lazy != 0 && l < r){
            tree[id << 1].lazy += tree[id].lazy;
			tree[id << 1 | 1].lazy += tree[id].lazy;
			tree[id << 1].val += tree[id].lazy;
			tree[id << 1 | 1].val += tree[id].lazy;
        }
        tree[id].lazy = 0;
    }

    node merge(node l , node r){
        node ret(0 , 0);
        if(l.val < r.val){
            ret.val = l.val;
        }
        else{
            ret.val = r.val;
        }
        return ret;
    }

    void build(int l , int r , int id){
        if(l > r)return;
        if(l == r){
            tree[id].val = F2[l];
            if(ID)printf("tree[%d %d] = %lld\n" , l , r , tree[id].val);
        }
        else{
            int mid = (l + r) >> 1;
            build(l , mid , id << 1);
            build(mid + 1 , r , id << 1 | 1);
            tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
            if(ID)printf("tree[%d %d] = %lld\n" , l , r , tree[id].val);
        }
    }

    void update(int l , int r , int x , int y , int id , ll v){ // support range update
        if(l > r || x > y || r < x || l > y)return;
        push_down(x , y , id);
        if(l <= x && y <= r){
            tree[id].val += v;
            tree[id].lazy += v;
            return;
        }
        int mid = (x + y) >> 1;
        if(r <= mid){
            update(l , r , x , mid , id << 1 , v);
        }
        else if(l > mid){
            update(l , r , mid + 1 , y , id << 1 | 1 , v);
        }
        else{
            update(l , r , x , mid , id << 1 , v);
            update(l , r , mid + 1 , y , id << 1 | 1 , v);
        }
        tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }

    ll query(int l , int r , int x , int y , int id){
        if(l > r || x > y || y < l || x > r)return INF;
        push_down(x , y , id);
        if(l <= x && y <= r){
            return tree[id].val;
        }
        int mid = (x + y) >> 1;
        if(r <= mid){
            return query(l , r , x , mid , id << 1);
        }
        if(l > mid){
            return query(l , r , mid + 1 , y , id << 1 | 1);
        }
        return min(
            query(l , r , x , mid , id << 1) ,
            query(l , r , mid + 1 , y , id << 1 | 1)
        );
    }

} F3;

struct min_tree{

    ll tree[maxn << 2];

    ll merge(ll a , ll b){
        return min(a , b);
    }

    void build(int l , int r , int id){
        if(l > r)return;
        if(l == r){
            tree[id] = INF;
        }
        else{
            int mid = (l + r) >> 1;
            build(l , mid , id << 1);
            build(mid + 1 , r , id << 1 | 1);
            tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
        }
    }

    void update(int l , int r , int x , int y , int id , ll v){ // support range update
        if(l > r || x > y || r < x || l > y)return;
        if(l <= x && y <= r){
            tree[id] = v;
            return;
        }
        int mid = (x + y) >> 1;
        if(r <= mid){
            update(l , r , x , mid , id << 1 , v);
        }
        else if(l > mid){
            update(l , r , mid + 1 , y , id << 1 | 1 , v);
        }
        else{
            update(l , r , x , mid , id << 1 , v);
            update(l , r , mid + 1 , y , id << 1 | 1 , v);
        }
        tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }

    ll query(int l , int r , int x , int y , int id){
        if(l > r || x > y || y < l || x > r)return INF;
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
        return min(
            query(l , r , x , mid , id << 1) ,
            query(l , r , mid + 1 , y , id << 1 | 1)
        );
    }

} F;


int main(){
    scanf("%d %d %d" , &N , &M , &Q);

    for(int i = 1; i < N; ++i){
        scanf("%lld %lld" , &F1[i] , &F2[i]);
    }

    for(int i = 1; i <= M; ++i){
        // edges from Ai to Bj
        int x , y , w; scanf("%d %d %d" , &x , &y , &w);
        g[x].emplace_back(y , w);
    }

    F3.build(0 , N - 1 , 1); // cut for y ranges from [0 , N - 1]

    for(int x = 1; x <= N; ++x){
        for(auto& e : g[x]){
            F3.update(0 , e.first - 1 , 0 , N - 1 , 1 , e.second); // changes on y[0 .. to - 1]
        }
        Best[x] = F3.query(0 , N - 1 , 0 , N - 1 , 1);
        if(ID)printf("Best[%d] = %lld\n" , x , Best[x]);
    }

    F.build(1 , N , 1); // cut for x ranges from [1 , N]

    for(int i = 1; i <= N; ++i){
        F.update(i , i , 1 , N , 1 , Best[i] + F1[i]);
    }

    printf("%lld\n" , F.query(1 , N , 1 , N , 1));

    for(int i = 1; i <= Q; ++i){
        // changes
        int v , w; scanf("%d %d" , &v , &w);
        F.update(v , v , 1 , N , 1 , w + Best[v]);
        printf("%lld\n" , F.query(1 , N , 1 , N , 1));
    }
}
