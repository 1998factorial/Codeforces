/*
    DP[l][r][x][y] = maximal total power if we hire x minions from a[l ... r] and killed y of them
    unfortunately, this approach fails
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 76;
const int inf = 1e9 + 10;
int DP[maxn][maxn][maxn][maxn];
bool vis[maxn][maxn][maxn][maxn];
int N , K;
int A[maxn] , B[maxn];


int get(int l , int r , int x , int y){
    if(x < 0 || y < 0 || x < y || x - y > K || x > r - l + 1)return -inf;
    if(l > r || x == y)return 0;
    int& ret = DP[l][r][x][y];
    if(vis[l][r][x][y])return ret;
    vis[l][r][x][y] = 1;
    for(int m = l; m <= r; ++m){
        // do not hire m
        for(int a = 0; a <= x; ++a){
            for(int b = 0; b <= a; ++b){
                if(y - b < 0)break;
                if(a >= K || x - a >= K)continue;
                if(l == 1 && r == 5 && x == 3 && y == 1){
                    printf("(%d , %d , %d , %d) = %d + (%d , %d , %d , %d) = %d\n" , l , m - 1 , a ,b , get(l , m - 1 , a , b), m + 1 , r , x - a , y - b , get(m + 1 , r , x - a , y - b) );
                }
                ret = max(ret , get(l , m - 1 , a , b) + get(m + 1 , r , x - a , y - b));
            }
        }
        // hire m and do not kill m
        for(int a = 0; a <= x - 1; ++a){
            for(int b = 0; b <= a; ++b){
                if(y - b < 0)break;
                if(a >= K || x - 1 - a >= K)continue;
                if(l == 1 && r == 5 && x == 3 && y == 1){
                    printf("(%d , %d , %d , %d) = %d + (%d , %d , %d , %d) = %d + %d\n" , l , m - 1 , a , b ,get(l , m - 1 , a , b), m + 1 , r , x - a - 1 , y - b , get(m + 1 , r , x - 1 - a , y - b),A[m]);
                }
                ret = max(ret , get(l , m - 1 , a , b) + get(m + 1 , r , x - 1 - a , y - b) + A[m]);
            }
        }
        // hire m and we kill m
        for(int a = 0; a <= x - 1; ++a){
            for(int b = 0; b <= a; ++b){
                if(y - b < 0)break;
                if(a >= K || x - 1 - a >= K)continue;
                if(l == 1 && r == 5 && x == 3 && y == 1){
                    printf("(%d , %d , %d , %d) = %d + (%d , %d , %d , %d) = %d + %d * %d\n" , l , m - 1 , a , b , get(l , m - 1 , a , b) , m + 1 , r , x - a - 1 , y - b - 1 , get(m + 1 , r , x - 1 - a , y - 1 - b) , B[m] , (x - y));
                }
                ret = max(ret , get(l , m - 1 , a , b) + get(m + 1 , r , x - 1 - a , y - 1 - b) + B[m] * (x - y));
            }
        }
    }
    printf("DP[%d][%d][%d][%d] = %d\n" , l , r , x , y , ret);
    return ret;
}

int solve(){
    // return the maximal power
    memset(DP , 0 , sizeof(DP));
    memset(vis , 0 , sizeof(vis));
    for(int i = 1; i <= N; ++i){
        DP[i][i][1][0] = A[i];
    }
    int ret = 0;
    for(int a = 0; a <= N; ++a){
        for(int b = 0; b <= a; ++b){
            if(a - b <= K){
                ret = max(ret , get(1 , N , a , b));
            }
        }
    }
    return ret;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> N >> K;
        for(int i = 1; i <= N; ++i)cin >> A[i] >> B[i];
        cout << solve() << endl;
    }
}
