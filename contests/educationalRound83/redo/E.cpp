#include <bits/stdc++.h>
using namespace std;

const int maxn = 505;
const int inf = 1e9;
int a[maxn];
int can[maxn][maxn];
int DP[maxn];
int N;

int main(){
    cin >> N;
    for(int i = 0; i <= N; ++i){
        DP[i] = inf;
        for(int j = 0; j <= N; ++j){
            can[i][j] = -1;
        }
    }
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
        can[i][i] = a[i];
    }
    for(int len = 2; len <= N; ++len){
        for(int i = 1; i + len - 1 <= N; ++i){
            int j = i + len - 1;
            for(int k = i; k <= j && can[i][j] == -1; ++k){
                if(can[i][k] != -1 && can[k + 1][j] != -1 && can[i][k] == can[k + 1][j]){
                    can[i][j] = can[i][k] + 1;
                }
            }
        }
    }
    DP[0] = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = i; j >= 1; --j){
            if(can[j][i] > -1){
                DP[i] = min(DP[i] , DP[j - 1] + 1);
            }
        }
    }
    cout << DP[N] << endl;
}
