#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
    int N , M;
    cin >> N >> M;
    vector<vector<char>> a(N , vector<char>(M));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cin >> a[i][j];
        }
    }
    if(N > 3 && M > 3){
        cout << -1 << endl;
        return 0;
    }
    if(N <= 1 || M <= 1){
        cout << 0 << endl;
        return 0;
    }
    vector<vector<char>> s(min(N , M) , vector<char>(max(N , M)));
    if(N > M){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                s[j][i] = a[i][j];
            }
        }
        swap(N , M);
        a = s;
    }
    int INF = N * M + 10;
    vector<vector<int>> DP(M , vector<int> (1 << N , INF));
    for(int mask = 0; mask < 1 << N; ++mask){
        int cnt = 0;
        for(int i = 0; i < N; ++i){
            int v = mask >> i & 1;
            cnt += v != (a[i][0] - '0');
        }
        DP[0][mask] = cnt;
    }
    for(int i = 0; i < M - 1; ++i){
        for(int mask = 0; mask < 1 << N; ++mask){
            if(DP[i][mask] >= INF)continue;
            for(int nmask = 0; nmask < 1 << N; ++nmask){
                int c1 = 0;
                c1 += mask >> 0 & 1;
                c1 += mask >> 1 & 1;
                c1 += nmask >> 0 & 1;
                c1 += nmask >> 1 & 1;
                if((c1 & 1) == 0)continue;
                if(N > 2){
                    int c2 = 0;
                    c2 += mask >> 1 & 1;
                    c2 += mask >> 2 & 1;
                    c2 += nmask >> 1 & 1;
                    c2 += nmask >> 2 & 1;
                    if((c2 & 1) == 0)continue;
                }
                int cnt = 0;
                for(int j = 0; j < N; ++j){
                    int v = nmask >> j & 1;
                    cnt += v != (a[j][i + 1] - '0');
                }
                DP[i + 1][nmask] = min(DP[i + 1][nmask] , DP[i][mask] + cnt);
            }
        }
    }
    int ret = INF;
    for(int mask = 0; mask < 1 << N; ++mask){
        ret = min(ret , DP[M - 1][mask]);
    }
    cout << ret << endl;
}