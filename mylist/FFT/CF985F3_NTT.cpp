#include <bits/stdc++.h>
#define ID if(1)
using namespace std;

/*
    p = 1009 , g = 3
*/
const int mod = 1009;
const int maxn = 2e5 + 10;
int N , M , K;
int cnt[maxn];
int r[maxn * 4];
vector<vector<int>> poly;

inline int qpow(int x , int n){
    int ret = 1;
    while(n){
        if(n & 1)ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }
    return ret;
}

void NTT(vector<int>& x , int len , int tp){
    int i , j , k , m , gn , g , tmp;
    for(int i = 0; i < len; ++i)
        if(r[i] < i)swap(x[i] , x[r[i]]);
    for(m = 2; m <= len; m <<= 1){
        k = m >> 1;
        gn = qpow(3 , (mod - 1) / m);
        for(i = 0; i < len; i += m){
            g = 1;
            for (j = 0; j < k; ++j, g = 1ll * g * gn % mod) {
                tmp = 1ll * x[i + j + k] * g % mod;
                x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                x[i + j] = (x[i + j] + tmp) % mod;
            }
        }
    }
    if (tp == -1) {
        reverse(x.begin(), x.end());
        int inv = qpow(len, mod - 2);
        for (i = 0; i < len; ++i) x[i] = 1ll * x[i] * inv % mod;
    }
}

vector<int> multiply(vector<int> a , vector<int> b){
    int n = a.size() , m = b.size() , len = 1 , i;
    while(len < 2 * n || len < 2 * m)len <<= 1;
    for(i = n; i < len; ++i)a.push_back(0);
    for(i = m; i < len; ++i)b.push_back(0);
    ID {
        printf("multiply a with b where a is : ");
        printf("\n");
        for(int i : a)printf("%d " , i);
        printf("b is : ");
        for(int i : b)printf("%d " , i);
        printf("\n");
    }
    for(i = 0; i < len; ++i)r[i] = (i & 1) * (len >> 1) + (r[i >> 1] >> 1);
    NTT(a , len , 1);
    NTT(b , len , 1);
    vector<int> c;
    for(i = 0; i < len; ++i)c.push_back(a[i] * b[i] % mod);
    NTT(c , len , -1);
    ID{
        printf("we get c : ");
        for(int i : c)printf("%d " , i);
        printf("\n");
    }
    return c;
}

vector<int> solve(int l , int r){
    if(l == r){
        vector<int> ret;
        for(int i : poly[l])ret.push_back(i);
        return ret;
    }
    int mid = (l + r) >> 1;
    return multiply(solve(l , mid) , solve(mid + 1 , r));
}

int main(){
    int i , x , j;
    scanf("%d %d %d" , &N , &M , &K);
    for(i = 1; i <= N; ++i){
        int x; scanf("%d" , &x); ++cnt[x];
    }
    for(i = 1; i <= M; ++i){
        if(cnt[i] == 0)continue;
        vector<int> pi;
        for(j = 0; j <= cnt[i]; ++j){
            pi.push_back(1);
        }
        poly.push_back(pi);
    }
    /*
    ID{
        printf("show polynomials \n");
        for(int i = 0; i < poly.size(); ++i){
            printf("the %d th poly : " , i);
            for(int j : poly[i]){
                printf("%d " , j);
            }
            printf("\n");
        }
    }
    */
    vector<int> ret = solve(0 , poly.size() - 1);
    printf("%d\n" , ret[K] % mod);
}