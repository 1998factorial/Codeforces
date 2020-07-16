#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 5e5 + 10;
const ll INF = 1e18;

struct max_lazy_tree{

    struct node{
        ll val , lz;
        node(){}
        node(ll val_ , ll lz_) : val(val_) , lz(lz_) {}
    };

    node tree[maxn << 2];

    void push_down(int l , int r , int id){
        if(l < r && tree[id].lz){
            tree[id << 1].val += tree[id].lz;
            tree[id << 1 | 1].val += tree[id].lz;
            tree[id << 1].lz += tree[id].lz;
            tree[id << 1 | 1].lz += tree[id].lz;
            tree[id].lz = 0;
        }
    }

    node merge(node a , node b){
        node ret(0 , 0);
        ret.val = max(a.val , b.val);
        return ret;
    }

    void build(int l , int r , int id){
        if(l == r){
            tree[id].val = l;
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
        push_down(x , y , id);
        if(l <= x && y <= r){
            tree[id].val += v;
            tree[id].lz += v;
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

int N , lim , K , M;
multiset<ii> pos;
multiset<int> cur;

int main(){
    scanf("%d %d %d" , &N , &K , &M);
    lim = 2 * N;
    T.build(1 , lim , 1);
    while(M--){
        int col , row; scanf("%d %d" , &col , &row);
        int mrow = row + abs(col - K);
        if(ID)printf("mrow = %d\n" , mrow);
        if(pos.count({row , col})){
            pos.erase(pos.find({row , col}));
            T.update(1 , mrow , 1 , lim , 1 , -1);
            cur.erase(cur.find(mrow));
        }
        else{
            pos.insert({row , col});
            T.update(1 , mrow , 1 , lim , 1 , 1);
            cur.insert(mrow);
        }
        if(!cur.empty())printf("%lld\n" , max(0ll , T.query(1 , *cur.rbegin() , 1 , lim , 1) - N - 1));
        else printf("0\n");
    }
}
