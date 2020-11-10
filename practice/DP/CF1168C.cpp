#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int maxn = 3e5 + 10;
int nex[maxn][20] , N , Q , a[maxn] , f[maxn][20];
// f[i][j] = minimal x > i st a[x] & (1 << j) > 0
// nex[i][j] = minimal x reachable from i st a[x] & (1 << j)

int main(){
    scanf("%d%d" , &N , &Q);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 20; ++j){
            nex[i][j] = INF;
            f[i][j] = INF;
        }
    }
    for(int i = N - 1; i >= 1; --i){
        for(int j = 0; j < 20; ++j){
            if(a[i + 1] & (1 << j))f[i][j] = min(i + 1  , f[i][j]);
            else f[i][j] = min(f[i][j] , f[i + 1][j]);
            //if(f[i][j] <= N)printf("f[%d][%d] = %d\n" , i , j , f[i][j]);
        }
    }
    for(int i = N; i >= 1; --i){
        for(int j = 0; j < 20; ++j){
            if(a[i] & (1 << j)){
                nex[i][j] = i;
            }
            else{
                int ans = INF;
                for(int k = 0; k < 20; ++k){
                    if(a[i] & (1 << k)){
                        if(f[i][k] <= N){
                            ans = min(ans , nex[f[i][k]][j]);
                        }
                    }
                }
                nex[i][j] = ans;
            }
            //if(nex[i][j] <= N)printf("nex[%d][%d] = %d\n" , i , j , nex[i][j]);
        }
    }
    while(Q--){
        int x , y , ok = 0;
        scanf("%d%d" , &x , &y);
        for(int i = 0; i < 20; ++i){
            if(((1 << i) & a[y]) && nex[x][i] <= y)ok = 1;
        }
        if(ok)printf("Shi\n");
        else printf("Fou\n");
    }
}