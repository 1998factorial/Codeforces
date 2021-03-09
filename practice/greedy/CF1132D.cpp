#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int maxn = 2e5 + 10;
int N , K;
ll a[maxn] , b[maxn];

struct computer {
    ll ai , bi , t;
    computer(){}
    computer(ll x , ll y , ll z) : ai(x) , bi(y) , t(z) {}
    bool operator < (const computer& rhs) const {
        return t < rhs.t;
    }
    bool operator > (const computer& rhs) const {
        return t > rhs.t;
    }
};

bool check(ll mid){
    priority_queue<computer , vector<computer> , greater<computer>> q;
    for(int i = 1; i <= N; ++i){
        q.push(computer(a[i] , b[i] , a[i] / b[i]));
    }
    for(int t = 1; t <= K; ++t){
        computer c = q.top();
        q.pop();
        if(c.t + 1 < t)return 0;
        if(c.t + 1 >= K)return 1;
        q.push(computer(c.ai + mid , c.bi , (c.ai + mid) / c.bi));
    }
    return 1;
}

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &a[i]);
    }
    ll bmax = 0;
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &b[i]);
        bmax = max(bmax , b[i]);
    }
    ll l = 0 , r = bmax * K , ans = -1;
    while(l <= r){
        ll mid = (l + r) >> 1;
        if(check(mid)){
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    printf("%lld\n" , ans);
}