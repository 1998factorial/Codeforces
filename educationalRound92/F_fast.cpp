#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;

const int maxn = 4e5 + 10;
const int INF = 1e9;
struct seg{
    int l , r , t;
    seg(){}
    seg(int l_ , int r_ , int t_) : l(l_) , r(r_) , t(t_) {}
    bool operator < (const seg& rhs) const {
        return r < rhs.r;
    }
};

struct max_seg_tree_lazy{
    struct node{
        int val , lz;
        node(){}
        node(int v , int l) : val(v) , lz(l) {}
    };
    node tree[maxn << 2];
    
    node merge(node l , node r){
        node ret = node(0 , 0);
        ret.val = l.val > r.val ? l.val : r.val;
        return ret;
    }

    void push_down(int l , int r , int id){
        if(l < r && tree[id].lz){
            tree[id << 1].lz += tree[id].lz;
            tree[id << 1 | 1].lz += tree[id].lz;
            tree[id << 1].val += tree[id].lz;
            tree[id << 1 | 1].val += tree[id].lz;
        }
        tree[id].lz = 0;
    }

    void add_range(int l , int r , int x , int y , int val , int id){
        if(l > r || x > y || l > y || r < x)return;
        push_down(x , y , id);
        if(l <= x &&  y <= r){
            tree[id].val += val;
            tree[id].lz += val;
        }
        else{
            int mid = (x + y) >> 1;
            if(r <= mid){
                add_range(l , r , x , mid , val , id << 1);
            }
            else if(l > mid){
                add_range(l , r , mid + 1 , y , val , id << 1 | 1);
            }
            else{
                add_range(l , r , x , mid , val , id << 1);
                add_range(l , r , mid + 1 , y , val , id << 1 | 1);
            }
            tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
        }
    }

    void update(int pos , int x , int y , int val , int id){
        if(x > y || pos < x || pos > y)return;
        push_down(x , y , id);
        if(pos == x && y == pos){
            tree[id].val = max(val , tree[id].val);
        }
        else{
            int mid = (x + y) >> 1;
            if(pos <= mid){
                update(pos , x , mid , val , id << 1);
            } 
            else{
                update(pos , mid + 1 , y , val , id << 1 | 1);
            }
            tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
        }
    }

    int query(int l , int r , int x , int y , int id){
        if(x > y || x > r || y < l)return 0;
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
        return max(query(l , r , x , mid , id << 1) , query(l , r , mid + 1 , y , id << 1 | 1));
    }

} black , white;

map<int , int> mp , imp;
vector<int> tmp;
seg segs[maxn];
int N , tot = 0;

void disk(){
    sort(tmp.begin() , tmp.end());
    for(int i : tmp){
        if(!mp[i]){
            mp[i] = ++tot;
            imp[tot] = i;
        }
    }
}

int solve(){
    sort(segs + 1 , segs + 1 + N);
    for(int i = 1; i <= N; ++i){
        int l = mp[segs[i].l] , r = mp[segs[i].r];
        ID printf("process [%d %d] with type = %d\n" , l , r , segs[i].t);
        if(segs[i].t == 1){ // black
            white.add_range(0 , l - 1 , 0 , tot , 1 , 1); // [1 , l] += 1
            ID printf("white [%d %d] += 1\n" , 0 , l - 1);
            int mx = white.query(0 , l - 1 , 0 , tot , 1);
            ID printf("current best mx = %d\n" , mx);
            black.update(r , 0 , tot , mx , 1);
            ID printf("black pos = %d updated to %d\n" , r , mx);
        }
        else{ // white
            black.add_range(0 , l - 1 , 0 , tot , 1 , 1); // [1 , l] += 1
            ID printf("black [%d %d] += 1\n" , 0 , l - 1);
            int mx = black.query(0 , l - 1 , 0 , tot , 1);
            ID printf("current best mx = %d\n" , mx);
            white.update(r , 0 , tot , mx , 1);
            ID printf("white pos = %d updated to %d\n" , r , mx);
        }
    }
    return max(black.tree[1].val , white.tree[1].val);
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d %d" , &segs[i].l , &segs[i].r , &segs[i].t); --segs[i].t;
        tmp.push_back(segs[i].l);
        tmp.push_back(segs[i].r);
    }
    disk();
    printf("%d\n" , solve());
}