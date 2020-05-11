#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename elemType>
inline void Read(elemType &T){
    elemType X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    T=(w?-X:X);
}

// for any shrub, if we can obtain at least 2 filled buckets , and all of them are mixed colored
// then we can always make them into at most 1 mixed bucket and the remaining ones being single
ll DP[505][505];
// DP[i][j] = maximal number of filled bukets if we left out j red berries after the ith shrub?
int N , K;
int a[505] , b[505];
ll sum[505];

int main(){
    int i , j , k , up , low;
    ll C , red_cnt , blue_cnt;
    Read(N);
    Read(K);
    memset(DP , -1 , sizeof(DP));
    DP[0][0] = 0;
    for(i = 0; i < N; ++i){
        Read(a[i + 1]);
        Read(b[i + 1]);
        sum[i + 1] = sum[i] + a[i + 1] + b[i + 1];
        for(j = 0; j < K; ++j){
            if(~DP[i][j]){ // left j red burries
                C = sum[i] - DP[i][j] * K;
                int q = (j + a[i + 1]) % K;
                // do not make mix color bucket
                DP[i + 1][q] = max(DP[i + 1][q] , DP[i][j] + (ll)(j + a[i + 1]) / K + (ll)(C - j + b[i + 1]) / K);
                up = min(a[i + 1] , K);
                low = max(0 , K - b[i + 1]);
                for(k = low; k <= up; ++k){
                    // brute force number of red burries in the mixed bucket from shrub i + 1
                    int p = (j + a[i + 1] - k) % K;
                    DP[i + 1][p] = max(DP[i + 1][p] , DP[i][j] + 1 + (j + a[i + 1] - k) / K + (C - j + b[i + 1] - K + k) / K);
                }
            }
        }
    }
    ll ret = 0;
    for(i = 0; i < K; ++i){
        if(ret < DP[N][i])ret = DP[N][i];
    }
    printf("%lld\n" , ret);
}
