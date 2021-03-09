#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e16;
const int maxn = 5e2 + 10;
int N , M , a[maxn] , p[maxn] , b[maxn];
ll DP[maxn];

// BRUTE FORCE

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &p[i]);
    }
    scanf("%d" , &M);
    for(int i = 1; i <= M; ++i){
        scanf("%d" , &b[i]);
    }
    for(int i = 0; i <= N; ++i){
        DP[i] = -INF;
    }
    DP[0] = 0;
    a[0] = 0;
    b[0] = 0 , b[M + 1] = N;
    for(int i = 1; i <= N; ++i){
        int l = 0 , r = M + 1 , pos = -1;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(b[mid] >= a[i]){
                r = mid - 1;
                pos = mid;
            }
            else{
                l = mid + 1;
            }
        }
        if(~pos && a[i] == b[pos]){
            for(int k = i - 1; k >= 0; --k){
                if(a[k] != b[pos - 1])continue;
                ll s = 0;
                for(int t = k + 1; t <= i - 1; ++t){
                    if(a[t] <= a[k] && p[t] > 0)s += p[t];
                }   
                DP[i] = max(DP[i] , DP[k] + s + p[i]);
            }
        }
    }
    ll mx = -INF;
    for(int i = 1; i <= N; ++i){
        if(a[i] == b[M]){
            ll v = DP[i];
            for(int j = i + 1; j <= N; ++j){
                if(a[j] <= a[i] && p[j] > 0){
                    v += p[j];
                }
            }
            mx = max(mx , v);
        }
    }
    if(mx <= -INF / 2){
        printf("NO\n");
    }
    else{
        ll sum = 0;
        for(int i = 1; i <= N; ++i)sum += p[i];
        printf("YES\n%lld\n" , sum - mx);
    }
}