#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 1e4 + 10;

ll DP[maxn][105][2];
string s;
int N , D;

int main(){
    cin >> s;
    cin >> D;
    N = s.size();
    reverse(s.begin() , s.end());
    DP[0][0][1] = 1;
    for(int i = 0; i < N; ++i){
        for(int d = 0; d <= 9; ++d){
            for(int j = 0; j < D; ++j){
                int nj = (j + d) % D;
                for(int k = 0; k < 2; ++k){
                    int nk = d == s[i] - '0' ? k : d < s[i] - '0';
                    DP[i + 1][nj][nk] += DP[i][j][k];
                    DP[i + 1][nj][nk] %= mod;
                }
            }
        }
    }
    cout << (DP[N][0][1] - 1 + mod) % mod << endl;
}
