/*
    data structure , Hall's therom , rating 2600
    goal is to find the number of subarray of length M of a[1..N] , so that,
    after suffeling b[1..M] , all a[i] + b[i] >= H.
    Which is similar to matching problem
    sort b , for each a[i] , we want to find the smallest b[j] st b[j] >= H - a[i]
    we do sum[j , M] += 1.
    if for all i , sum[i] >= i , then we have a perfect matching.
    (Hall's theorm , any subset of X , |X| <= |f(X)|) So we can keep a range
    tree that stores the max value of i - sum[i]. If the max is <= 0 , then we have a match.
*/
#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;

const int maxn = 150005;
const ll INF = 1e18;

int N , M , H;
ll a[maxn] , b[maxn];
int L[maxn];

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
            tree[id].val = l;
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


int solve(){
    int ret = 0;
    sort(b + 1 , b + 1 + M);
    if(ID){
        for(int i = 1; i <= M; ++i){
            cout << b[i] << " ";
        }
        cout << endl;
    }
    for(int i = 1; i <= N; ++i){
        auto it = lower_bound(b + 1 , b + 1 + M , H - a[i]);
        L[i] = it - b;
        if(ID)printf("L[%d] = %d\n" , i , L[i]);
    }
    T.build(1 , M , 1);
    for(int i = 1; i <= M; ++i){
        T.update(L[i] , M , 1 , M , 1 , -1);
        if(ID)printf("add on [%d %d] with %d\n" , L[i] , M , -1);
    }
    ret += T.tree[1].val <= 0;
    if(ID)cout << "current maximal = " << T.tree[1].val << endl;
    for(int i = M + 1; i <= N; ++i){
        T.update(L[i - M] , M , 1 , M , 1 , 1);
        T.update(L[i] , M , 1 , M , 1 , -1);
        if(ID)printf("add on [%d %d] with %d\n" , L[i - M] , M , 1);
        if(ID)printf("add on [%d %d] with %d\n" , L[i] , M , -1);
        if(ID)cout << "current maximal = " << T.tree[1].val << endl;
        ret += T.tree[1].val <= 0;
    }
    return ret;
}

int main(){
    scanf("%d %d %d" , &N , &M , &H);
    for(int i = 1; i <= M; ++i){
        scanf("%lld" , &b[i]);
    }
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &a[i]);
    }
    printf("%d\n" , solve());
}
