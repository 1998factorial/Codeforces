#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const int maxn = 1e5 + 10;
const int K = 26 * 2 + 10;
char s[maxn];
int a[maxn] , cnt[K];
int N , Q;
ll fac[maxn] , inv[maxn] , DP[maxn / 2] , ans[K][K] , tDP[maxn / 2];

inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

void init(){
    fac[0] = 1; inv[0] = qpow(fac[0] , MOD - 2);
    for(int i = 1; i < maxn; ++i)fac[i] = fac[i - 1] * i % MOD , inv[i] = qpow(fac[i] , MOD - 2);
    for(int i = 1; i <= N; ++i){
        if('a' <= s[i] && s[i] <= 'z'){
            a[i] = s[i] - 'a';
        }
        else if('A' <= s[i] && s[i] <= 'Z'){
            a[i] = s[i] - 'A' + 26;
        }
        ++cnt[a[i]];
    }
}

int main(){
    scanf("%s" , (s + 1));
    N = strlen(s + 1);
    init();
    DP[0] = 1; 
    // DP[j] = number of ways to select from first i alphabets to 
    // make sum of frequences = j
    ll good_way = fac[N / 2] * fac[N / 2] % MOD;
    for(int i = 0; i < K; ++i)good_way *= inv[cnt[i]] , good_way %= MOD;
    for(int i = 0; i < K; ++i){
        if(cnt[i] == 0)continue;
        for(int j = N / 2; j >= cnt[i]; --j){
            DP[j] += DP[j - cnt[i]];
            if(DP[j] >= MOD)DP[j] -= MOD;
        }
    }
    // ans[i][j] = number of ways that type i and j are in the same half
    for(int i = 0; i < K; ++i){
        if(cnt[i])ans[i][i] = DP[N / 2];
    }
    for(int i = 0; i < K; ++i){
        // for i != j, we want to find the number of ways that
        // we do not use cnt[i] and cnt[j] to make N / 2
        // here we use the "remove" technique in bag DP
        // if we do not use cnt[i] , DP[j] -= DP[j - cnt[i]]
        // enumerate in ascending order , as for each term we subtract ,
        // we have removed the contribution from cnt[i]
        for(int j = 0; j <= N / 2; ++j)tDP[j] = DP[j];
        // here we remove the ways that we get from using cnt[i]
        for(int j = cnt[i]; j <= N / 2; ++j){
            tDP[j] -= tDP[j - cnt[i]];
            if(tDP[j] < 0)tDP[j] += MOD;
        }
        for(int j = i + 1; j < K; ++j){
            // now we deal with j
            // remove the contribution from cnt[j]
            if(cnt[j] == 0)continue;
            for(int k = cnt[j]; k <= N / 2; ++k){
                tDP[k] -= tDP[k - cnt[j]];
                if(tDP[k] < 0)tDP[k] += MOD;
            }
            ans[j][i] = ans[i][j] = tDP[N / 2] * 2 % MOD; // i and j can be in either side
            // symmetry
            // add back the contribution from cnt[j]
            for(int k = N / 2; k >= cnt[j]; --k){
                tDP[k] += tDP[k - cnt[j]];
                if(tDP[k] >= MOD)tDP[k] -= MOD;
            }
        }
    }
    scanf("%d" , &Q);
    while(Q--){
        int x , y;
        scanf("%d %d" , &x , &y);
        printf("%lld\n" , ans[a[x]][a[y]] * good_way % MOD);
    }
}