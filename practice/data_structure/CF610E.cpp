#include <bits/stdc++.h>
using namespace std;
// we use a range tree to maintain the count of adjcent symbols 
// and use lazy propogation to handel range update
const int maxn = 2e5 + 10;
const int maxsz = maxn * 4;
int N , M , K;
char a[maxn];
struct node {
    int cnt[10][10] , lsym , rsym;
} tree[maxn * 6];
int lazy[maxn * 6];

node merge(const node& lhs , const node& rhs){
    node ret;
    for(int i = 0; i < K; ++i){
        for(int j = 0; j < K; ++j){
            ret.cnt[i][j] = lhs.cnt[i][j] + rhs.cnt[i][j];
        }
    }
    ret.lsym = lhs.lsym;
    ret.rsym = rhs.rsym;
    ret.cnt[lhs.rsym][rhs.lsym] += 1;
    return ret;
}

void mark(int l , int r , int id , int sym){ // cover [l , r] with sym 
    for(int i = 0; i < K; ++i){
        for(int j = 0; j < K; ++j){
            tree[id].cnt[i][j] = 0;
        }
    }
    tree[id].cnt[sym][sym] = r - l;
    tree[id].lsym = tree[id].rsym = lazy[id] = sym;
}

void push(int l , int r , int id){ // push mark down
    if(lazy[id] != -1){
        int mid = (l + r) >> 1;
        mark(l , mid , id << 1 , lazy[id]);
        mark(mid + 1 , r , id << 1 | 1 , lazy[id]);
        lazy[id] = -1;        
    }
}

void build(int l , int r , int id){
    lazy[id] = -1;
    if(l == r){
        tree[id].lsym = tree[id].rsym = a[l] - 'a';
    }
    else{
        int mid = (l + r) >> 1;
        build(l , mid , id << 1);
        build(mid + 1 , r , id << 1 | 1);
        assert(id * 2 + 1 < maxn * 6);
        tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }
}

void update(int l , int r , int x , int y , int id , int sym){
    if(l > r || x > y || r < x || y < l)return ;
    push(x , y , id);
    if(l <= x && y <= r){
        // [x , y] in [l , r] , so we cover it
        mark(x , y , id , sym);
        return ;
    }
    int mid = (x + y) >> 1;
    if(r <= mid)
        update(l , r , x , mid , id << 1 , sym);
    else if(l > mid)
        update(l , r , mid + 1 , y , id << 1 | 1 , sym);
    else{
        update(l , r , x , mid , id << 1 , sym);
        update(l , r , mid + 1 , y , id << 1 | 1 , sym);
    }
    assert(id * 2 + 1 < maxn * 6);
    tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
}

int main(){
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    */
    scanf("%d %d %d" , &N , &M , &K);
    scanf("%s" , (a + 1));
    build(1 , N , 1);
    for(int kase = 1; kase <= M; ++kase){
        int t;
        cin >> t;
        if(t == 1){
            int l , r;
            char c;
            scanf("%d %d %c" , &l , &r , &c);
            update(l , r , 1 , N , 1 , c - 'a');
        }
        else if(t == 2){
            string p;
            cin >> p;
            int ans = 0;
            for(int i = 0; i < K; ++i){
                for(int j = i; j < K; ++j){
                    ans += tree[1].cnt[p[j] - 'a'][p[i] - 'a'];
                }
            }
            printf("%d\n" , ans + 1);
        }
    }
}