/*
    time : O(N * K * logN)
*/
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int maxn = 2e5 + 10;
int N , K;
int L[105] , R[105];
struct min_segtree{
    int tree[maxn * 3];
    void init(){
        for(int i = 0; i <= 2 * 2 * N + 2048; ++i)tree[i] = INF;
    }
    void update(int l , int r , int pos , int id , int val){
        if(l > r || pos < l || pos > r)return;
        if(l == pos && pos == r){tree[id] = val;return;}
        int mid = (l + r) >> 1;
        if(pos <= mid)update(l , mid , pos , id << 1 , val);
        else update(mid + 1 , r , pos , id << 1 | 1 , val);
        tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
    }
    int query(int l , int r , int x , int y , int id){
        if(l > r || x > y || r < x || l > y)return INF;
        if(l <= x && y <= r)return tree[id];
        int mid = (x + y) >> 1;
        if(r <= mid)return query(l , r , x , mid , id << 1);
        if(l > mid)return query(l , r , mid + 1 , y , id << 1 | 1);
        return min(query(l , r , x , mid , id << 1) , query(l , r , mid + 1 , y , id << 1 | 1));
    }
}DP[105];

int main(){
    scanf("%d %d" , &N , &K);
    int i , j , lim = 2 * N;
    for(i = 1; i <= K; ++i)scanf("%d %d" , &L[i] , &R[i]);
    for(i = 0; i <= K; ++i){
        DP[i].init();
    }
    DP[0].update(0 , lim , 0 , 1 , 0);
    // DP[i][j] = min{DP[i][j - (R[i] - R[i - 1])]}
    // DP[i][j] = min{1 + DP[i - 1][R[i - 1] + t - j] , 0 <= t <= R[i] - L[i]}
    // DP[i][j] = min{2 + DP[i - 1][j - R[i] + R[i - 1] + t] , 0 <= t <= R[i] - L[i]}
    for(i = 1; i <= K; ++i){
        for(j = 0; j <= lim && j <= R[i]; ++j){
            // solve for DP[i][j]
            int zero = (j - R[i] + R[i - 1] >= 0) ? DP[i - 1].query(j - R[i] + R[i - 1] , j - R[i] + R[i - 1] , 0 , lim , 1) : INF;
            int one = 1 + DP[i - 1].query(max(0 , R[i - 1] - j) , min(lim , R[i - 1] - j + R[i] - L[i]) , 0 , lim , 1);
            int two = 2 + DP[i - 1].query(max(0 , j - R[i] + R[i - 1]) , min(lim , j - R[i] + R[i - 1] + R[i] - L[i]) , 0 , lim , 1);
            DP[i].update(0 , lim , j , 1 , min(zero , min(one , two)));
        }
    }
    if(R[K] - N < 0 || DP[K].query(R[K] - N , R[K] - N , 0 , lim , 1) >= INF){
        printf("Hungry\n");
    }
    else{
        printf("Full\n%d\n" , DP[K].query(R[K] - N , R[K] - N , 0 , lim , 1));
    }
}