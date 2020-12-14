#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a , b) for(int i = a; i >= b; --i)
#define MAXN 2005
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
int N , M;
char s[MAXN][MAXN];
int row[MAXN][MAXN] , col[MAXN][MAXN];
int DP[MAXN][MAXN][2]; // 0 => right , 1 => down
int rsum[MAXN][MAXN][2] , csum[MAXN][MAXN][2];

void add(int& x , int y){
    x += y;
    if(x >= MOD)x -= MOD;
}

int main(){
    cin >> N >> M;
    rep(i , 1 , N){
        rep(j , 1 , M){
            cin >> s[i][j];
        }
    }
    rep(i , 1 , N){
        rep(j , 1 , M){
            row[i][j] = row[i][j - 1] + (s[i][j] == 'R');
        }
    }
    rep(i , 1 , M){
        rep(j , 1 , N){
            col[i][j] = col[i][j - 1] + (s[j][i] == 'R');
        }
    }
    if(N == 1 && M == 1){
        printf("%d\n" , s[1][1] == 'R' ? 0 : 1);
        return 0;
    }
    DP[1][1][0] = DP[1][1][1] = 1;
    rep(i , 0 , 1){
        rsum[1][1][i] = csum[1][1][i] = 1;
    }
    rep(i , 1 , N){
        rep(j , 1 , M){
            if(i == 1 && j == 1)continue;
            // if we go down here
            int l = 1 , r = j - 1 , t = -1;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(row[i][M] - row[i][mid] <= M - j){
                    t = mid , r = mid - 1;
                }
                else l = mid + 1;
            }
            if(~t){
                add(DP[i][j][0] , (rsum[i][j - 1][1] - rsum[i][t - 1][1] + MOD) % MOD);
                //rep(k , t , j - 1){
                //    add(DP[i][j][0] , DP[i][k][1]);
                //}
            }
            // if we go right here
            l = 1 , r = i - 1 , t = -1;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(col[j][N] - col[j][mid] <= N - i){
                    t = mid , r = mid - 1;
                }
                else l = mid + 1;
            }
            if(~t){
                add(DP[i][j][1] , (csum[i - 1][j][0] - csum[t - 1][j][0] + MOD) % MOD);
                //rep(k , t , i - 1){
                //    add(DP[i][j][1] , DP[k][j][0]);
                //}
            }
            rep(k , 0 , 1){
                rsum[i][j][k] = rsum[i][j - 1][k];
                add(rsum[i][j][k] , DP[i][j][k]);
                csum[i][j][k] = csum[i - 1][j][k];
                add(csum[i][j][k] , DP[i][j][k]);
            }
        }
    }
    add(DP[N][M][0] , DP[N][M][1]);
    printf("%d\n" , DP[N][M][0]);
}   