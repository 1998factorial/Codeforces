#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int maxn = 2e3 + 10;
char s[maxn] , t[maxn];
int N;

int main(){
    int T;
    scanf("%d" , &T);
    while(T--){
        scanf("%d" , &N);
        scanf("%s" , s + 1);
        scanf("%s" , t + 1);
        // s[l..r] -> s[r,l..r-1] same as moving s[r] to pos l
        // so this operation can be interpreted as select some 
        // s[i], and move to some j, j < i (move to left , but not right)
        vector<vector<int>> cnts(N + 1 , vector<int>(26));
        vector<vector<int>> cntt(N + 1 , vector<int>(26));
        for(int i = 1; i <= N; ++i){
            for(int j = 0; j < 26; ++j){
                cnts[i][j] = cnts[i - 1][j] + ((s[i] - 'a') == j);
                cntt[i][j] = cntt[i - 1][j] + ((t[i] - 'a') == j);
            }
        }
        int ok = 1;
        for(int j = 0; j < 26; ++j){
            if(cnts[N][j] != cntt[N][j]){
                ok = 0;
            }
        }
        if(!ok){
            printf("-1\n");
            continue;
        }
        vector<vector<int>> DP(N + 1 , vector<int> (N + 1));
        // ans = N - longest common sequence
        // but with special condition
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= N; ++j){
                DP[i][j] = max(DP[i - 1][j] , DP[i][j - 1]);
                if(s[i] == t[j]){
                    int ok2 = 1;
                    for(int k = 0; k < 26; ++k){
                        if(cnts[N][k] - cnts[i - 1][k] < cntt[N][k] - cntt[j - 1][k]){
                            ok2 = 0;
                        }
                    }
                    if(ok2){
                        DP[i][j] = max(DP[i][j] , DP[i - 1][j - 1] + 1);
                    }
                }
            }
        }
        printf("%d\n" , N - DP[N][N]);
    }
}