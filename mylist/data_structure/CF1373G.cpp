/*
    data structure , hall's theorm, Rating 2600
    observe we need at most N extra rows
    let f(j) = # of pawns that can go to row[j , j + 1 , ..]
    by halls theorm , we need for all f(j) <= R - j + 1.
    where R is the size of the board. Our goal is the find the minimal
    number of rows that we need to add , so that there exist a matching
    (pawns to cell on col K)
    So,  we need to first minimse R. Observe that f(j) + j - 1 <= R,
    the minimal R take places when R = f(j) + j - 1. Since such R must
    be >= all f(j) + j - 1. The minimal R is the maximal among all
    f(j) + j - 1. so ans = max(0 , max{f(j) + j - 1} - N)

    how do we calculate f(j) ?
    given a pawn , (row , col) , it is easy to see that the smallest row on col K
    that this pawn can get to is : mcol = row + abs(col - K)
    now , we know that for all f(j) , j <= mcol , f(j) += 1
*/
#include <bits/stdc++.h>
#define ID 0
#define mkp make_pair
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;

const int maxn = 4e5 + 10;
const ll INF = 1e18;

set<ii> pos;
multiset<int> up;
int N , M , K , lim;

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

int abs(int x){
    return x >= 0 ? x : -x;
}

int main(){
    scanf("%d %d %d" , &N , &K , &M);
    lim = 2 * N;
    T.build(1 , lim , 1);
    while(M--){
        int row , col; scanf("%d %d" , &col , &row);
        int dis = row + abs(col - K);
        if(pos.count(mkp(row , col))){
            T.update(1 , dis , 1 , lim , 1 , -1);
            up.erase(up.find(dis));
            pos.erase(pos.find(mkp(row , col)));
        }
        else{
            up.insert(dis);
            T.update(1 , dis , 1 , lim , 1 , 1);
            pos.insert(mkp(row , col));
        }
        if(!up.empty()){
            int ret = max(0ll , T.query(1 , *up.rbegin() , 1 , lim , 1) - N - 1);
            printf("%d\n" , ret);
        }
        else printf("0\n");
    }
}
