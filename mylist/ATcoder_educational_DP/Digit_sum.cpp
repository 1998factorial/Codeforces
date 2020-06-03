#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 1e4 + 10;
int number[maxn]; // K
int N;
int D;
ll DP[maxn][105][2];
string s;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    cin >> D;
    N = s.size();
    for(int i = 0; i < N; ++i){
        number[i + 1] = s[i] - '0';
    }
    // [1 , K]
    // no leading zero
    // flag of strictly less
    DP[0][0][0] = 1;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < D; ++j){
            for(int k = 0; k < 2; ++k){
                if(DP[i][j][k] == 0)continue;
                for(int cur = 0; cur < 10; ++cur){
                    if(k == 0 && cur > number[i + 1])break;
                    DP[i + 1][(j + cur) % D][k || cur < number[i + 1]] += DP[i][j][k];
                    DP[i + 1][(j + cur) % D][k || cur < number[i + 1]] %= mod;
                }
            }
        }
    }
    ll ret = DP[N][0][0] + DP[N][0][1];
    cout << (ret - 1 + mod) % mod << endl;
}
