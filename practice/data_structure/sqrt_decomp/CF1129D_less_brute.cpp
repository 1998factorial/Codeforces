// O(N ** 2)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int maxn = 1e5 + 10;
int N , K;
int a[maxn] , cnt[maxn];
ll DP[maxn];
vector<int> pos[maxn];

int main(){
    int i , j , k;
    scanf("%d %d" , &N , &K);
    for(i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    DP[0] = 1;
    for(i = 1; i <= N; ++i){
        int x = a[i] , sz , sum = 1;
        pos[x].push_back(i);
        sz = pos[x].size();
        cnt[i] = 1;
        if(sz >= 2)cnt[pos[x][sz - 2]] = -1;
        if(sz >= 3)cnt[pos[x][sz - 3]] = 0; 
        for(j = i - 1; j >= 0; --j){
            if(sum <= K){
                DP[i] += DP[j];
                DP[i] %= mod;
            }
            sum += cnt[j];
        }
    }
    printf("%lld\n" , DP[N]);
}