#include <bits/stdc++.h>
using namespace std;

const int maxn = 55;
int N , Q;
int a[maxn][maxn][maxn];
int DP[maxn][maxn][maxn][maxn];
int ans[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> Q;
    while(Q--){
        cin >> N;
        memset(ans , 0 , sizeof(ans));
        memset(DP , 0 , sizeof(DP));
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= N; ++j){
                for(int k = 1; k <= N; ++k){
                    cin >> a[i][j][k];
                }
            }
        }
        for(int d = 1; d <= N; ++d){
            for(int x = 1; x + d - 1 <= N; ++x){
                for(int y = 1; y + d - 1 <= N; ++y){
                    for(int z = 1; z + d - 1 <= N; ++z){
                        if(d == 1){
                            DP[x][y][z][d] = a[x][y][z];
                        }
                        else{
                            for(int u = 0; u < 2; ++u){
                                for(int v = 0; v < 2; ++v){
                                    for(int w = 0; w < 2; ++w){
                                        DP[x][y][z][d] = max(DP[x][y][z][d] , DP[x + u][y + v][z + w][d - 1]);
                                    }
                                }
                            }
                        }
                        if(DP[x][y][z][d] == d)++ans[d];
                    }
                }
            }
        }
        for(int i = 1; i <= N; ++i){
            cout << ans[i] << " ";
        }
        cout << endl;
    }
}
