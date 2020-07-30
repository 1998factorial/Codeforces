#include <bits/stdc++.h>
#define x first
#define y second
#define ID 0
using namespace std;
typedef pair<int , int> ii;
const int maxn = 2e5 + 10;
const int INF = 1e9 + 10;
int N , M , Q;
ii pos[maxn];
// ans be like : YES , YES , ... , YES , NO , ... , NO

struct max_tree{

    int tree[maxn << 2];

    int merge(int l , int r){
        return max(l , r);
    }

    void build(){
        for(int i = 0; i < maxn; ++i)tree[i] = -INF;
    }

    void update(int l , int r , int x , int y , int id , int v){
        if(l > r || x > y || r < x || l > y)return;
        if(l <= x && y <= r){
            tree[id] = v;
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

    int query(int l , int r , int x , int y , int id){
        if(l > r || x > y || y < l || x > r)return -INF;
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
        return max(
            query(l , r , x , mid , id << 1) ,
            query(l , r , mid + 1 , y , id << 1 | 1)
        );
    }

} T;


ii getCo(int x , int y){
    ii ret = make_pair((x + 1) / 2 , (y + 1) / 2);
    return ret;
}

bool isL(int x , int y){
    return x % 2 == 1;
}

bool check(int x){ // expecting linear scan
    if(ID)cout << "checking " << x << endl;
    T.build();
    for(int i = 1; i <= x; ++i){
        if(isL(pos[i].x , pos[i].y))continue;
        ii pt = getCo(pos[i].x , pos[i].y);
        T.update(pt.y , pt.y , 1 , M , 1 , pt.x);
        if(ID)cout << "update " << "y = " << pt.y << " to be " << pt.x << endl; 
    }
    for(int i = 1; i <= x; ++i){
        if(isL(pos[i].x , pos[i].y)){
            ii pt = getCo(pos[i].x , pos[i].y);
            if(ID)cout << "checking for " << pt.x << " " << pt.y << endl;
            if(T.query(pt.y , M , 1 , M , 1) >= pt.x){
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    scanf("%d %d %d" , &N , &M , &Q);
    for(int i = 1; i <= Q; ++i){
        scanf("%d %d" , &pos[i].x , &pos[i].y);
    }
    // binary search the first ans = NO
    int l = 1 , r = Q , ans = Q + 1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    for(int i = 1; i <= Q; ++i){
        if(i < ans)printf("YES\n");
        else printf("NO\n");
    }
}