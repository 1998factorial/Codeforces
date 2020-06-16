/*
    Dynamic programming , rating 2400
    we can consider the each bit seperately.
    for each bit , DP[i][j] = # of ways that for the first i bits, where the largest index of putting 0 is j
    DP[i][j] = DP[i - 1][j] if i > j
    DP[i][i] = sum of DP[i - 1][k] for k < i
    we can ignore the first dimension of DP since i only depends on i - 1, we can also use prefix sums to replace the iteration
    we can use prefix sum differences on keeping track of which range must contain 1, by doing [l]++ , [r + 1]--.
    One more important thing, we need to avoid counting invalid case , such as , state DP[i][j] is not allowed to be consider
    in our answer if there exists [l , r] that needs to have at least 1 zero where j < l and r < i. So we need to use 2 pointers
    here to avoid it, using the fact that j is monotone.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const int maxn = 5e5 + 10;
int ones[maxn][35];
int DP[maxn][35];
int sum[35];
int maxL[maxn][35];
int K , N , M;

struct query{
    int l , r , x;
    query(){}
    query(int l_ , int r_ , int x_) : l(l_) , r(r_) , x(x_) {}
}qs[maxn];

int main(){
    scanf("%d %d %d" , &N , &K , &M);
    for(int i = 1; i <= M; ++i){
        scanf("%d %d %d" , &qs[i].l , &qs[i].r , &qs[i].x);
    }
    ll ret = 1ll;
    memset(maxL , -1 , sizeof(maxL));
    for(int bit = 0; bit < K; ++bit){
        // preprocess the restrictions for this bit
        for(int i = 1; i <= M; ++i){
            int l = qs[i].l , r = qs[i].r , x = qs[i].x;
            if(x & (1 << bit)){ // forced [l , r] to be all 1
                ++ones[l][bit];
                --ones[r + 1][bit];
            }
            else{ // forces [l , r] to have at least one 0
                maxL[r][bit] = max(maxL[r][bit] , l);
            }
        }
        for(int i = 1; i <= N; ++i){
            ones[i][bit] += ones[i - 1][bit];
            maxL[i][bit] = max(maxL[i][bit] , maxL[i - 1][bit]);
        }
        int pos = 0 , sum = 1;
        DP[0][bit] = 1;
        for(int i = 1; i <= N; ++i){
            if(ones[i][bit]){
                DP[i][bit] = 0;
            }
            else{
                DP[i][bit] = sum;
            }
            sum = (sum + DP[i][bit]) % mod;
            while(pos < maxL[i][bit]){ // subtract the invalid cases where pos is less than the largest index smaller than i to place a zero
                sum = (sum - DP[pos][bit] + mod) % mod;
                ++pos;
            }
            //printf("DP[%d][%d] = %d\n" , i , bit , DP[i][bit]);
        }
        //cout << sum << endl;
        ret = ret * sum % mod;
    }
    printf("%lld\n" , ret);
}
