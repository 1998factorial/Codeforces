#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 10;
int N , M , a[maxn] , b[maxn] , p[maxn * 2];
ll K , LCM , u[5] , v[5] , t[maxn];

/*
    Given 2 sequences of distinct integers where 
    they keep cycling. Goal is to find the smallest x
    such that the number of a[i] != b[i] is at least K for i <= x
    binary search x
    For each a[i] , find j , where b[j] = a[i]. find the first time i and j
    pair up. Let it be t. then for prefix of length x, they meet
    (x - t) / lcm(N , M) + 1 times
    how to find t?
    this is the same as solving for 
    {
        i = x mod N
        j = x mod M
    }
    which can be solved by Chinese remainder theorm
*/

ll gcd(ll n , ll m){
    return n == 0 ? m : gcd(m % n , n);
}

void extented_gcd(ll A , ll B , ll& d , ll& x , ll& y){
    if(B == 0){
        d = A;
        x = 1;
        y = 0;
    }
    else{
        extented_gcd(B , A % B , d , y , x);
        y -= x * (A / B);
    }
}

ll extented_crt(ll* m , ll* r , int n){
    // m[i] = the mod number in the ith equation
    // r[i] = the expected remainder for the ith equation
    ll MM = m[1] , R = r[1] , x , y , d;
    for(int i = 2; i <= n; ++i){
        extented_gcd(MM , m[i] , d , x , y);
        if((r[i] - R) % d)return -1;
        x = (r[i] - R) / d * x % (m[i] / d);
        R += x * MM;
        MM = MM / d * m[i];
        R %= MM;
    }
    return R > 0 ? R : R + MM;
}

bool check(ll mid){
    ll sum = 0;
    for(int i = 1; i <= N; ++i){
        if(t[i] == -1)continue;
        if(t[i] > mid)continue;
        sum += (mid - t[i]) / LCM + 1;
    }
    return mid - sum >= K;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> K;
    LCM = (ll)N * M / gcd(N , M);
    for(int i = 1; i <= N; ++i)cin >> a[i];
    for(int i = 1; i <= M; ++i)cin >> b[i] , p[b[i]] = i;
    for(int i = 1; i <= N; ++i){
        if(!p[a[i]]){
            t[i] = -1;
        }
        else{
            u[1] = N;
            v[1] = i % N;
            u[2] = M;
            v[2] = p[a[i]] % M;
            t[i] = extented_crt(u , v , 2);
        }
    }
    ll l = 1 , r = 1e18 , ans = -1;
    while(l <= r){
        ll mid = (l + r) / 2;
        if(check(mid)){
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    cout << ans << endl;
}