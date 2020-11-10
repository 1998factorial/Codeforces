#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#include <bits/stdc++.h>
#include <stdio.h>
#include <algorithm>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
#define rep(i, a , b) for(int i = a; i <= (int)b; ++i)

// O(K * logN * N + N ^ 2) TLE

const int maxn = 5e3 + 5;
const ll inf = 1e18 + 1;

struct mine{
    ll x , w;
    mine(){}
    mine(int a , int b): x(a) , w(b) {}
    bool operator < (const mine& rhs) const {
        return x < rhs.x;
    }
}a[maxn];

ll DP[maxn][2];
int pos[2][maxn];
ll val[maxn][maxn];
ll A[maxn]; // A[i] = w[1] + ... + w[i]
ll B[maxn]; // B[i] = w[1] * x[1] + ... + x[i] * w[i]
int N , K;

template <class T>
inline void scan_d(T &ret)
{
    char c;
    ret = 0;
    while ((c = getchar()) < '0' || c > '9');
    while (c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0'), c = getchar();
    }
}

void Out(ll a)
{   //  输出外挂
    if (a < 0)
    {
        putchar('-');
        a = -a;
    }
    if (a >= 10)
    {
       Out(a / 10);
    }
    putchar(a % 10 + '0');
}

ll cost(int l , int k , int r){
    if(l > r || k < l || k > r)return 0;
    return a[k].x * (A[k] - A[l - 1]) - (B[k] - B[l - 1]) -
           a[k].x * (A[r] - A[k - 1]) + (B[r] - B[k - 1]);
}

void solve(int l , int r , int x , int y , int k){
    if(l > r)return;
    int mid = (l + r) >> 1;
    int pos = -1;
    DP[mid][k & 1] = inf;
    int up = y < mid ? y : mid;
    rep(i , x , up) {
        if(DP[mid][k & 1] > DP[i - 1][(k - 1) & 1] + val[i][mid]){
            DP[mid][k & 1] = DP[i - 1][(k - 1) & 1] + val[i][mid];
            pos = i;
        }
    }
    if(l < r){
        solve(l , mid - 1, x , pos , k);
        solve(mid + 1 , r , pos , y , k);
    }
}

int main(){
    //scanf("%d %d" , &N , &K);
    scan_d(N); scan_d(K);
    rep(i , 1 , N) {
        //scanf("%lld %lld" , &a[i].x , &a[i].w);
        scan_d(a[i].x);
        scan_d(a[i].w);
    }
    //sort(a + 1 , a + 1 + N);
    rep(i , 1 , N) {
        A[i] = A[i - 1] + a[i].w;
        B[i] = B[i - 1] + a[i].w * a[i].x;
    }
    // O(N * N) time compute val[1 .. N][1 .. N]
    rep(i , 1 , N) {
        val[i][i] = 0;
        pos[1][i] = i;
    }
    rep(len , 2 , N) {
        for(int i = 1; i + len - 1 <= N; ++i){
            int from = pos[(len - 1) & 1][i] , to = pos[(len - 1) & 1][i + 1];
            int best = from;
            rep(j , from , to) {
                if(cost(i , best , i + len - 1) > cost(i , j , i + len - 1)){
                    best = j;
                }
            }
            val[i][i + len - 1] = cost(i , best , i + len - 1);
            pos[len & 1][i] = best;
        }
    }

    rep(i , 1 , N) {
        DP[i][1] = val[1][i];
    }
    
    Out(DP[N][K & 1]);
}
