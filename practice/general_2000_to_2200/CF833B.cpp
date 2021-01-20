#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int N , K , L , R , cost;
int a[35005] , DP[35005][55] , cnt[35005];

void query(int l , int r){ // invariant l <= r
    while(L < l){ //pop out
        --cnt[a[L]];
        if(!cnt[a[L]])--cost;
        ++L;
    }
    while(L > l){ //push in
        --L;
        if(!cnt[a[L]])++cost;
        ++cnt[a[L]];
    }
    while(R < r){ //push in
        ++R;
        if(!cnt[a[R]])++cost;
        ++cnt[a[R]];
    }
    while(R > r){ //pop out
        --cnt[a[R]];
        if(!cnt[a[R]])--cost;
        --R;
    }
}

void solve(int l , int r , int x , int y , int k){
    if(l > r)return;
    int mid = (l + r) >> 1;
    int pos = -1;
    DP[mid][k] = -INF;
    for(int i = x; i <= min(y , mid); ++i){
        query(i , mid);
        if(DP[mid][k] < DP[i - 1][k - 1] + cost){
            DP[mid][k] = DP[i - 1][k - 1] + cost;
            pos = i;
        }
    }
    solve(l , mid - 1 , x , pos , k);
    solve(mid + 1 , r , pos , y , k);
}

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    cost = 0;
    for(int i = 1; i <= N; ++i){
        if(!cnt[a[i]])++cost;
        DP[i][1] = cost;
        ++cnt[a[i]];
    }
    L = 1 , R = N;
    for(int j = 2; j <= K; ++j){
        solve(1 , N , 1 , N , j);
    }
    printf("%d\n" , DP[N][K]);
}
