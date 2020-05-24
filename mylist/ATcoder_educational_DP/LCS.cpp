#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;

string s , t;
int DP[3005][3005];
int pre[3005][3005][2];
int N , M;
char a[3005] , b[3005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s >> t;
    N = s.size();
    M = t.size();
    for(int i = 1; i <= N; ++i){
        a[i] = s[i - 1];
    }
    for(int j = 1; j <= M; ++j){
        b[j] = t[j - 1];
    }
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= M; ++j){
            for(int k = 0; k < 2; ++k){
                pre[i][j][k] = -1;
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(a[i] == b[j]){
                if(DP[i][j] < DP[i - 1][j - 1] + 1){
                    DP[i][j] = DP[i - 1][j - 1] + 1;
                    pre[i][j][0] = i - 1;
                    pre[i][j][1] = j - 1;
                }
            }
            else{
                if(DP[i][j] < DP[i - 1][j]){
                    DP[i][j] = DP[i - 1][j];
                    pre[i][j][0] = i - 1;
                    pre[i][j][1] = j;
                }
                if(DP[i][j] < DP[i][j - 1]){
                    DP[i][j] = DP[i][j - 1];
                    pre[i][j][0] = i;
                    pre[i][j][1] = j - 1;
                }
            }
        }
    }
    int dx = N , dy = M;
    string ret = "";
    while(pre[dx][dy][0] != -1){
        int nx = pre[dx][dy][0];
        int ny = pre[dx][dy][1];
        if(nx + 1 == dx && ny + 1 == dy){
            ret += b[dy];
        }
        dx = nx;
        dy = ny;
    }
    reverse(ret.begin() , ret.end());
    cout << ret << endl;
}
