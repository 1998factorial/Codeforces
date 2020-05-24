#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 10;
const ll inf = 1e18;
int h[maxn];
ll a[maxn];
ll DP[maxn];
int N;

struct maxtree{
    ll tree[maxn << 2];
    void build(int l , int r , int id){
        if(l == r){
            tree[id] = -inf;
        }
        else{
            int mid = (l + r) >> 1;
            build(l , mid , id << 1);
            build(mid + 1 , r , id << 1 | 1);
            tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
        }
    }
    void update(int l , int r , int pos , ll val , int id){
        if(l > r || pos < l || pos > r)return;
        if(l == r && l == pos){
            tree[id] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid){
            update(l , mid , pos , val , id << 1);
        }
        else{
            update(mid + 1 , r , pos , val , id << 1 | 1);
        }
        tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
    }
    ll query(int l , int r , int x , int y , int id){
        if(l <= x && y <= r){
            return tree[id];
        }
        int mid = (x + y) >> 1;
        if(mid < l){
            return query(l , r , mid + 1 , y , id << 1 | 1);
        }
        if(mid >= r){
            return query(l , r , x , mid , id << 1);
        }
        return max(
            query(l , r , x , mid , id << 1),
            query(l , r , mid + 1 , y , id << 1 | 1)
        );
    }

}T;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; ++i){
        cin >> h[i];
    }
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
    }
    T.build(0 , N , 1);
    T.update(0 , N , 0 , DP[0] , 1);
    ll ret = 0;
    for(int i = 1; i <= N; ++i){
        DP[i] = T.query(0 , h[i] - 1 , 0 , N , 1) + a[i];
        ret = max(ret , DP[i]);
        T.update(0 , N , h[i] , DP[i] , 1);
    }
    cout << ret << endl;
}
