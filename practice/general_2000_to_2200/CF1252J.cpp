#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
char a[maxn];
int N , K , G1 , G2 , G3 , DP[maxn][55] , nrock = 0 , nsoil = 0;
// DP[i][j] = maximal number of type 2 for a[1..i] with j type 3
int main(){
    scanf("%d %d %d %d %d" , &N , &K , &G1 , &G2 , &G3);
    scanf("%s" , (a + 1));
    for(int i = 1; i <= N; ++i){
        if(a[i] == '.')++nsoil;
        else ++nrock;
    }
    // consider using only type 2 and type 3
    memset(DP , -1 , sizeof(DP));
    DP[0][0] = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j <= nrock; ++j){
            if(~DP[i][j]){
                // skip
                DP[i + 1][j] = max(DP[i + 1][j] , DP[i][j]);
                // use type 2
                if(i + 2 <= N && a[i + 1] == '.' && a[i + 2] == '.'){
                    DP[i + 2][j] = max(DP[i + 2][j] , DP[i][j] + 1);
                }
                // use type 3
                if(i + 3 <= N && a[i + 1] == '.' && a[i + 2] == '#' && a[i + 3] == '.'){
                    DP[i + 3][j + 1] = max(DP[i + 3][j + 1] , DP[i][j]);
                }
            }
        }
    }
    int ret = 0;
    for(int j = 0; j <= nrock; ++j){
        if(~DP[N][j]){
            //printf("DP[%d][%d] = %d\n" , N , j , DP[N][j]);
            int lsoil = min(K , nsoil - 2 * DP[N][j] - 2 * j);
            int llsoil = max(0 , K - lsoil); // we have llsoil type 1 left
            int v = DP[N][j] * G2 + j * G3 + lsoil * G1;
            if(G1 > G2){
                // replace as much type 2 by type 1 as possible
                int can = min(2 * DP[N][j] , llsoil);
                v += can * G1;
                v -= ceil((double)can / 2) * G2;
            }
            else if(2 * G1 > G2){
                // replace some type 2 by type 1, but we can not get rid of 1 type 2 by 1 type 1
                int can = min(llsoil , 2 * DP[N][j]);
                if(can & 1)--can;
                v += can * G1;
                v -= can / 2 * G2;
            }
            ret = max(ret , v);
        }
    }
    printf("%d\n" , ret);
}