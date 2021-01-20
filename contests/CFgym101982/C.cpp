#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
int d[1005] , N , K , cnt[1005] , M = 1;
ll DP[1005];

int main(){
    scanf("%d %d" , &N , &K);
    vector<int> tmp;
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &d[i]);
    }
    sort(d + 1 , d + 1 + N);
    cnt[M] = 1;
    for(int i = 2; i <= N; ++i){
        if(d[i] == d[i - 1]){
            ++cnt[M];
        }
        else{
            ++M;
            ++cnt[M];
        }
    }
    DP[0] = 1;  
    for(int i = 1; i <= M; ++i){
        for(int j = K; j >= 1; --j){
            DP[j] += DP[j - 1] * cnt[i] % MOD;
            if(DP[j] >= MOD)DP[j] -= MOD;
        }
    }
    printf("%lld\n" , DP[K]);
}