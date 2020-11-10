/*
    data structure , rating 2600

    Need to answer Q querys , for each query , we need to find the minimal path sum from
    a leaf x in [l , r] to v

    we can solve all Q querys offline , by doing a DFS search from root 1
    (parent , child , w) , when we move from parent to child , all answer in [l , r]
    which is governed by child is decreased by w , all answers in [1 , l - 1] U [r + 1 , N]
    will be increased by w
    so we need a range tree that support range update (lazy) and range query (query for min val)
*/
#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;
typedef pair<int , ll> ii;
const int maxn = 500000 + 10;
const ll INF = 1e18;
int N , Q;
struct query{
    int l , r , id;
    query(){}
    query(int l_ , int r_ , int id_) : l(l_) , r(r_) , id(id_) {}
};
vector<ii> g[maxn];
vector<query> qs[maxn];
int dfn[maxn] , L[maxn] , R[maxn] , tot;
ll ans[maxn] , sum[maxn];

struct min_lazy_tree{

    struct node{
        ll val , lazy;
        node(){}
        node(ll v , ll z) : val(v) , lazy(z) {}
    };

    node tree[maxn << 1];

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
        if(l == r){ // we are at leaf
            tree[id].val = sum[l];
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

} T;

void DFS(int v , int p , ll w){
    ++tot;
    dfn[v] = tot;
    sum[dfn[v]] = w;
    L[v] = dfn[v];
    for(auto& e : g[v]){
        if(e.first != p){
            DFS(e.first , v , sum[v] + e.second);
        }
    }
    R[v] = tot;
}

void solve(int v , int p , ll w){
    int l = L[v] , r = R[v];
    if(ID){
        cout << "adding " << -w << " to " << l << " " << r << endl;
        cout << "adding " << w << " to " << 1 << " " << l - 1 << endl;
        cout << "adding " << w << " to " << r + 1 << " " << N << endl;
    }
    T.update(l , r , 1 , N , 1 , -w);
    T.update(1 , l - 1 , 1 , N , 1 , w);
    T.update(r + 1 , N , 1 , N , 1 , w);

    for(auto& q : qs[v]){
        ans[q.id] = T.query(q.l , q.r , 1 , N , 1);
        if(ID)printf("ans[%d] = %lld\n" , q.id , ans[q.id]);
    }

    for(auto& e : g[v]){
        if(e.first != p){
            solve(e.first , v , e.second);
        }
    }

    if(ID){
        cout << "adding " << w << " to " << l << " " << r << endl;
        cout << "adding " << -w << " to " << 1 << " " << l - 1 << endl;
        cout << "adding " << -w << " to " << r + 1 << " " << N << endl;
    }

    T.update(l , r , 1 , N , 1 , w);
    T.update(1 , l - 1 , 1 , N , 1 , -w);
    T.update(r + 1 , N , 1 , N , 1 , -w);
}

int main(){
    tot = 0;
    scanf("%d %d" , &N , &Q);
    for(int i = 2; i <= N; ++i){
        int j , w;
        scanf("%d %d" , &j , &w);
        g[i].emplace_back(j , w);
        g[j].emplace_back(i , w);
    }
    DFS(1 , -1 , 0);
    for(int i = 1; i <= N; ++i){
        if(g[i].size() > 1 || i == 1){
            sum[dfn[i]] = INF;
        }
    }
    if(ID)for(int i = 1; i <= N; ++i){
        printf("dfn[%d] = %d , R[%d] = %d\n" , i , dfn[i] , i , R[i]);
        printf("sum[%d] = %lld\n" , i , sum[i]);
    }
    for(int q = 1; q <= Q; ++q){
        int v , l , r;
        scanf("%d %d %d" , &v , &l , &r);
        qs[v].emplace_back(l , r , q);
    }
    // solve for it
    // at the beginning , [l , r] will store the minimal answer from leaf x in [l , r] to 1
    T.build(1 , N , 1);
    solve(1 , -1 , 0);
    for(int i = 1; i <= Q; ++i){
        printf("%lld\n" , ans[i]);
    }
}
