/*
    Dynamic programming , rating 2700
    key : only the 峰 and 谷 will make contribution to the answer
    DP[i][j][k] is the maximal answer we get from partitioning
    a[1..i] into j parts and the jth part is in state k.
    where
    k = 0 means : the jth part is 谷
    k = 1 means : the jth part is between [峰 谷)
    k = 2 means : the jth part is 峰
    k = 3 means : the jth part is between [谷 峰)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 10;

int N , K;
ll a[30000 + 10] , DP[30000 + 10][205][4];

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i <= N; ++i)scanf("%lld" , &a[i]);
    for(int j = 1; j <= K; ++j){
        for(int k = 0; k < 4; ++k){
            DP[0][j][k] = -INF;
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= K; ++j){
            ll c = (j > 1 && j < K) ? 2 : 1; // in the middle or not
            DP[i][j][0] = max(DP[i - 1][j][0] , DP[i - 1][j - 1][1]) - c * a[i]; // S[j] is 谷
            DP[i][j][2] = max(DP[i - 1][j][2] , DP[i - 1][j - 1][3]) + c * a[i]; // S[j] is 峰
            DP[i][j][1] = max(DP[i - 1][j][1] , DP[i][j][2]); // S[j] is in [峰 谷)
            DP[i][j][3] = max(DP[i - 1][j][3] , DP[i][j][0]); // S[j] is in [谷 峰)
            if(c > 1){
                DP[i][j][1] = max(DP[i][j][1] , DP[i - 1][j - 1][1]);
                DP[i][j][3] = max(DP[i][j][3] , DP[i - 1][j - 1][3]);
            }
            //for(int k = 0; k < 4; ++k)printf("DP[%d][%d][%d] = %lld\n" , i , j , k , DP[i][j][k]);
        }
    }
    ll ret = 0;
    for(int k = 0; k < 4; ++k)ret = max(ret , DP[N][K][k]);
    printf("%lld\n" , ret);
}
