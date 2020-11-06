#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
typedef long long ll;

int N , M;
char S[3005] , T[3005];
ll DP[3005][3005];
// DP[i][j] = # ways to use S[1..j-i+1] to make T[i..j]

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cin >> (S + 1);
    cin >> (T + 1);
    N = strlen(S + 1);
    M = strlen(T + 1);
    int i , j , len;
    for(i = 1; i <= N; ++i){
        DP[i][i] = i <= M ? 2 * (S[1] == T[i]) : 2;
    }
    for(len = 2; len <= N; ++len){
        for(i = 1; i + len - 1 <= N; ++i){
            j = i + len - 1;
            if(i > M || T[i] == S[len])DP[i][j] += DP[i + 1][j] , DP[i][j] %= MOD;
            if(j > M || T[j] == S[len])DP[i][j] += DP[i][j - 1] , DP[i][j] %= MOD;
        }
    }
    ll ret = 0;
    for(i = M; i <= N; ++i)ret += DP[1][i] , ret %= MOD;
    cout << ret << endl;
}