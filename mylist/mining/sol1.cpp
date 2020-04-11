#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// O(N^2K + N^3)TLE
// https://www.hackerrank.com/contests/world-codesprint-5/challenges/mining/problem
const int maxn = 5e3 + 10;
const ll inf = 1e18 + 10;

struct mine{
    ll x , w;
    mine(){}
    mine(int a , int b): x(a) , w(b) {}
    bool operator < (const mine& rhs) const {
        return x < rhs.x;
    }
}a[maxn];

ll DP[maxn][maxn];
ll val[maxn][maxn];
ll A[maxn]; // A[i] = w[1] + ... + w[i]
ll B[maxn]; // B[i] = w[1] * x[1] + ... + x[i] * w[i]
int N , K;

ll cost(int l , int k , int r){
    if(l > r || k < l || k > r)return 0;
    return a[k].x * (A[k] - A[l - 1]) - (B[k] - B[l - 1]) -
           a[k].x * (A[r] - A[k - 1]) + (B[r] - B[k - 1]);
}

int main(){
    cin >> N >> K;
    for(int i = 1; i <= N; ++i){
        cin >> a[i].x >> a[i].w;
    }
    sort(a + 1 , a + 1 + N);
    for(int i = 1; i <= N; ++i){
        A[i] = A[i - 1] + a[i].w;
        B[i] = B[i - 1] + a[i].w * a[i].x;
    }
    for(int i = 1; i <= N; ++i){
        for(int j = i; j <= N; ++j){
            val[i][j] = inf;
            for(int k = i; k <= j; ++k){
                val[i][j] = min(val[i][j] , cost(i , k , j));
            }
        }
    }
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= K; ++j){
            DP[i][j] = inf;
        }
    }
    DP[0][0] = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= min(K , i); ++j){
            DP[i][j] = inf;
            for(int k = i; k >= j; --k){
                DP[i][j] = min(DP[i][j] , DP[k - 1][j - 1] + val[k][i]);
            }
        }
    }
    cout << DP[N][K] << endl;
}
