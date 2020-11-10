/*
    for each r
    ans[i] = the power of a[i ... r] , ans[i] >= ans[i + 1]
    say ans[i] = power of a[i ... r - 1] , consider a[r] , ans[i] += [ans[i] >= r - a[r]]
    find maximal pos st max{ans[r] , ans[r - 1] , ... , ans[pos]} >= r - a[r]
    ans[1,...,pos] += 1
*/
#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef pair<int , int> ii;
const int maxn = 3e5 + 10;
const int INF = 1e9;
int N , Q;
int a[maxn] , ans[maxn];
vector<ii> qs[maxn];
struct max_lazy_tree{
    struct node{
        int val , lz;
        node(){}
        node(int v , int l) : val(v) , lz(l) {}
    };
    node tree[maxn << 2];
    void push_down(int l , int r , int id){
        if(l < r && tree[id].lz){
            tree[id << 1].lz += tree[id].lz;
            tree[id << 1].val += tree[id].lz;
            tree[id << 1 | 1].lz += tree[id].lz;
            tree[id << 1 | 1].val += tree[id].lz;
        }
        tree[id].lz = 0;
    }
    node merge(node lhs , node rhs){
        node ret(0 , 0);
        if(lhs.val > rhs.val){
            ret.val = lhs.val;
        }
        else{
            ret.val = rhs.val;
        }
        return ret;
    }
    int query(int l , int r , int x , int y , int id){
        if(l > r || x > y || r < x || y < l)return -INF;
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
    void update(int l , int r , int x , int y , int id , int v){ // support range update
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
} T;

int main(){
    int i;
    scanf("%d %d" , &N , &Q);
    for(i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(i = 1; i <= Q; ++i){
        int x , y;
        scanf("%d %d" , &x , &y);
        qs[N - y].emplace_back(x + 1 , i);
    }
    for(i = 1; i <= N; ++i){
        int l = 1 , r = i , pos = -1;
        while(l <= r && i - a[i] >= 0){
            int mid = (l + r) >> 1;
            if(T.query(mid , i , 1 , N , 1) >= i - a[i]){
                pos = mid;
                l = mid + 1;
            }
            else{
                r = mid - 1;
            }
        }
        if(~pos){
            T.update(1 , pos , 1 , N , 1 , 1);
        }
        for(auto& q : qs[i]){
            ans[q.y] = T.query(q.x , i , 1 , N , 1);
        }
    }
    for(i = 1; i <= Q; ++i){
        printf("%d\n" , ans[i]);
    }
}