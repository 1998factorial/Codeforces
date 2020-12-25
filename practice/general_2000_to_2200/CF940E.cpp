#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int a[maxn] , N , C;
ll DP[maxn];
int tree[maxn << 2];

void update(int l , int r , int pos , int val , int id){
    if(l > r || pos < l || pos > r)return;
    if(pos == l && pos == r){
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
    tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
}

int query(int l , int r , int x , int y , int id){
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
    return min(query(l , r , x , mid , id << 1) , query(l , r , mid + 1 , y , id << 1 | 1));
}

int main(){
    ll sum = 0;
    scanf("%d %d" , &N , &C);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]) , sum += a[i];
        update(1 , N , i , a[i] , 1);
    }
    for(int i = 1; i <= N; ++i)DP[i] = -1;
    DP[0] = 0;
    for(int i = 1; i <= N; ++i){
        DP[i] = max(DP[i] , DP[i - 1]);
        if(i - C >= 0){
            DP[i] = max(DP[i] , DP[i - C] + query(i - C + 1 , i , 1 , N , 1));
        }
    }
    printf("%lld\n" , sum - DP[N]);
}
