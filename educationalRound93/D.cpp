#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll DP[205][205][205];
int cnt[3];
int v[3][205];

ll solve(int a , int b , int c){
    if(a < 0 || b < 0 || c < 0)return 0;
    int z = 0; 
    if(!a)++z; 
    if(!b)++z; 
    if(!c)++z;
    if(z > 1)return 0;
    if(~DP[a][b][c])return DP[a][b][c];
    ll& ret = DP[a][b][c];
    ret = 0;
    if(a && b){
        ret = max(ret , solve(a - 1 , b - 1 , c) + v[0][a] * v[1][b]);
    }
    if(a && c){
        ret = max(ret , solve(a - 1 , b , c - 1) + v[0][a] * v[2][c]);
    }
    if(b && c){
        ret = max(ret , solve(a , b - 1 , c - 1) + v[1][b] * v[2][c]);
    }
    return ret;
}

int main(){
    scanf("%d %d %d" , &cnt[0] , &cnt[1] , &cnt[2]);
    for(int i = 0; i < 3; ++i){
        for(int j = 1; j <= cnt[i]; ++j){
            scanf("%d" , &v[i][j]);
        }
        sort(v[i] + 1 , v[i] + cnt[i] + 1);
    }
    memset(DP , -1 , sizeof(DP));
    printf("%lld\n" , solve(cnt[0] , cnt[1] , cnt[2]));
}