#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a , b) for(int i = a; i >= b; --i)
using namespace std;
const int INF = 1e9;
// idea is from slow solution
// say in optimal solution we go from i to j, then we need some k, to i
// st, k < i & k + a[k] >= i & k + a[k] <= j - 1, DP is to speed this up
// DP[i][j] = min number of platforms need to close if 
// we are currently at platform i, and we covered [1...j]
int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        int N;
        scanf("%d" , &N);
        vector<int> a(N + 1);
        rep(i , 1 , N)scanf("%d" , &a[i]);
        vector<vector<int>> DP(N + 2 , vector<int>(N + 2));
        int cnt;
        rep(i , 2 , N){
            cnt = 0;
            rep(j , i , N)DP[i][j] = INF;
            rrep(j , i - 1 , 1){
                if(a[j] + j > i - 1){
                    DP[i][a[j] + j] = min(DP[i][a[j] + j] , DP[j][i - 1] + cnt);
                    ++cnt;
                }
            }
            rep(j , i + 1 , N)DP[i][j] = min(DP[i][j] , DP[i][j - 1]);
        }   
        printf("%d\n" , DP[N][N]);     
    }
}