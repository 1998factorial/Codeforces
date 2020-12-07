#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
const int INF = 1e9;
vector<int> ps[maxn];
bool vis[maxn];
int N , a[maxn] , nmul[maxn] , tag[maxn];

int gcd(int x , int y){
    return x == 0 ? y : gcd(y % x , x);
}

int main(){
    // prime factorise all numbers <= 3e5
    // no need to keep exp term as we only care if we can get to gcd = 1
    for(int i = 2; i < maxn; ++i){
        if(!vis[i]){
            for(int j = i; j < maxn; j += i){
                vis[j] = 1;
                ps[j].push_back(i);
            }
        }
    }
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        int x = 1; 
        for(int y : ps[a[i]])x *= y;
        a[i] = x;
        tag[x] = 1; // remove duplication
    }
    int d = a[1];
    for(int i = 2; i <= N; ++i)d = gcd(d , a[i]);
    if(d > 1){
        printf("-1\n");
        return 0;
    }
    if(tag[1]){
        printf("1\n");
        return 0;
    }
    // nmul[i] = # of elements in a that is divisible by i
    for(int i = 1; i < maxn; ++i){
        for(int j = i; j < maxn; j += i){
            nmul[i] += tag[j];
        }
    }
    int ans = INF;
    for(int i = 2; i < maxn; ++i){
        if(tag[i] == 0)continue;
        // we start with i , as the first element in our set
        // i has at most 6 distinct prime factors
        int sz = ps[i].size();
        vector<int> val(1 << sz , 1) , can(1 << sz);
        // can[mask] = number of elements divisible by exactly the primes in mask
        for(int mask = 0; mask < 1 << sz; ++mask){
            for(int j = 0; j < sz; ++j){
                if(mask >> j & 1){
                    val[mask] *= ps[i][j];
                }
            }
            can[mask] = 0;//nmul[val[mask]];
        }
        for(int mask = 0; mask < 1 << sz; ++mask){
            for(int nmask = 0; nmask < 1 << sz; ++nmask){
                if((mask & nmask) == mask){
                    can[mask] += (__builtin_popcount(mask) % 2 == __builtin_popcount(nmask) % 2 ? 1 : -1) * nmul[val[nmask]];
                }
            }
        }    
        vector<int> DP(1 << sz , INF);
        DP[(1 << sz) - 1] = 1;
        for(int mask = (1 << sz) - 1; mask >= 0; --mask){
            for(int cur = 0; cur < (1 << sz); ++cur){
                if(can[cur]){
                    DP[mask & cur] = min(DP[mask & cur] , DP[mask] + 1);
                }
            }
        }
        ans = min(ans , DP[0]);
    }
    printf("%d\n" , (ans > N ? -1 : ans));
}