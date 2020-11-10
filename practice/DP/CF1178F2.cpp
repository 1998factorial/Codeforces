#include <bits/stdc++.h>
#define ID if(1)
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int maxn = 1e6 + 10;
ll DP[1020][1020]; // DP[l][r] = answer to fill a[l..r]
int N , M , C[maxn] , a[maxn];
deque<int> pos[505];
int tot = 0;

int main(){
    int i , j , len , k , x , y;
    scanf("%d %d" , &N , &M);
    for(i = 1; i <= M; ++i){
        scanf("%d" , &C[i]);
    }
    // we can compress
    for(i = 1; i <= M; ++i){
        if(C[i] != C[i - 1]){
            a[++tot] = C[i];
        }
    }
    if(tot > 2 * N){ 
        // if we have more than 2N blocks, we can not finish with only N operations
        printf("0\n");
        return 0;
    }
    for(i = 1; i <= tot; ++i){
        pos[a[i]].push_back(i);
    }
    for(i = 1; i <= tot; ++i){
        DP[i][i] = pos[a[i]].front() >= i && pos[a[i]].back() <= i;
    }
    for(i = 1; i <= tot + 1; ++i){
        DP[i][i - 1] = 1; 
    }
    for(len = 2; len <= tot; ++len){
        for(i = 1; i + len - 1 <= tot; ++i){
            j = i + len - 1;
            int minc = N;
            for(k = i; k <= j; ++k){
                // find the first color in this segment
                minc = min(minc , a[k]);
            }
            if(pos[minc].front() >= i && pos[minc].back() <= j){
                // means it we can color i can be done in one go
                int l = pos[minc].front() , r = pos[minc].back();
                // DP[i][j] = sum{DP[i][x - 1] * DP[x][l - 1] * DP[r + 1][y] * DP[y + 1][j]} * sum
                ll lv = 0 , rv = 0 , sum = 1;
                for(x = i; x <= l; ++x){
                    lv += DP[i][x - 1] * DP[x][l - 1] % mod;
                    lv %= mod;
                }
                for(x = r; x <= j; ++x){
                    rv += DP[r + 1][x] * DP[x + 1][j] % mod;
                    rv %= mod;
                }
                for(x = 1; x < pos[minc].size(); ++x){
                    if(pos[minc][x] >= pos[minc][x - 1] + 1){
                        sum *= DP[pos[minc][x - 1] + 1][pos[minc][x] - 1];
                        sum %= mod;
                    }
                }
                DP[i][j] = sum * (lv * rv % mod) % mod;
            }
        }
    }
    printf("%lld\n" , DP[1][tot]);
}