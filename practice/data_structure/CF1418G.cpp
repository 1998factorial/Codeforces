/*
    Covering problem
    x--x--x---x---x-----x
    fix right point, count good left points
    maintain the range of good / bad intervals
    good -1 , bad + 1
    query number of minval in [1 , r] where minval = 0
*/
#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 10;
const int INF = 1e9;
int a[maxn] , N;
vector<int> pos[maxn];

struct range_sum_lazy_tree {
    struct node {
        int lz , minv , cnt;
        node(){}
        node(int a , int b , int c) : lz(a) , minv(b) , cnt(c) {}
    } tree[maxn << 2];

    void push_down(int l , int r , int id){
        if(l < r && tree[id].lz){
            tree[id << 1].lz += tree[id].lz;
            tree[id << 1 | 1].lz += tree[id].lz;
            tree[id << 1].minv += tree[id].lz;
            tree[id << 1 | 1].minv += tree[id].lz;
        }
        tree[id].lz = 0;
    }

    node merge(node l , node r){
        node ret (0 , 0 , 0);
        ret.minv = min(l.minv , r.minv);
        ret.cnt = l.cnt * (ret.minv == l.minv) + r.cnt * (ret.minv == r.minv);
        return ret;
    }

    void build(int l , int r , int id){
        if(l == r){
            tree[id] = node(0 , 0 , 1);
        }
        else{
            int mid = (l + r) >> 1;
            build(l , mid , id << 1);
            build(mid + 1 , r , id << 1 | 1);
            tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
        }
    }

    void update(int l , int r , int x , int y , int id , int val){
        if(l > r || x > y || r < x || l > y)return ;
        if(l <= x && y <= r){
            tree[id].lz += val;
            tree[id].minv += val;
            return ;
        }
        int mid = (x + y) >> 1;
        push_down(x , y , id);
        if(r <= mid){
            update(l , r , x , mid , id << 1 , val);
        }
        else if(l > mid){
            update(l , r , mid + 1 , y , id << 1 | 1 , val);
        }
        else{
            update(l , r , x , mid , id << 1 , val);
            update(l , r , mid + 1 , y , id << 1 | 1 , val);
        }
        tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }

    node query(int l , int r , int x , int y , int id){
        if(l > r || x > y || y < l || r < x)return node(0 , INF , 1);
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
        return merge(query(l , r , x , mid , id << 1) , query(l , r , mid + 1 , y , id << 1 | 1));
    }

} T;

int main(){
    ll ret = 0;
    scanf("%d" , &N);
    T.build(1 , N , 1);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(int r = 1; r <= N; ++r){
        int x = a[r];
        pos[x].push_back(r);
        if(pos[x].size() == 1){
            ID printf("making [%d %d] illegal\n" , 1 , pos[x][0]);
            T.update(1 , pos[x][0] , 1 , N , 1 , 1); // [1 , pos[x][0]] is illegal
        }
        else if(pos[x].size() == 2){
            ID printf("making [%d %d] illegal\n" , pos[x][0] + 1 , pos[x][1]);
            T.update(pos[x][0] + 1 , pos[x][1] , 1 , N , 1 , 1); // [pos[x][0] + 1 , pos[x][1]] is illegal
        }
        else if(pos[x].size() == 3){
            ID printf("making [%d %d] illegal\n" , pos[x][1] + 1 , pos[x][2]);
            ID printf("making [%d %d] legal\n" , 1 , pos[x][0]);
            T.update(pos[x][1] + 1 , pos[x][2] , 1 , N , 1 , 1); // [pos[x][1] + 1 , pos[x][2]] is illegal
            T.update(1 , pos[x][0] , 1 , N , 1 , -1); // [1 , pos[x][0]] is legal
        }
        else{
            int sz = pos[x].size();
            ID printf("making [%d %d] illegal\n" , pos[x][sz - 2] + 1 , pos[x][sz - 1]);
            ID printf("making [%d %d] legal\n" , pos[x][sz - 4] + 1 , pos[x][sz - 3]);
            ID printf("making [%d %d] illegal\n" , sz - 5 >= 0 ? pos[x][sz - 5] + 1 : 1 , pos[x][sz - 4]);
            T.update(pos[x][sz - 2] + 1 , pos[x][sz - 1] , 1 , N , 1 , 1); // [pos[x][n - 2] + 1 , pos[x][n - 1]] is illegal
            T.update(pos[x][sz - 4] + 1 , pos[x][sz - 3] , 1 , N , 1 , -1); // [pos[x][n - 4] + 1 , pos[x][n - 3]] is legal
            T.update(sz - 5 >= 0 ? pos[x][sz - 5] + 1 : 1 , pos[x][sz - 4] , 1 , N , 1 , 1); // [pos[x][n - 5] + 1 , pos[x][4]] is illegal
        }
        range_sum_lazy_tree :: node rt = T.query(1 , r , 1 , N , 1);
        ID printf("current min = %d , with %d of such value\n" , rt.minv , rt.cnt);
        ret += rt.cnt * (rt.minv == 0); // good l points yeilds with minv = 0
    }
    printf("%lld\n" , ret);
}