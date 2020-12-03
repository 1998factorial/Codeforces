#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
const int INF = 1e9;
vector<int> p[maxn];
bool vis[maxn];
int nmultiple[maxn] , N , tag[maxn] , a[maxn];

int gcd(int x , int y){
    return x == 0 ? y : gcd(y % x , x);
}

int main(){
    for(int i = 2; i < maxn; ++i){
        if(!vis[i]){
            for(int j = i; j < maxn; j += i){
                vis[j] = 1;
                p[j].push_back(i);
            }
        }
    }
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        int x = 1; for(int j : p[a[i]])x *= j;
        a[i] = x; tag[a[i]] = 1;
    }
    if(tag[1]){
        printf("1\n");
        return 0;
    }
    int d = a[1];
    for(int i = 1; i <= N; ++i)d = gcd(d , a[i]);
    if(d > 1){
        printf("-1\n");
        return 0;
    }
    for(int i = 1; i < maxn; ++i){
        for(int j = i; j < maxn; j += i){
            nmultiple[i] += tag[j];
        }
    }
    int ans = INF;
    for(int i = 1; i <= N; ++i){
        int v = a[i] , sz = p[v].size() , up = (1 << sz) - 1;
        vector<int> DP(up + 1 , INF) , mp(up + 1 , 0);
        vector<vector<int>> ways(up + 1 , vector<int> (sz + 1));
        for(int mask = 0; mask <= up; ++mask){
            int x = 1;
            for(int j = 0; j < sz; ++j){
                if(mask >> j & 1){
                    x *= p[v][j];
                }
            }            
            mp[mask] = x;
            ways[mask][0] = nmultiple[x];
        }
        for(int j = 0; j < sz; ++j){
            for(int mask = 0; mask <= up; ++mask){
                int pmask = mask ^ (1 << j);
                ways[pmask][j + 1] = ways[pmask][j];
                if(mask >> j & 1){
                    ways[pmask][j + 1] -= ways[mask][j];
                }
            }
        }
        DP[up] = 1;
        for(int mask = up; mask >= 0; --mask){
            for(int pick = 0; pick <= up; ++pick){
                if(ways[pick][sz]){
                    DP[mask & pick] = min(DP[mask & pick] , DP[mask] + 1);
                }
            }
        }
        ans = min(ans , DP[0]);
    }
    printf("%d\n" , ans);
}