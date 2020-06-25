/*
    Dynamic programming , math (divisor function) , rating 2600

    d(n) = |{x , x | n}| , which is the divisor function , and note that d(a * b) = d(a) * d(b) if gcd(a , b) = 1
    the goal is to calculate sum{ d(i * j * k) for i in [1 , a] , j in [1 , b] , k in [1 , c]}
    by the property of divisor function above, it might be helpful if we calculate d(x) for each prime x, in the order of
    descending primes
    so we can answer the following question: when ranges are [1 , a] , [1 , b] , [1 , c] , and the largest prime that will be
    in the product is p, what is the answer ?
    let the solution to this subproblem be DP[a][b][c][p], we can enumerate the powers of this prime p
    say from first dimension, we get p^x , from second and third we get p^y and p^z , now in total, we get p^(x + y + z)
    so for range [1 , a] , since, all integers will be a multiple of p^x , now we focus on range [1 , a / p^x] and similar for
    other 2 ranges. once we fix the power of p, we can not use p anymore , and will focus on smaller primes

    # primes in [1 , 2000] is 303
    time complexity should not be too bad as each time we are decreasing by half on at least 1 of the first 3 dimensions
    and decreased by 1 on the last dimension.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1ll << 30;
const int maxn = 2005;

map<array<int , 4>  , ll> DP;
vector<int> primes;
bool vis[maxn];

ll solve(int a , int b , int c , int i){
    if(i < 0)return 1; // no primes left
    array<int , 4> key = {a , b , c , i};
    sort(key.begin() , key.begin() + 3); // sort first 3 elements
    auto it = DP.find(key);
    if(it != DP.end()){
        return DP[key];
    }
    ll ret = 0;
    int p = primes[i];
    for(int x = 0 , na = a; na >= 1; ++x , na /= p){
        for(int y = 0 , nb = b; nb >= 1; ++y , nb /= p){
            for(int z = 0 , nc = c; nc >= 1; ++z , nc /= p){
                // fixing the power of p , and relax on the remaining i - 1 primes
                ll cnt = solve(na , nb , nc , i - 1) * (x + y + z + 1) % mod; // d(p^(x + y + z)) = (x + y + z + 1)
                ret += cnt; ret %= mod;
            }
        }
    }
    DP[key] = ret;
    return ret;
}

int main(){
    int a , b , c; cin >> a >> b >> c;
    for(int i = 2; i <= maxn; ++i){ // sieve get all primes in [1 , 2000]
        if(!vis[i]){
            primes.push_back(i);
            for(int j = i; j <= maxn; j += i){
                vis[j] = 1;
            }
        }
    }
    cout << solve(a , b , c , primes.size() - 1) << endl;
}
