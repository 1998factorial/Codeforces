/*
    Dynamic programming , rating 2400
    similar to POJ1390
    we can firstly , merge [1..1] and [0..0] into blocks
    DP[i][j][k] = maximal gain from s[i..j] given that to the right of j , there are
    k consecutive elements as s[j].
    transition : DP[i][j][k] = DP[i][j - 1][0] + gain[k + len[j]] if we merge s[j] with k external ones
    DP[i][j][k] = max{DP[i][m][len[j] + k] + DP[m + 1][j - 1][0]} if we do not merge s[j] yet , and
    leave len[j] + k of these elements until we finish all blocks in [m + 1 , j - 1]
*/
#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;

ll gain[105]; // gain[i] = maximal gain to merge i consecutive elements
int len[105];
int val[105];
int M;
int N;
ll a[105];
char s[105];
ll DP[105][105][105];
bool vis[105][105][105];

ll solve(int l , int r , int x){
    if(l > r)return 0;
    if(l == r){
        return gain[x + len[l]];
    }
    if(vis[l][r][x]){
        return DP[l][r][x];
    }
    ll& ret = DP[l][r][x];
    vis[l][r][x] = 1;
    ret = max(ret , solve(l , r - 1 , 0) + gain[x + len[r]]);
    for(int m = l; m <= r; ++m){
        if(val[r] == val[m]){
            ret = max(ret , solve(l , m , len[r] + x) + solve(m + 1 , r - 1 , 0));
        }
    }
    if(ID)printf("DP[%d][%d][%d] = %lld\n" , l , r , x , DP[l][r][x]);
    return ret;
}

int main(){
    cin >> N;
    cin >> (s + 1);
    for(int i = 1; i <= N; ++i)cin >> a[i];
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j <= i; ++j){
            gain[i] = max(gain[i] , gain[i - j] + a[j]);
        }
        if(ID)printf("gain[%d] = %lld\n" , i , gain[i]);
    }
    M = 1;
    len[M] = 1;
    val[M] = (s[M] == '0') ? 0 : 1;
    for(int i = 2; i <= N; ++i){
        if(s[i] == s[i - 1]){
            ++len[M];
        }
        else{
            ++M;
            ++len[M];
            val[M] = (s[i] == '0') ? 0 : 1;
        }
    }
    if(ID)for(int i = 1; i <= M; ++i){
        printf("len[%d] = %d\n" , i , len[i]);
        printf("val[%d] = %d\n" , i , val[i]);
    }
    printf("%lld\n" , solve(1 , M , 0));
}
