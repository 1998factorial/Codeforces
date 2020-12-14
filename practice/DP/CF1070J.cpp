#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a , b) for(int i = a; i >= b; --i)
#define pb push_back
#define ID if(0)
using namespace std;
const int maxn = 2e5 + 10;
int T , N , M , K;
char s[maxn];

int main(){
    scanf("%d" , &T);
    while(T--){
        scanf("%d %d %d" , &N , &M , &K);
        scanf("%s" , (s + 1));
        vector<int> cnt(26 , 0);
        rep(i , 1 , K)++cnt[s[i] - 'A'];
        vector<int> DP(K + 1);
        DP[0] = 1;
        // can we do it with no conflict ?
        rep(i , 0 , 25){
            if(!cnt[i])continue;
            rrep(j , K , cnt[i]){
                DP[j] |= DP[j - cnt[i]];
            }
        }
        int ok = 0;
        rep(i , N , K){
            if(DP[i] && K - i >= M){
                ok = 1;
            }
        }
        if(ok){
            printf("0\n");
        }
        else{
            // now, we need to have exactly one kind of character in both
            // row and col
            int ret = N * M;
            rep(i , 0 , 25){ // say char i will appear in both row & col
                if(!cnt[i])continue;
                rep(j , 1 , K)DP[j] = 0;
                rep(ni , 0 , 25){
                    if(ni == i)continue;
                    if(!cnt[ni])continue;
                    rrep(j , K , cnt[ni]){
                        DP[j] |= DP[j - cnt[ni]];
                    }
                }
                int sz = K - cnt[i];
                rep(j , max(0 , N - cnt[i]) , N - 1){
                    if(DP[j]){
                        int dr = N - j;
                        int dc = M - (sz - j);
                        if(dc <= 0)continue;
                        ret = min(ret , dr * dc);
                        ID cout << dr << " " << dc << endl;
                    }
                }
            }
            printf("%d\n" , ret);
        }
    }
}