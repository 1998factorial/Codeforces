#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int N , M , K , a[75][75];
int col[75][75][75];
int row[75][75];

int main(){
    cin >> N >> M >> K;
    for(int i = 1; i <= N; ++i){
        for(int  j = 1; j <= M; ++j){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= K; ++j){
            row[i][j] = -INF;
        }
    }
    row[0][0] = 0;
    for(int i = 1; i <= N; ++i){
        // solve for row[i]
        for(int i = 0; i <= M; ++i){
            for(int j = 0; j <= M; ++j){
                for(int k = 0; k <= K; ++k){
                    col[i][j][k] = -INF;
                }
            }
        }
        col[0][0][0] = 0;
        for(int j = 0; j < M; ++j){
            for(int k = 0; k <= M / 2; ++k){
                for(int x = 0; x < K; ++x){
                    col[j + 1][k][x] = max(col[j + 1][k][x] , col[j][k][x]);
                    if(k + 1 <= M / 2){
                        int nx = (x + a[i][j + 1]) % K;
                        col[j + 1][k + 1][nx] = max(col[j + 1][k + 1][nx] , col[j][k][x] + a[i][j + 1]);
                    }
                }
            }
        }
        for(int k = 0; k < K; ++k){
            // row[i - 1][k] to what state ?
            for(int j = 0; j <= M / 2; ++j){
                for(int x = 0; x < K; ++x){
                    int nk = (k + x) % K;
                    row[i][nk] = max(row[i][nk] , row[i - 1][k] + col[M][j][x]);
                }
            }
        }
    }
    cout << row[N][0] << endl;
}
