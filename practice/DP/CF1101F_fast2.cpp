#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 10;
const int maxn = 250003;
const int maxl = 1e9 + 10;
int a[403] , N , M;
int DP[403][403][403];
// DP[i][j][k] = minimal maximal of intervals if we partition a[i .. j] into k intervals

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            for(int k = 1; k <= N; ++k){
                DP[i][j][k] = i == j ? 0 : maxl;
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = i; j <= N; ++j){
            DP[i][j][0] = a[j] - a[i];
        }
    }
    for(int k = 1; k <= N; ++k){    
        for(int i = 1; i <= N; ++i){
            int pos = i;
            for(int j = i + 1; j <= N; ++j){
                while(pos < j && max(DP[i][pos][k - 1] , a[j] - a[pos]) >= max(DP[i][pos + 1][k - 1] , a[j] - a[pos + 1]))++pos;
                DP[i][j][k] = max(DP[i][pos][k - 1] , a[j] - a[pos]);
            }
        }
    }
    ll ans = 0;
    for(int i = 1; i <= M; ++i){
        int s , f , c , r;
        scanf("%d %d %d %d" , &s , &f , &c , &r);
        ans = max(ans , (ll)DP[s][f][r] * c);
    }
    printf("%lld\n" , ans);
}
