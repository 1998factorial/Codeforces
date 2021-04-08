#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;
int N , Q;
int a[maxn] , freq[maxn][45];
bool vis[maxn];
map<int , int> p[maxn] , v[maxn];
vector<int> primes , factorise[maxn];
array<int , 2> qs[maxn]; // (i , x)
/*
    this attempts fail as frequency of a prime can be much larger than 45
*/

// freq[i][j] = the number of elements in array a, that are divisible by i ^ j
// factorise[i] = the primes in i
// v[i][j] = the power of j in i
// p[i][j] = the power of j in a[i]

ll gcd(ll n , ll m){
    return n == 0 ? m : gcd(m % n , n);
}

void mul(ll& x , ll y){
    x = (x * y) % mod;
}

ll qpow(ll x , ll n){
    ll ret = 1;
    while(n){
        if(n & 1)mul(ret , x);
        mul(x , x);
        n /= 2;
    }
    return ret;
}

void div_mod(ll& x , ll y){ // return (x / y) % mod
    ll dy = qpow(y , mod - 2);
    mul(x , dy);
}

int main(){
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    */
    scanf("%d %d" , &N , &Q);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int i = 2; i <= 200000; ++i){
        if(vis[i])continue;
        primes.push_back(i);
        for(int j = i; j <= 200000; j += i){
            vis[j] = 1;
            factorise[j].push_back(i);
        }
    }
    for(int i = 2; i <= 200000; ++i){
        for(int j : factorise[i]){
            int tmp = i , cnt = 0;
            while(tmp % j == 0){
                ++cnt;
                tmp /= j;
            }
            v[i][j] = cnt;
        }
    }
    int nz = 0;
    for(int i = 1; i <= N; ++i){
        int val = a[i];
        if(val == 1){
            ++nz;
            continue;
        }
        for(auto& e : v[val]){
            p[i][e.first] = e.second;
            //printf("p[%d][%d] = %d\n" , i , e.first , e.second);
            for(int j = 0; j <= e.second; ++j){
                ++freq[e.first][j];
            }
            //printf("freq[%d][%d]++\n" , e.first , e.second);
        }
    }
    for(int i : primes){
        freq[i][0] += nz;
    }
    ll ret = a[1];
    for(int i = 2; i <= N; ++i){
        ret = gcd(ret , a[i]);
    }
    for(int q = 1; q <= Q; ++q){
        int pos , val;
        scanf("%d %d" , &pos , &val);
        if(val == 1){
            printf("%lld\n" , ret);
            continue;
        }
        // a[pos] is multiplied by val
        // say val has pi^xi
        // then p[pos][pi] += xi for each i
        int cnt = 0;
        for(auto& e : v[val]){
            ++cnt;
            int pi = e.first , xi = e.second;
            // we need to find the smallest power of pi
            int f = 0;
            for(int i = 36; i >= 0; --i){
                if(freq[pi][i] >= N){
                    f = i;
                    break;
                }
            }
            // pi^f is the current contribution in our gcd
            // div_mod(ret , qpow(pi , f));

            for(int i = 0; i <= p[pos][pi]; ++i){
                --freq[pi][i];
            }
            p[pos][pi] += xi;

            //printf("p = %d\n" , p[][]);

            for(int i = 0; i <= p[pos][pi]; ++i){
                ++freq[pi][i];
            }
            int nf = 0;
            for(int i = 36; i >= 0; --i){
                if(freq[pi][i] >= N){
                    nf = i;
                    break;
                }
            }
            for(int i = 1; i <= nf - f; ++i){
                mul(ret , pi);
            }
            //mul(ret , qpow(pi , f));
        }
        printf("cnt = %d\n" , cnt);
        printf("%lld\n" , ret);
    }
}