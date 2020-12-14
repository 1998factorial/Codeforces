#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a , b) for(int i = a; i >= b; --i)
using namespace std;
const short INF = 3e3;
int N , M;
char s[205] , t[205];
short DP[202][202][805] , base = 400;
array<short , 4> pre[202][202][805];

int main(){
    scanf("%s" , s + 1);
    scanf("%s" , t + 1);
    N = strlen(s + 1);
    M = strlen(t + 1);
    rep(i , 0 , N){
        rep(j , 0 , M){
            rep(k , 0 , 804){
                DP[i][j][k] = INF;
                pre[i][j][k] = {-1 , -1 , -1};
            }
        }
    }
    DP[0][0][base] = 0;
    rep(i , 0 , N){
        rep(j , 0 , M){
            rep(k , -N - M , N + M){
                short ck = k + base;
                // use (
                int ni = i + ((i == N || s[i + 1] != '(') ? 0 : 1);
                int nj = j + ((j == M || t[j + 1] != '(') ? 0 : 1);
                int nk = ck + 1;
                if(DP[ni][nj][nk] > DP[i][j][ck] + 1){
                    DP[ni][nj][nk] = DP[i][j][ck] + 1;
                    pre[ni][nj][nk] = {(short)i , (short)j , (short)ck , 1}; // (
                }
                if(k <= 0)continue;
                // use )
                ni = i + ((i == N || s[i + 1] != ')') ? 0 : 1);
                nj = j + ((j == M || t[j + 1] != ')') ? 0 : 1);
                nk = ck - 1;
                if(DP[ni][nj][nk] > DP[i][j][ck] + 1){
                    DP[ni][nj][nk] = DP[i][j][ck] + 1;
                    pre[ni][nj][nk] = {(short)i , (short)j , (short)ck , -1}; // )
                }
            }
        }
    }
    int ret = INF;
    rep(k , -N - M , N + M){
        short ck  = k + base;
        ret = min(ret , (int)DP[N][M][ck] + abs(k));
    }
    rep(k , -N - M , N + M){
        short ck  = k + base;
        if(DP[N][M][ck] + abs(k) == ret){
            vector<char> a;
            while(k != 0){
                if(k > 0)--k , a.push_back(')');
                else if(k < 0)++k , a.push_back('(');
            }
            while(1){
                array<short , 4> cur = pre[N][M][ck];
                if(cur[0] == -1)break;
                if(cur[3] == 1)a.push_back('(');
                else a.push_back(')');
                N = cur[0];
                M = cur[1];
                ck = cur[2];
            }
            reverse(a.begin() , a.end());
            for(auto& c : a){
                printf("%c" , c);
            }
            return 0;
        }
    }
    //printf("%d\n" , ret);
}