#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const int maxn = 5e5 + 10;
int N , M;
char s[maxn];
ll C[100];
ll DP[maxn];

ll mul(ll x , ll y){
    return x * y % mod;
}

ll add(ll x , ll y ){
    ll ret = x + y;
    if(ret > mod)ret %= mod;
    return ret;
}

void init(){
    for(int i = 0; i <= 18; ++i){
        for(int a = 0; a <= 9; ++a){
            for(int b = 0; b <= 9; ++b){
                C[i] += (a + b == i);
            }
        }
    }
}






int main(){
    init();
    scanf("%d %d" , &N , &M);
    scanf("%s" , s + 1);
    while(M--){
        int pos , val; 
        scanf("%d %d" , &pos , &val);
        pos = pos;
        s[pos] = '0' + val;
        DP[N] = C[s[N] - '0'];
        DP[N + 1] = 1;
        for(int i = N - 1; i >= 1; --i){
            ll v1 = mul(DP[i + 1] , C[s[i] - '0']);
            int v = (s[i] - '0') * 10 + (s[i + 1] - '0');
            ll v2 = (s[i] != '0') ? mul(DP[i + 2] , C[v]) : 0;
            DP[i] = add(v1 , v2);
        }
        printf("%lld\n" , DP[1]);
    }
}