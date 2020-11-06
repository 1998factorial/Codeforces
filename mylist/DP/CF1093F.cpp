#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int maxk = 100 + 10;
int a[maxn] , N , K , len;
ll DP[maxn][maxk] , sum[maxn]; 
// DP[i][j] = answer if we put j at a[i]
// sum[i] = sum of DP[i][1 <= j <= K]
int cover[maxn][maxk];

int main(){
    int i , j , k;
    scanf("%d %d %d" , &N , &K , &len);
    for(i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        for(j = 1; j <= K; ++j){
            cover[i][j] = cover[i - 1][j];
            if(a[i] == -1)++cover[i][j];
            else if(a[i] == j)++cover[i][j];
        }
    }
    if(len == 1){
        printf("0\n");
        return 0;
    }
    sum[0] = 1;
    for(i = 1; i <= N; ++i){
        if(a[i] == -1){
            for(j = 1; j <= K; ++j){
                DP[i][j] = sum[i - 1];
                if(i < len)continue;
                if(cover[i][j] - cover[i - len][j] < len)continue;
                // remove a[i - len + 1 ... i] are all -1 or j
                // but we do not want over subtract DP[i - len][j]
                // as we subtracted the case where a[i - len] = j in DP[i - 1][j]
                DP[i][j] -= sum[i - len] - DP[i - len][j];
                if(DP[i][j] < 0)DP[i][j] += MOD;
            }
        }
        else{
            for(j = 1; j <= K; ++j){
                DP[i][j] = j == a[i] ? sum[i - 1] : 0;
                if(i < len)continue;
                if(cover[i][j] - cover[i - len][j] < len)continue;
                DP[i][j] -= sum[i - len] - DP[i - len][j];
                if(DP[i][j] < 0)DP[i][j] += MOD;
            }
        }
        for(j = 1; j <= K; ++j){
            //printf("DP[%d][%d] = %lld\n" , i , j , DP[i][j]);
            sum[i] += DP[i][j];
            sum[i] %= MOD;
        }
        //printf("sum[%d] = %lld\n" , i , sum[i]);
    }
    ll ans = 0;
    for(i = 1; i <= K; ++i){
        ans += DP[N][i];
        ans %= MOD;
    }
    printf("%lld\n" , ans);
}