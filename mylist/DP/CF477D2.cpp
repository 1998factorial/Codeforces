#include <bits/stdc++.h>
#define ID if(1)
#define MOD 1000000007
using namespace std;
const int INF = 1e9;
int N , way[5005][5005] , sum[5005][5005] , ones[5005][5005] , MIN[5005][5005];
int LCP[5005][5005] , p[5005];
// LCP[i][j] = longest common prefix of a[j...] and a[i...]
// j < i
char a[5005];

int main(){
    scanf("%s" , a + 1);
    N = strlen(a + 1);
    p[0] = 1;for(int i = 1; i <= N; ++i)p[i] = p[i - 1] * 2 % MOD;
    for(int i = N; i >= 1; --i){
        for(int j = i - 1; j >= 1; --j){
            LCP[i][j] = a[i] == a[j] ? 1 + LCP[i + 1][j + 1] : 0;
        }
    }
    way[0][1] = 1;
    for(int i = 1; i <= N; ++i){
        sum[0][i] = sum[0][i - 1] + way[0][i];
        if(sum[0][i] >= MOD)sum[0][i] -= MOD;
    }
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            ones[i][j] = MIN[i][j] = INF;
        }
    }
    ones[0][1] = 0;
    for(int i = 1; i <= N; ++i)MIN[0][i] = min(MIN[0][i - 1] , ones[0][i]);
    // way[i][j] = # ways st segment ends with a[i] has length j
    // ones[i][j] = minimal number of "1" operations used if we have last segment ending with a[i] , length being j
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= i; ++j){
            if(j > 1 && a[i - j + 1] == '0')continue;
            if(i - j - j + 1 >= 1){
                int longest = LCP[i - j + 1][i - j - j + 1];
                int k = (longest >= j || a[i - j + longest + 1] >= a[i - j - j + longest + 1]) ? j : j - 1;
                way[i][j] = sum[i - j][k];
                ones[i][j] = min(MIN[i - j][k] + 1 , ones[i][j]);
            }
            else{
                way[i][j] = sum[i - j][j];
                ones[i][j] = min(MIN[i - j][j] + 1 , ones[i][j]);
            }
        }
        for(int j = 1; j <= N; ++j){
            sum[i][j] = sum[i][j - 1] + way[i][j];
            if(sum[i][j] >= MOD)sum[i][j] -= MOD;
            MIN[i][j] = min(MIN[i][j - 1] , ones[i][j]);
        }
    }
    printf("%d\n" , sum[N][N]);
    // find minimal length of operations
    // we want the number 2 + number 1 as small as possible
    int val = 0;
    int min_len = INF;
    for(int j = 1; j <= N; ++j){
        int i = N - j + 1;
        if(a[i] == '1'){
            val += p[j - 1];
            if(val >= MOD)val -= MOD;
        }
        //printf("val = %d\n" , val);
        if(ones[N][j] >= INF)continue;
        //printf("ones[%d][%d] = %d\n" , N , j , ones[N][j]);
        if(j < 25){
            min_len = min(min_len , ones[N][j] + val);
            //printf("for length = %d , val = %d\n" , j , ones[N][j] + val);
        }
        else{
            if(min_len == INF){
                min_len = (val + ones[N][j]) % MOD;
                //printf("for length = %d , val = %d\n" , j , min_len);
                break;
            }
        }
    }
    printf("%d\n" , min_len);
}