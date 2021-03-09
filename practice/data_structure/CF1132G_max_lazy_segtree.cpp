#include <bits/stdc++.h>
using namespace std;
typedef int ll;
const int maxn = 1e6 + 10;
const ll INF = 1e8 + 10;
int N , K , a[maxn] , tin[maxn] , tout[maxn] , DP[maxn] , tot;
vector<int> g[maxn] , rg[maxn];

struct max_lazy_tree{

    struct node{
        ll val , lazy;
        node(){}
        node(ll v , ll z) : val(v) , lazy(z) {}
    };

    node tree[maxn * 4 + 100];

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
        if(l.val > r.val){
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
            tree[id].val = 0;
            tree[id].lazy = 0;
        }
        else{
            int mid = (l + r) >> 1;
            build(l , mid , id << 1);
            build(mid + 1 , r , id << 1 | 1);
            tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
        }
    }

    void range_update(int l , int r , int x , int y , int id , ll v){ // support range update
        if(l > r || x > y || r < x || l > y)return;
        push_down(x , y , id);
        if(l <= x && y <= r){
            tree[id].val += v;
            tree[id].lazy += v;
            return;
        }
        int mid = (x + y) >> 1;
        if(r <= mid){
            range_update(l , r , x , mid , id << 1 , v);
        }
        else if(l > mid){
            range_update(l , r , mid + 1 , y , id << 1 | 1 , v);
        }
        else{
            range_update(l , r , x , mid , id << 1 , v);
            range_update(l , r , mid + 1 , y , id << 1 | 1 , v);
        }
        tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }

    void point_update(int pos , int l , int r , int id , ll v){
        if(pos < l || pos > r || l > r)return;
        push_down(l , r , id);
        if(pos == l && pos == r){
            tree[id].val += v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid){
            point_update(pos , l , mid , id << 1 , v);
        }
        else{
            point_update(pos , mid + 1 , r , id << 1 | 1 , v);
        }
        tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }

    /*int query(int l , int r , int id){
        if(tree[id].val <= 0)return -1;
        if(l == r)return l;
        push_down(l , r , id);
        int mid = (l + r) >> 1;
        if(tree[id << 1 | 1].val > 0)return query(mid + 1 , r , id << 1 | 1);
        return query(l , mid , id << 1);
    }*/

    ll query(int l , int r , int x , int y , int id){
        if(l > r || x > y || y < l || x > r)return -INF;
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
        return max(
            query(l , r , x , mid , id << 1) ,
            query(l , r , mid + 1 , y , id << 1 | 1)
        );
    }

} T;

void getDP(int v){
    if(DP[v])return;
    DP[v] = 1;
    for(int u : g[v]){
        getDP(u);
        DP[v] = max(DP[v] , DP[u] + 1);
    }
}

void DFS(int v){
    tin[v] = ++tot;
    for(int u : rg[v]){
        DFS(u);
    }
    tout[v] = tot;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
    }   
    vector<int> st;
    for(int i = 1; i <= N; ++i){
        while(!st.empty() && a[st.back()] < a[i]){
            g[st.back()].push_back(i);
            rg[i].push_back(st.back());
            //cerr<<st.back()<<" -> "<<i<<endl;
            st.pop_back();
        }
        st.push_back(i);
    }
    // DP[v] = longest greedy sequence starting with v 
    for(int i = 1; i <= N; ++i){
        if(DP[i] == 0){
            getDP(i);
        }
    }
    tot = 0;
    // represent the forest as segments
    for(int i = N; i >= 1; --i){
        if(tin[i] == 0){
            DFS(i);
        }
    }
    // sweep on forest , (by segments of length K)
    T.build(1 , tot , 1);
    vector<int> ans;
    for(int i = N; i >= N - K + 1; --i){
        T.point_update(tin[i] , 1 , tot , 1 , DP[i]);
    }
    ans.push_back(T.query(1 , tot , 1 , tot , 1));
    for(int i = N - K; i >= 1; --i){
        T.point_update(tin[i + K] , 1 , tot , 1 , -INF);
        T.point_update(tin[i] , 1 , tot , 1 , DP[i]);
        T.range_update(tin[i + K] , tout[i + K] , 1 , tot , 1 , -1);
        ans.push_back(T.query(1 , tot , 1 , tot , 1));
    }
    reverse(ans.begin() , ans.end());
    for(int i : ans)cout << i << " ";
    cout << endl;
}