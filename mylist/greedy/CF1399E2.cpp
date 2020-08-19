#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
const int INF = 1e9;
vector<vector<ii>> g;
vector<int> cnt , c;
vector<ll> w;
vector<ll> sum[3]; 
int N;
ll S;

void DFS(int v , int id){
    if(~id)cnt[id] = (g[v].size() == 1);
    for(auto& e : g[v]){
        if(e.y != id){
            DFS(e.x , e.y);
            if(~id)cnt[id] += cnt[e.y];
        }
    }
    //ID if(~id)printf("cnt[%d] = %d\n" , id , cnt[id]);
}

ll f(int i){
    return w[i] * cnt[i] - w[i] / 2 * cnt[i];
}

void solve(int v){
    sum[v].clear(); 
    set<ii> vals;
    ll acc = 0;
    for(int i = 1; i < N; ++i){
        if(c[i] == v){
            vals.insert({f(i) , i});
            acc += w[i] * cnt[i];
        }
    }
    while(acc){
        sum[v].push_back(acc);
        int id = vals.rbegin()->y;
        vals.erase(prev(vals.end()));
        acc -= f(id);
        w[id] /= 2;
        vals.insert({f(id) , id});
    }    
    sum[v].push_back(0);
}

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        scanf("%d %lld" , &N , &S);
        g = vector<vector<ii>> (N + 1);
        cnt = vector<int> (N + 1);
        c = vector<int> (N + 1);
        w = vector<ll> (N + 1);
        for(int i = 1; i < N; ++i){
            int u , v;
            scanf("%d %d %lld %d" , &u , &v , &w[i] , &c[i]);
            g[u].emplace_back(v , i);
            g[v].emplace_back(u , i);
        }
        DFS(1 , -1);
        for(int j : {1 , 2})solve(j);
        ID {
            for(int j : {1 , 2}){
                printf("only use %d \n" , j);
                for(ll i : sum[j]){
                    printf("%lld " , i);
                }
                printf("\n");
            }
        }
        int ans = INF;
        for(int i = 0; i < sum[1].size(); ++i){
            int l = 0 , r = sum[2].size() - 1 , j = -1;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(sum[1][i] + sum[2][mid] <= S){
                    j = mid;
                    r = mid - 1;
                }
                else{
                    l = mid + 1;
                }
            }
            if(~j)ans = min(ans , i + 2 * j);
        }
        printf("%d\n" , ans);
    }
}
