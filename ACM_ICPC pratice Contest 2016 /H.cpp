#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
const int inf = 1e9 + 10;
int N , Q;
vector<int> g[maxn];
vector<int> a;
int logs[maxn << 2];
int DP[maxn][22];
int tot;
int tin[maxn] , tout[maxn];
int sum[maxn << 2];
int height[maxn];

void add(int pos , int val){
    while(pos <= tot){
        sum[pos] += val;
        pos += pos & (-pos);
    }
}

int ask(int pos){
    int ret = 0;
    while(pos){
        ret += sum[pos];
        pos -= pos & (-pos);
    }
    return ret;
}

int better(int x , int y){
    return height[x] < height[y] ? x : y;
}

void DFS(int v , int p , int h){
    tin[v] = tot;
    DP[tot][0] = v;
    height[v] = h;
    ++tot;
    for(int u : g[v]){
        if(u != p){
            DFS(u , v , h + 1);
            DP[tot][0] = v;
            ++tot;
        }
    }
    tout[v] = tot;
}

void build(){
    for(int i = 2; i <= tot; ++i){
        logs[i] = logs[i / 2] + 1;
    }
    height[0] = inf;
    for(int j = 1; j <= logs[tot] + 1; ++j){
        for(int i = 1; i <= tot; ++i){
            int len = (1 << (j - 1));
            if(len + i <= tot){
                DP[i][j] = better(DP[i][j - 1] , DP[i + len][j - 1]);
            }
            else{
                DP[i][j] = DP[i][j - 1];
            }
        }
    }
}

int LCA(int x , int y){
    int l = min(tin[x] , tin[y]);
    int r = max(tout[x] , tout[y]);
    int len = r - l;
    return better(DP[l][logs[len]] , DP[r - (1 << logs[len])][logs[len]]);
}

int solve(){
    if(a.size() < 2)return 0;
    for(int i : a){
        //cout << "add 1 at " << tin[i] << endl;
        add(tin[i] , 1);
    }
    int nleaf = 0;
    for(int i : a){
        //printf("sum[0..%d] = %d , sum[0..%d] = %d\n" , tout[i] , ask(tout[i]) , tin[i] , ask(tin[i]));
        nleaf += (ask(tout[i]) - ask(tin[i])) == 0;
    }
    int root = 0;
    for(int i = 0; i < a.size(); ++i){
        if(height[a[i]] < height[a[root]]){
            root = i;
        }
    }
    rotate(a.begin() + root , a.begin() + root + 1, a.end());
    int other_lca = a[0];
    for(int i = 0; i < a.size() - 1; ++i){
        other_lca = LCA(other_lca , a[i]);
    }
    int lca = LCA(a.back() , other_lca);
    if(lca == a.back() && other_lca != lca)++nleaf;
    for(int i : a){
        add(tin[i] , -1);
    }
    return (int)ceil((double)nleaf / 2.0);
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i < N; ++i){
        int x , y;
        scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    tot = 1;
    DFS(1 , 1 , 0);
    build();
    scanf("%d" , &Q);
    for(int q = 1; q <= Q; ++q){
        int s; scanf("%d" , &s);
        a.clear();
        for(int i = 1; i <= s; ++i){
            int x; scanf("%d" , &x); a.push_back(x);
        }
        printf("%d\n" , solve());
    }
}
