#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
int N , M;
char a[1005][1005];
int DP[1005][1005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            cin >> a[i][j];
        }
    }
    DP[1][1] = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(a[i][j] == '.'){
                if(i - 1 >= 1 && a[i - 1][j] == '.')
                    DP[i][j] = (DP[i][j] + DP[i - 1][j]) % mod;
                if(j - 1 >= 1 && a[i][j - 1] == '.')
                    DP[i][j] = (DP[i][j] + DP[i][j - 1]) % mod;
            }
        }
    }
    cout << DP[N][M] << endl;
}
