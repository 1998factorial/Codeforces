#include <bits/stdc++.h>
#define ID if(0)
using namespace std;

const int maxn = 1e5 + 10;
const int INF = 1e9 + 10;
int N;
int a[maxn];
int cnt[maxn];
int ans[maxn];

int solve(int k){ // each subarray has at most k distinct numbers , greedily solve for it
    int i = 1 , ans = 0 , x;
    for(; i <= N; ){
        int j = i , distinct = 0;
        while(i <= N && distinct <= k){
            if(cnt[a[i]] == 0)++distinct;
            ++cnt[a[i]];
            ++i;
        }
        for(x = j; x < i; ++x)--cnt[a[x]];
        if(distinct > k)--i;
        ++ans;
    }
    return ans;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    int SQRT = sqrt(N);
    for(int i = 1; i <= N; ++i){
        ans[i] = N;
    }
    for(int i = 1; i <= SQRT; ++i){ // solve for the first [1 , sqrt(N)]
        ans[i] = solve(i);
        ID printf("ans[%d] = %d\n" , i , ans[i]);
    }
    for(int i = N / SQRT + 4; i >= 1; --i){
        int l = 1 , r = N , best = N;
        // number of subarrays is i
        while(l <= r){
            int mid = (l + r) >> 1;
            if(solve(mid) > i){ // this is monotone
                l = mid + 1;
            }
            else{
                best = mid;
                r = mid - 1;
            }
        }
        for(int j = best; j <= N; ++j){
            ans[j] = min(i , ans[j]);
        }
    }
    for(int i = 1; i <= N; ++i){
        printf("%d " , ans[i]);
    }
    printf("\n");
}