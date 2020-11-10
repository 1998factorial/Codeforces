#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int a[maxn][3];
int DP[maxn][3];
int N;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 3; ++j){
            cin >> a[i][j];
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 3; ++j){
            for(int k = 0; k < 3; ++k){
                if(j != k){
                    DP[i][j] = max(DP[i - 1][k] + a[i][j] , DP[i][j]);
                }
            }
        }
    }
    cout << max(DP[N][0] , max(DP[N][1] , DP[N][2])) << endl;
}
