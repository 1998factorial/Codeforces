#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const ll INF = 1e18;
// Hard DP , rating 2700
// goal is to find which patterns are valid
// we can not have +-+-+- or -+-+-+ alternating signs, as there must be at least two adjcent elements have same sign
// write a brute force pattern first
// we find that all valid patterns need to have (N + #(-1)) % 3 = 1
// this can be showed by induction, that all patterns that satisfy these 2 conditions are good
int a[maxn] , N;
ll DP[maxn][3][2][2][2];

int main(){
    scanf("%d" , &N);
    rep(i , 1 , N)scanf("%d" , &a[i]);
    if(N == 1){
        printf("%d\n" , a[1]);
        return 0;
    }
    rep(i , 0 , N){
        rep(j , 0 , 2){
            rep(k , 0 , 1){
                rep(x , 0 , 1){
                    rep(y , 0 , 1){
                        DP[i][j][k][x][y] = -INF;
                    }
                }
            }
        }
    }
    DP[1][2][1][0][0] = -a[1];
    DP[1][1][0][1][0] = a[1];
    rep(i , 1 , N - 1){
        rep(j , 0 , 2){
            rep(k , 0 , 1){
                rep(x , 0 , 1){
                    rep(y , 0 , 1){
                        if(DP[i][j][k][x][y] == -INF)continue;
                        int nj , nk , nx , ny;
                        // put - on a[i + 1]
                        nj = (2 + j) % 3;
                        nk = 1;
                        nx = 0;
                        ny = y || (nk && k);
                        DP[i + 1][nj][nk][nx][ny] = max(DP[i + 1][nj][nk][nx][ny] , DP[i][j][k][x][y] - a[i + 1]);
                        // put + on a[i + 1]   
                        nj = (1 + j) % 3;
                        nk = 0;
                        nx = 1;
                        ny = y || (nx && x);
                        DP[i + 1][nj][nk][nx][ny] = max(DP[i + 1][nj][nk][nx][ny] , DP[i][j][k][x][y] + a[i + 1]);   
                    }
                }
            }
        }
    }
    printf("%lld\n" , max(DP[N][1][1][0][1] , DP[N][1][0][1][1]));
}