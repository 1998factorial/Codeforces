#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const ll INF = 1e18;
char s[maxn];
int N , x , y , cnt[maxn][2];
int main(){
    scanf("%s" , s + 1);
    scanf("%d %d" , &y , &x);
    N = strlen(s + 1);
    ll ans = INF;
    // in optimal solution, for ?????? we always have 0000011111
    // or 111111000000
    // we have ??????.. -> 0000..1111
    // start with 0000000
    ll v = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 2; ++j){
            cnt[i][j] += cnt[i - 1][j];
        }
        if(s[i] == '1'){
            v += 1ll * y * cnt[i - 1][0];
            ++cnt[i][1];
        }
        else{
            v += 1ll * x * cnt[i - 1][1];
            ++cnt[i][0];
        }
    }
    ans = min(ans , v);
    // now we gradually change the suffix to 1s
    int nq = 0;
    for(int i = N; i >= 1; --i){
        if(s[i] != '?')continue;
        v -= 1ll * x * cnt[i - 1][1];
        v += 1ll * y * cnt[i - 1][0];
        int nones = cnt[N][1] - cnt[i][1] + nq;
        int nzeros = N - i - nones;
        v -= 1ll * y * nones;
        v += 1ll * x * nzeros;
        ans = min(ans , v);
        ++nq;
    }
    // start with 111111
    memset(cnt , 0 , sizeof(cnt));
    v = 0 , nq = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 2; ++j){
            cnt[i][j] += cnt[i - 1][j];
        }
        if(s[i] == '0'){
            v += 1ll * x * cnt[i - 1][1];
            ++cnt[i][0];
        }
        else{
            v += 1ll * y * cnt[i - 1][0];
            ++cnt[i][1];
        }
    }
    ans = min(ans , v);
    // now we gradually change the suffix to 0s
    for(int i = N; i >= 1; --i){
        if(s[i] != '?')continue;
        v -= 1ll * y * cnt[i - 1][0];
        v += 1ll * x * cnt[i - 1][1];
        int nzeros = cnt[N][0] - cnt[i][0] + nq;
        int nones = N - i - nzeros;
        v -= 1ll * x * nzeros;
        v += 1ll * y * nones;
        ans = min(ans , v);
        ++nq;
    }
    printf("%lld\n" , ans);
}