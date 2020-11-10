#include <bits/stdc++.h>
#define ID if(1)
#define x first
#define y second
using namespace std;
typedef pair<int , int> ii;
const int maxn = 5e5 + 10;
const int INF = 1e9;
int N , Q;
int a[maxn] , ans[maxn];
vector<ii> querys[maxn];
vector<int> pos[maxn];
struct min_state_tree {
    struct node {
        int minv , index;
        node(){}
        node(int a , int b): minv(a) , index(b) {}
    } tree[maxn << 2];

    node merge(node l , node r){
        node ret(INF , 0);
        if(l.minv < r.minv){
            ret.minv = l.minv; ret.index = l.index;
        }
        else{
            ret.minv = r.minv; ret.index = r.index;
        }
        return ret;
    }

    void build(int l , int r , int id){
        if(l == r){
            tree[id] = node(INF , 0);
        }
        else{
            int mid = (l + r) >> 1;
            build(l , mid , id << 1);
            build(mid + 1 , r , id << 1 | 1);
            tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
        }
    }

    void update(int pos , int l , int r , int id , int val){
        if(l > r || pos > r || pos < l)return ;
        if(pos == l && pos == r){
            tree[id] = node(val , pos);
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid)update(pos , l , mid , id << 1 , val);
        else update(pos , mid + 1 , r , id << 1 | 1 , val);
        tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }
  
    node query(int l , int r , int x , int y , int id){
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
        return merge(
            query(l , r , x , mid , id << 1),
            query(l , r , mid + 1 , y , id << 1 | 1)
        );
    }

} T;

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    scanf("%d" , &Q);
    for(int i = 1; i <= Q; ++i){
        int l , r; 
        scanf("%d %d" , &l , &r);
        querys[r].emplace_back(l , i);
    }
    for(int r = 1; r <= N; ++r){
        int x = a[r];
        pos[x].push_back(r);
        if(pos[x].size() == 1){
            T.update(r , 1 , N , 1 , 0);
        }
        else{
            int prev = pos[x][pos[x].size() - 2];
            T.update(prev , 1 , N , 1 , INF);
            T.update(r , 1 , N , 1 , prev);
        }
        for(auto& qs : querys[r]){
            int l = qs.x , id = qs.y;
            min_state_tree :: node rt = T.query(l , r , 1 , N , 1);
            if(rt.minv < l)ans[id] = a[rt.index];
        }
    }
    for(int i = 1; i <= Q; ++i){
        printf("%d\n" , ans[i]);
    }
}   
