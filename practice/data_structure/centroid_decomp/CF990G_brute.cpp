/*
    number of different gcd is small, bounded by logN
    therefore , we can just bruteforce. takes about 4 second
s*/
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const int lim = 2e5;
vector<int> g[maxn];
ll ans[maxn];
ll a[maxn];
int N;
map<int , ll> cnt[maxn];

int gcd(int n , int m){
    return n == 0 ? m : gcd(m % n , n);
}

void DFS(int v , int p){
    ++cnt[v][a[v]];
    ++ans[a[v]];
    for(int u : g[v]){
        if(u != p){
            DFS(u , v);
            for(auto& e1 : cnt[v]){
                for(auto& e2 : cnt[u]){
                    ans[gcd(e1.x , e2.x)] += (ll)e1.y * e2.y; 
                }
            }
            for(auto& e : cnt[u]){
                cnt[v][gcd(a[v] , e.x)] += e.y;
            }
            cnt[u].clear();
        }
    }
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%lld" , &a[i]);
    for(int i = 1; i < N; ++i){
        int x , y; 
        scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    DFS(1 , 1);
    for(int i = 1; i <= lim; ++i){
        if(ans[i])printf("%d %lld\n" , i , ans[i]);
    }
}