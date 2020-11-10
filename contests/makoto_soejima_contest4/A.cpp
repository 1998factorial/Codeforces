/*
    not many such divisorful numbers, around 1000
    so we can do as : use first i primes to keep building up the set of divisorful numbers
    be careful of overflow, use long double to avoid this annoying issue
*/
#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef long double ll;
typedef pair<ll , ll> ii; 
const ll lim = 1e18;
int K;
vector<int> primes;
bool vis[1000000];
set<ii> divisorful;
ll solve(){
    ll pos = 0;
    vector<ll> ans;
    for(auto& e : divisorful){
        ans.push_back(e.x);
    }
    while(pos < K){
        if(pos >= divisorful.size()){
            return -1;
        }
        ++pos;
    }
    ID printf("%d\n" , (int)ans.size());
    return ans[pos - 1];
}
void sieve(){
    for(int i = 2; i < 1000000; ++i){
        if(!vis[i]){
            primes.push_back(i);
            for(int j = i; j < 1000000; j += i){
                vis[j] = 1;
            }
        }
    }
}
void process(){
    sieve();
    divisorful.insert({1 , 1});
    int pos = 0;
    int nprimes = primes.size();
    for( ;pos < nprimes;){
        int old_sz = divisorful.size();
        vector<ll> ps;
        ps.push_back(1ll);
        set<ii> ndivisorful;
        ll p = primes[pos];
        while(p <= lim){
            ps.push_back(p);
            p *= primes[pos];
        }
        for(auto& e : divisorful){
            for(int i = 0; i < ps.size(); ++i){
                ll v = ps[i];
                if(e.x * v <= lim)ndivisorful.insert({e.x * v , e.y * (i + 1)});
                else break;
                //if(e.x * v == 864691128455135232){
                //    printf("%lld * %lld\n" , e.y , (ll)i + 1);
                    //return ;
                //}
            }
        }
        // brute force delete
        divisorful.clear();
        vector<ll> pq;
        pq.push_back(0); pq.push_back(0);
        for(auto& e : ndivisorful){
            if(e.y >= pq[1]){
                divisorful.insert(e);
            }
            pq.push_back(e.y);
            sort(pq.begin() , pq.end());
            reverse(pq.begin() , pq.end());
            pq.pop_back();
        }
        ID{
            printf("show divisorful set at prime = %d\n" , primes[pos]);
            for(auto& e : divisorful){
                printf("(%Lf , %Lf) " , e.x , e.y);
            }
            printf("\n");
        }
        if(divisorful.size() == old_sz){
            break;
        }
        ++pos;
    }
}

int main(){
    process();
    scanf("%d" , &K);
    printf("%lld\n" , (unsigned long long)solve());
}