#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
char a[55];
char req[402][55];
int val[402] , len[402] , DP[51][51][402][51][2];
int C , N;
// DP[l][r][i][j][k] = maximal euros we can get if we consider 
// a[l...r], given that we are building portion for the ith kid,
// up to prefix req[i][1...j] and k => a[l...r] needs to be used completely
// !k => a[l...r] do not need to be used completely

int solve(int l , int r , int i , int j , int k){
    if(l > r){
        return j >= len[i] ? val[i] : 0;
    }
    if(~DP[l][r][i][j][k]){
        return DP[l][r][i][j][k];
    }
    int& ret = DP[l][r][i][j][k];
    ret = -INF;
    if(i == 0){
        // we are not building any portion for any kid
        if(k == 0){ // ignore a[l], if we are not required to use a[l..r] completely
            ret = max(ret , solve(l + 1 , r , i , j , k));
        }
        // try to build up for some kid
        for(int ni = 1; ni <= C; ++ni){
            if(req[ni][1] == a[l]){
                ret = max(ret , solve(l + 1 , r , ni , 1 , k));
            }
        }
    }
    else{
        // we are building for the ith kid
        if(j >= len[i]){
            // we are done for ith kid
            ret = max(ret , solve(l , r , 0 , 0 , k) + val[i]);
        }
        else{
            // we stop building for ith kid
            // we need to keep building for ith kid
            if(a[l] == req[i][j + 1]){
                ret = max(ret , solve(l + 1 , r , i , j + 1 , k));
            }
            for(int m = l + 1; m <= r; ++m){
                if(a[m] == req[i][j + 1]){
                    ret = max(ret , solve(l , m - 1 , 0 , 0 , 1) + solve(m + 1 , r , i , j + 1 , k));
                }
            }
        }
    }
    return ret;
}

int main(){
    scanf("%s" , a + 1);
    N = strlen(a + 1);
    scanf("%d" , &C);
    for(int i = 1; i <= C; ++i){
        scanf("%s %d" , req[i] + 1 , &val[i]);
        len[i + C] = len[i] = strlen(req[i] + 1);
        val[i + C] = val[i];
        for(int j = 1; j <= len[i]; ++j){
            req[i + C][j] = req[i][len[i] - j + 1];
        }
    }
    C *= 2;
    memset(DP , -1 , sizeof(DP));
    printf("%d\n" , solve(1 , N , 0 , 0 , 0));
}