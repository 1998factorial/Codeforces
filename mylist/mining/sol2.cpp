#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// O((N + K) * logN * N) TLE

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

void solve_interval(int base , int l , int r , int x , int y){
    if(l > r)return;
    int mid = (l + r) >> 1;
    int best = base > x ? base : x;
    int up = y < mid ? y : mid;
    for(int i = best; i <= up; ++i){
        if(cost(base , i , mid) < cost(base , best , mid)){
            best = i;
        }
    }
    val[base][mid] = cost(base , best , mid);
    if(l < r){
        solve_interval(base , l , mid - 1, x , best);
        solve_interval(base , mid + 1 , r , best , y);
    }
}

void solve(int l , int r , int x , int y , int k){
    if(l > r)return;
    int mid = (l + r) >> 1;
    int pos = -1;
    DP[mid][k] = inf;
    for(int i = x; i <= min(y , mid); ++i){
        if(DP[mid][k] > DP[i - 1][k - 1] + val[i][mid]){
            DP[mid][k] = DP[i - 1][k - 1] + val[i][mid];
            pos = i;
        }
    }
    if(l < r){
        solve(l , mid - 1, x , pos , k);
        solve(mid + 1 , r , pos , y , k);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;
    for(int i = 1; i <= N; ++i){
        cin >> a[i].x >> a[i].w;
    }
    sort(a + 1 , a + 1 + N);
    for(int i = 1; i <= N; ++i){
        A[i] = A[i - 1] + a[i].w;
        B[i] = B[i - 1] + a[i].w * a[i].x;
    }
    // O(N * K * logN) time compute val[1 .. N][1 .. N]
    for(int i = 1; i <= N; ++i){
        solve_interval(i , i , N , i , N);
    }
    for(int i = 1; i <= N; ++i){
        DP[i][1] = val[1][i];
    }
    for(int i = 2; i <= K; ++i){
        solve(1 , N , 1 , N , i);
    }
    cout << DP[N][K] << endl;
}
