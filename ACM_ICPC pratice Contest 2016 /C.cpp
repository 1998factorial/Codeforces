#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;
const int maxn = 2e5 + 10;

int N , M;
vector<int> g[maxn];
vector<int> diff[maxn];
int vis[maxn];
int cnt[2];
int DP[maxn] , a[maxn] , pre[maxn];
int zero_larger[maxn];
int ncomponent = 0;
vector<int> roots;
bool connected[maxn];

void DFS(int v , int c){
    vis[v] = c;
    ++cnt[c];
    for(int u : g[v]){
        if(vis[u] == -1)
            DFS(u , 1 - c);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    for(int i = 1; i <= M; ++i){
        int x , y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    memset(vis , -1 , sizeof(vis));
    int tot = 0;
    for(int i = 1; i <= N; ++i){
        if(vis[i] == -1){
            ++ncomponent;
            cnt[0] = cnt[1] = 0;
            DFS(i , 0);
            roots.push_back(i);
            tot += abs(cnt[0] - cnt[1]);
            zero_larger[i] = cnt[0] >= cnt[1];
            ++a[abs(cnt[0] - cnt[1])];
            diff[abs(cnt[0] - cnt[1])].push_back(i);
        }
    }
    for(int i = 1; i <= tot; ++i){
        DP[i] = N + 1;
    }
    for(int i = 1; i <= tot; ++i){
        if(a[i] > 0){ // this diff exist , try to feed in some positve numbers of this diff
            for(int j = 0; j + i <= tot; ++j){
                if(DP[j] < N + 1 && DP[j + i] > DP[j] + 1){ // j can be obtain by some |x - y|
                    DP[j + i] = DP[j] + 1;
                    pre[j + i] = j;
                }
            }
            for(int j = 0; j <= tot; ++j){
                if(DP[j] > a[i]){
                    DP[j] = N + 1;
                    pre[j] = 0;
                }
                else{
                    DP[j] = 0;
                }
            }
        }
    }
    int v = 0;
    int ans = tot;
    for(int i = 0; i <= tot; ++i){
        if(DP[i] < N + 1){
            if(ans >= abs(tot - 2 * i)){
                ans = abs(tot - 2 * i);
                v = i;
            }
        }
    }
    memset(vis , -1 , sizeof(vis));
    while(v){
        int d = v - pre[v];
        int nd = diff[d].back();
        diff[d].pop_back();
        DFS(nd , zero_larger[nd]);
        v = pre[v];
    }
    for(int i = 1; i <= N; ++i){
        if(vis[i] == -1){
            DFS(i , 1 - zero_larger[i]);
        }
    }
    cout << ans << " " << ncomponent - 1 << endl;
    if(ncomponent > 1){
        unordered_set<int> blacks , whites;
        for(int i : roots){
            if(vis[i] == 0)whites.insert(i);
            else blacks.insert(i);
        }
        if(whites.size() == 0){
            for(int i : blacks){
                if(g[i].size()){
                    blacks.erase(i);
                    whites.insert(g[i][0]);
                    break;
                }
            }
        }
        else if(blacks.size() == 0){
            for(int i : whites){
                if(g[i].size()){
                    whites.erase(i);
                    blacks.insert(g[i][0]);
                    break;
                }
            }
        }
        for(int i : whites){
            cout << *blacks.begin() << " " << i << endl;
        }
        blacks.erase(blacks.begin());
        for(int i : blacks){
            cout << i << " " << *whites.begin() << endl;
        }
    }
}
