#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(1)
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
vector<vector<ii>> g;
vector<ll> w;
vector<int> cnt;
int N;
ll S;

void DFS(int v , int id){
    if(~id)cnt[id] = (g[v].size() == 1);
    for(auto& e : g[v]){
        if(e.y != id){
            DFS(e.x , e.y);
            if(~id){
                cnt[id] += cnt[e.y];
            }
        }
    }
    //if(~id)printf("cnt[%d] = %d\n" , id , cnt[id]);
}

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        scanf("%d %lld" , &N , &S);
        g = vector<vector<ii>> (N + 1);
        cnt = vector<int> (N + 1 , 0);
        w = vector<ll> (N + 1);
        for(int i = 1; i < N; ++i){
            int u , v;
            scanf("%d %d %lld" , &u , &v , &w[i]);
            g[u].emplace_back(v , i);
            g[v].emplace_back(u , i);
        }
        DFS(1 , -1);
        auto f = [&](int i){
            return w[i] * cnt[i] - w[i] / 2 * cnt[i];
        };
        set<ii> vals;
        ll sum = 0;
        for(int i = 1; i < N; ++i){
            vals.insert({f(i) , i});
            sum += w[i] * cnt[i];
        }
        int ans = 0;
        while(sum > S){
            auto it = *vals.rbegin();
            int id = it.y;
            sum -= f(id);
            w[id] /= 2;
            vals.erase(prev(vals.end()));
            vals.insert({f(id) , id});
            ++ans;
        }
        printf("%d\n" , ans);
    }
}