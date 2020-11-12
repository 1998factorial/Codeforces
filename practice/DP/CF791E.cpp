#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int INF = 1e9;
int N , a[80] , DP[76][76][76][2];
char A[80];
vector<int> pos[3];
// DP[i][j][k][last one is V ?] = minimal number of operations needed
// to make length i + j + k string, with i V's , j K's and k X's, st 
// the last character is V or not.

int main(){
    cin >> N;
    cin >> (A + 1);
    vector<int> cnt(3);
    for(int i = 1; i <= N; ++i){
        if(A[i] == 'V')a[i] = 0;
        else if(A[i] == 'K')a[i] = 1;
        else a[i] = 2;
        pos[a[i]].push_back(i);
        ++cnt[a[i]];
    }
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            for(int k = 0; k <= N; ++k){
                for(int f : {0 , 1}){
                    DP[i][j][k][f] = INF;
                }
            }
        }
    }
    DP[0][0][0][0] = 0;
    for(int len = 0; len < N; ++len){
        for(int i = 0; i <= cnt[0]; ++i){
            for(int j = 0; j <= cnt[1]; ++j){
                for(int k = 0; k <= cnt[2]; ++k){
                    if(i + j + k < len)continue;
                    if(i + j + k > len)break;
                    for(int f : {0 , 1}){
                        if(DP[i][j][k][f] >= INF)continue;
                        ID printf("DP[%d][%d][%d][%d] = %d\n" , i , j , k , f , DP[i][j][k][f]);
                        // if we append V
                        if(i < cnt[0]){
                            int p = pos[0][i];
                            vector<int> ccnt(3);
                            for(int x = 1; x <= p; ++x){
                                ++ccnt[a[x]];
                            }
                            DP[i + 1][j][k][1] = min(DP[i + 1][j][k][1] , DP[i][j][k][f] + max(0 , ccnt[1] - j) + max(0 , ccnt[2] - k));
                            ID printf("update DP[%d][%d][%d][%d] = %d\n" , i + 1 , j , k , 1 , DP[i + 1][j][k][1]);
                        }
                        // if we append K
                        if(j < cnt[1] && f == 0){
                            int p = pos[1][j];
                            vector<int> ccnt(3);
                            for(int x = 1; x <= p; ++x){
                                ++ccnt[a[x]];
                            }
                            DP[i][j + 1][k][0] = min(DP[i][j + 1][k][0] , DP[i][j][k][f] + max(0 , ccnt[0] - i) + max(0 , ccnt[2] - k));
                            ID printf("update DP[%d][%d][%d][%d] = %d\n" , i , j + 1 , k , 0 , DP[i][j + 1][k][0]);
                        }
                        // if we append X
                        if(k < cnt[2]){
                            int p = pos[2][k];
                            vector<int> ccnt(3);
                            for(int x = 1; x <= p; ++x){
                                ++ccnt[a[x]];
                            }
                            DP[i][j][k + 1][0] = min(DP[i][j][k + 1][0] , DP[i][j][k][f] + max(0 , ccnt[0] - i) + max(0 , ccnt[1] - j));
                            ID printf("update DP[%d][%d][%d][%d] = %d\n" , i , j , k + 1 , 0 , DP[i][j][k + 1][0]);
                        }
                    }
                }
            }
        }
    }
    ID for(int f : {0 , 1})printf("DP[%d][%d][%d][%d] = %d\n" , cnt[0] , cnt[1] , cnt[2] , f , DP[cnt[0]][cnt[1]][cnt[2]][f]);
    cout << min(DP[cnt[0]][cnt[1]][cnt[2]][0] , DP[cnt[0]][cnt[1]][cnt[2]][1]) << endl;
}






/*#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int INF = 1e9;
int N;
int DP[80][80][3][3];
int a[80];
char A[80];
// ... 0 , 1 ... is not allowed
int main(){
    cin >> N;
    cin >> (A + 1);
    for(int i = 1; i <= N; ++i){
        if(A[i] == 'V')a[i] = 0;
        else if(A[i] == 'K')a[i] = 1;
        else a[i] = 2;
    }
    for(int l = 1; l <= N; ++l){
        for(int r = l; r <= N; ++r){
            for(int x : {0 , 1 , 2}){
                for(int y : {0 , 1 , 2}){
                    DP[l][r][x][y] = INF;
                }
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        DP[i][i][a[i]][a[i]] = 0;
    }
    for(int len = 2; len <= N; ++len){
        for(int l = 1; l + len - 1 <= N; ++l){
            int r = l + len - 1;
            for(int x : {0 , 1 , 2}){
                for(int y : {0 , 1 , 2}){
                    if(len == 2 && x == 0 && y == 1)continue;
                    // consider a[l] , a[l+1...r]
                    if(a[l] == x){
                        for(int nx : {0 , 1 , 2}){
                            if(x == 0 && nx == 1)continue;
                            DP[l][r][x][y] = min(DP[l][r][x][y] , DP[l + 1][r][nx][y]);
                        }
                    }
                    // now we need to consider the case where 
                    // we move a[l] to some where in a[l+1...r]
                    for(int m = l + 1; m < r; ++m){ // move a[l] to a[m]
                        for(int nx : {0 , 1 , 2}){
                            for(int ny : {0 , 1 , 2}){
                                if(a[l] == 0 && nx == 1)continue;
                                if(ny == 0 && a[l] == 1)continue;
                                DP[l][r][x][y] = min(
                                    DP[l][r][x][y],
                                    DP[l + 1][m][x][ny] + DP[m + 1][r][nx][y] + m - l
                                );
                            }
                        }
                    }
                    // move a[l] to a[r]
                    if(a[l] == y){
                        for(int ny : {0 , 1 , 2}){
                            if(ny == 0 && a[l] == 1)continue;
                            DP[l][r][x][y] = min(DP[l][r][x][y] , DP[l + 1][r][x][ny] + r - l);
                        }
                    }
                    // consider a[l...r-1] a[r]
                    if(a[r] == y){
                        for(int ny : {0 , 1 , 2}){
                            if(ny == 0 && y == 1)continue;
                            DP[l][r][x][y] = min(DP[l][r][x][y] , DP[l][r - 1][x][ny]);
                        }
                    }
                    // now we need to consider the case where
                    // we move a[r] to some where in a[l...r-1]
                    for(int m = r - 1; m > l; --m){
                        for(int nx : {0 , 1 , 2}){
                            for(int ny : {0 , 1 , 2}){
                                if(ny == 0 && a[r] == 1)continue;
                                if(a[r] == 0 && nx == 1)continue;
                                DP[l][r][x][y] = min(
                                    DP[l][r][x][y],
                                    DP[l][m - 1][x][ny] + DP[m][r - 1][nx][y] + r - m
                                );
                            }
                        }
                    }
                    // move a[r] to a[l]
                    if(a[r] == x){
                        for(int nx : {0 , 1 , 2}){
                            if(x == 0 && nx == 1)continue;
                            DP[l][r][x][y] = min(DP[l][r][x][y] , DP[l][r - 1][nx][y] + r - l);
                        }
                    }
                    if(DP[l][r][x][y] < INF)printf("DP[%d][%d][%d][%d] = %d\n" , l , r , x , y , DP[l][r][x][y]);
                }
            }
        }
    }
    int ret = INF;
    for(int i : {0 , 1 , 2}){
        for(int j : {0 , 1 , 2}){
            if(N > 2)ret = min(ret , DP[1][N][i][j]);
            if(N == 2 && !(i == 0 && j == 1))ret = min(ret , DP[1][N][i][j]);
            if(N == 1)ret = min(ret , DP[1][N][i][j]);
        }
    }
    cout << ret << endl;
}
*/