#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const ll inf = 1e18;
int N;
// dis(i -> j) = max(c[i] , a[j] - a[i])
// dis(i -> j) = c[i] + max(0 , a[j] - a[i] - c[i])
array<ll , 2> a[maxn]; // (a[i] , c[i])
vector<array<ll , 2>> g[maxn];
ll dis[maxn] , vis[maxn];

ll dijstra(){
    for(int i = 1; i <= N; ++i){
        dis[i] = inf;
        vis[i] = 0;
    }
    priority_queue<array<ll , 2> , vector<array<ll , 2>> , greater<array<ll , 2>>> q;
    dis[1] = 0;
    q.push({dis[1] , 1});
    while(!q.empty()){
        auto c = q.top();
        q.pop();
        ll d = c[0];
        int v = c[1];
        if(vis[v])continue;
        vis[v] = 1;
        for(auto& e : g[v]){
            int nv = e[0] , w = e[1];
            if(vis[nv])continue;
            if(dis[nv] > d + w){
                dis[nv] = d + w;
                q.push({dis[nv] , nv});
            }
        }
    }
    return dis[N];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> N;
    ll ans = 0;
    for(int i = 1; i <= N; ++i){
        cin >> a[i][0] >> a[i][1];
        ans += a[i][1];
    }
    sort(a + 1 , a + 1 + N);
    for(int i = 2; i <= N; ++i){
        g[i].push_back({i - 1 , 0}); // max(0 , a[i - 1] - a[i] - c[i]) = 0
    }
    for(int i = 1; i <= N; ++i){
        int j = -1 , l = i , r = N;
        while(l <= r){
            int mid = (l + r) / 2;
            if(a[mid][0] <= a[i][0] + a[i][1]){
                l = mid + 1;
                j = mid;
            }
            else r = mid - 1;
        }
        if(~j){
            g[i].push_back({j , 0});
            if(j < N)g[i].push_back({j + 1 , max(0ll , a[j + 1][0] - a[i][0] - a[i][1])});
        }
    }
    cout << ans + dijstra() << endl;
}