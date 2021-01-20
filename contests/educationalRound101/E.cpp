#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
char s[maxn];
int N , K;

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        scanf("%d %d" , &N , &K);
        scanf("%s" , (s + 1));
        if(K <= 20){
            vector<bool> vis(1 << K);
            for(int i = 1; i + K - 1 <= N; ++i){
                int mask = 0;
                for(int j = 0; j < K; ++j){
                    if(s[i + K - 1 - j] == '1')mask |= (1 << j);
                }
                mask ^= (1 << K) - 1;
                vis[mask] = 1;
            }
            bool ok = 0;
            for(int mask = 0; mask < 1 << K && !ok; ++mask){
                if(!vis[mask]){
                    ok = 1;
                    printf("YES\n");
                    for(int j = K - 1; j >= 0; --j){
                        int v = mask >> j & 1;
                        printf("%d" , v);
                    }
                    printf("\n");
                }
            }
            if(!ok)printf("NO\n");
        }
        else{
            // put 000000..0000[brute force last 20 digits]
            vector<bool> vis(1 << 20);
            vector<int> sum(N + 1);
            for(int i = 1; i <= N; ++i){
                sum[i] = sum[i - 1] + (s[i] == '1');
            }
            for(int i = 1; i + K - 1 <= N; ++i){
                int mask = 0;
                for(int j = 0; j < 20; ++j){
                    if(s[i + K - 1 - j] == '1')mask |= (1 << j);
                }
                mask ^= (1 << 20) - 1;
                if(sum[i + K - 1 - 20] - sum[i - 1] == i + K - 1 - 20 - i + 1){
                    vis[mask] = 1;
                }
            }
            bool ok = 0;
            for(int mask = 0; mask < 1 << 20 && !ok; ++mask){
                if(!vis[mask]){
                    ok = 1;
                    printf("YES\n");
                    for(int i = 1; i <= K - 20; ++i){
                        printf("0");
                    }
                    for(int j = 19; j >= 0; --j){
                        int v = mask >> j & 1;
                        printf("%d" , v);
                    }
                    printf("\n");
                }
            }
            if(!ok){
                printf("NO\n");
            }
        }
    }
}