#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 10;
// the optimal ordering is , v[s[i]] <= v[s[i + 1]]
// intuition: we should always keep the good one until the end
int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        int N , K;
        scanf("%d %d" , &N , &K);
        vector<vector<int>> a(N + 1 , vector<int> (2));
        for(int i = 1; i <= N; ++i){
            // v , c
            scanf("%d %d" , &a[i][0] , &a[i][1]);
        }
        sort(a.begin() , a.end() , [&](vector<int>& l , vector<int>& r){
            return l[0] < r[0]; 
        });
        vector<vector<ll>> DP(N + 2 , vector<ll>(K + 1 , -INF));
        for(int j = 0; j <= K; ++j)DP[N + 1][j] = 0; // we can walk away empty handed
        for(int i = N; i >= 1; --i){
            DP[i][0] = max((ll)a[i][0] - a[i][1] , DP[i + 1][0]);
        }
        for(int j = 1; j <= K; ++j){
            for(int i = N; i >= 1; --i){
                DP[i][j] = max(DP[i][j] , DP[i + 1][j]); // ignore current item
                DP[i][j] = max(DP[i][j] , 
                    min(
                        (ll)a[i][0] - a[i][1] , 
                        DP[i + 1][j - 1] - a[i][1]
                    )
                );
            }
        }
        printf("%lld\n" , DP[1][K]);
    }
}