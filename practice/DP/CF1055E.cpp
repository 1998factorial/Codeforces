#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int , int> pii;
const int INF = 1e9 + 10;
int N , a[1505] , S , M , K , DP[1505][1505] , b[1505] , sum[1505] , nex[1505];
pii seg[1505];
// check if answer is at least mid
// see if we can use M segments, such that
// #(a[i] <= mid) >= K
// this can be done with DP
// DP[i][j] = maximal of ones we can cover for first i elements if we choose
// at most j segments

int check(int mid){
    sum[0] = 0;
    for(int i = 1; i <= N; ++i){
        sum[i] = sum[i - 1] + (b[i] <= mid ? 1 : 0);
    }
    memset(DP , 0 , sizeof(DP));
    for(int j = 1; j <= M; ++j){
        for(int i = 1; i <= N; ++i){
            // if we do not choose to cover the a[i] with jth segment
            DP[i][j] = max(DP[i][j] , DP[i][j - 1]);
        }
        for(int i = 1; i <= N; ++i){
            if(nex[i]){
                // if we choose to cover a[i..nex[i]] with some segment
                DP[nex[i]][j] = max(DP[nex[i]][j] , DP[i - 1][j - 1] + sum[nex[i]] - sum[i - 1]);
            }
        }
        for(int i = 1; i <= N; ++i){
            // update DP 
            DP[i][j] = max(DP[i][j] , DP[i - 1][j]);
        }
    }
    return DP[N][M] >= K;
}

int main(){
    scanf("%d %d %d %d" , &N , &S , &M , &K);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]) , b[i] = a[i];
    sort(a + 1 , a + 1 + N);
    for(int i = 1; i <= S; ++i){
        scanf("%d %d" , &seg[i].x , &seg[i].y);
        for(int j = seg[i].x; j <= seg[i].y; ++j){
            nex[j] = max(nex[j] , seg[i].y);
        }
    }
    int l = 1 , r = N , ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(a[mid])){
            r = mid - 1;
            ans = a[mid];
        }
        else{
            l = mid + 1;
        }
    }
    printf("%d\n" , ans);
}