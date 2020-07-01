#include <bits/stdc++.h>
#define ID 1
using namespace std;
typedef long long ll;

const ll INF = 1e18;
const int maxn = 2e5 + 10;
int N;
ll a[maxn];
ll DP[maxn][2];
// DP[i][0] = maximal even length subarray ending at i
// DP[i][1] = maximal odd length subarray ending at i

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d" , &N);
        ll sum = 0;
        for(int i = 0; i < N; ++i){
            scanf("%lld" , &a[i]);
            if((i & 1) == 0)sum += a[i];
            if((i & 1) == 0)a[i] *= -1;
            for(int j = 0; j < 2; ++j)DP[i][j] = -INF;
        }
        DP[0][1] = a[0];
        for(int i = 1; i < N; ++i){
            DP[i][0] = max(DP[i - 1][1] + a[i] , DP[i][0]);
            DP[i][1] = max(a[i] , DP[i - 1][0] + a[i]);
        }
        ll m = -INF;
        for(int i = 0; i < N; ++i){
            m = max(m , DP[i][0]);
        }
        printf("%lld\n" , max(sum , sum + m));
    }
}
