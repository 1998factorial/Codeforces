/*
key:
    ans = sum {i * cnt[v(a) = i]}
    1 * cnt[1]
    2 * cnt[2]
    3 * cnt[3]
    == 
    3 * cnt[>=1]
    2 * cnt[>=2]
    1 * cnt[>=3]

    also, array beauty is at most max(a[i]) / (K - 1), pigeon hole principle
    as we have (K - 1) different sections to consider, assuming sorted, and the 
    maximal of the minimal among these sections is at most max(a[i]) / (K - 1).
*/
#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
typedef long long ll;

int a[1005] , N , K , M = 0;
int DP[1005][1005];
int sum[1005][1005];
// DP[i][j][x] = number of sequence that ends with a[i], length = j, and array beauty at least x
// DP[i][j][x] = sum{DP[k][j - 1][x] | a[k] - a[i] >= x}

ll solve(int x){
    //printf("solve for array beauty at least %d\n" , x);
    int i , j , k = 0;
    for(i = 0; i <= N; ++i){
        for(j = 0; j <= K; ++j){
            DP[i][j] = sum[i][j] = 0;
        }
    }
    for(i = 1; i <= N; ++i)DP[i][1] = 1;
    sum[1][1] = 1;
    for(i = 2; i <= N; ++i){
        while(k + 1 < i && a[k + 1] - a[i] >= x)++k;
        for(j = 2; j <= K; ++j){
            DP[i][j] = sum[k][j - 1];
            if(DP[i][j] >= MOD)DP[i][j] -= MOD;
        }
        for(j = 0; j <= K; ++j){
            sum[i][j] = DP[i][j] + sum[i - 1][j];
            if(sum[i][j] >= MOD)sum[i][j] -= MOD;
        }
    }
    int ret = 0;
    for(i = 1; i <= N; ++i){
        ret += DP[i][K];
        if(ret >= MOD)ret -= MOD;
    }
    return ret;
}

int main(){
    scanf("%d%d" , &N , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        M = max(M , a[i]);
    }
    a[0] = M + 1;
    sort(a + 1 , a + 1 + N);
    reverse(a + 1 , a + 1 + N);
    int ret = 0;
    for(int x = 1; x <= M / (K - 1); ++x){
        ret += solve(x);
        if(ret >= MOD)ret -= MOD;
    }
    printf("%d\n" , ret);
}