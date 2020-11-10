// O(N ** 3)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int maxn = 1e5 + 10;
int N , K;
int a[maxn] , cnt[100][100];
ll DP[maxn];

int main(){
    int i , j , k;
    scanf("%d %d" , &N , &K);
    for(i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(i = 1; i <= N; ++i){
        for(j = i; j <= N; ++j){
            map<int , int> cc;
            for(k = i; k <= j; ++k){
                cc[a[k]]++;
            }
            for(auto& e : cc){
                if(e.second == 1)++cnt[i][j];
            }
        }
    }
    DP[0] = 1;
    for(i = 1; i <= N; ++i){
        for(j = i - 1; j >= 0; --j){
            if(cnt[j + 1][i] <= K){
                DP[i] += DP[j];
                DP[i] %= mod;
            }
        }
    }
    printf("%lld\n" , DP[N]);
}