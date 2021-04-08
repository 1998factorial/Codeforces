#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;
int N , Q;
int a[maxn];
bool vis[maxn];
map<int , int> p[maxn] , v[maxn] , id;
vector<int> primes , factorise[maxn];
multiset<int> freq[maxn];
ll ret;
// v[i][j] = the power of j in i
// p[i][j] = the power of j in a[i]
// freq[i] = the multiset of powers of i in the whole array a
ll gcd(ll n , ll m){
    return n == 0 ? m : gcd(m % n , n);
}

void mul(ll& x , ll y){
    x = (x * y) % mod;
}

void add(int pos , int val){
    for(auto& e : v[val]){
        int pi = e.first , xi = e.second;
        int cur_power = p[pos][pi];
        p[pos][pi] += xi;
        int cur_min = 0;
        if(freq[pi].size() >= N){
            cur_min = *freq[pi].begin();
        }
        if(cur_power){
            freq[pi].erase(freq[pi].find(cur_power));
        }
        freq[pi].insert(p[pos][pi]);
        if(freq[pi].size() >= N){
            for(int i = cur_min + 1; i <= *freq[pi].begin(); ++i){
                mul(ret , pi);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> Q;
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
    }
    for(int i = 2; i <= 200000; ++i){
        if(vis[i])continue;
        id[i] = primes.size();
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
    ret = 1;
    for(int i = 1; i <= N; ++i){
        add(i , a[i]);
    }
    for(int q = 1; q <= Q; ++q){
        int i , x;
        cin >> i >> x;
        add(i , x);
        cout << ret << endl;
    }
}