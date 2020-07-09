/*
    Data structure , rating 2200
    Observe that order of the queue does not matter
    we need to find maximal x st #(dish >= x) > #(student >= x)
*/
#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 100;
const ll INF = 1e18;
const int lim = 1e6;

struct max_lazy_tree{

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
            //tree[id].val = F2[l];
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

    int query(int l , int r , int id){
        if(tree[id].val <= 0)return -1;
        if(l == r)return l;
        push_down(l , r , id);
        int mid = (l + r) >> 1;
        if(tree[id << 1 | 1].val > 0)return query(mid + 1 , r , id << 1 | 1);
        return query(l , mid , id << 1);
    }

} T;

int N , M , Q;
int a[300005] , b[300005];
int main(){
    scanf("%d %d" , &N , &M);
    T.build(1 , lim , 1);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        T.update(1 , a[i] , 1 , lim , 1 , 1);
    }
    for(int i = 1; i <= M; ++i){
        scanf("%d" , &b[i]);
        T.update(1 , b[i] , 1 , lim , 1 , -1);
    }
    scanf("%d" , &Q);
    while(Q--){
        int t , pos , val;
        scanf("%d %d %d" , &t , &pos , &val);
        if(t == 1){
            T.update(1 , a[pos] , 1 , lim , 1 , -1);
            a[pos] = val;
            T.update(1 , a[pos] , 1 , lim , 1 , 1);
            printf("%d\n" , T.query(1 , lim , 1));
        }
        else{
            T.update(1 , b[pos] , 1 , lim , 1 , 1);
            b[pos] = val;
            T.update(1 , b[pos] , 1 , lim , 1 , -1);
            printf("%d\n" , T.query(1 , lim , 1));
        }
    }
}
