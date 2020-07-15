#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 10;
int N , A , B;
vector<int> level[maxn];
int dfn[maxn];
int R[maxn];
int tot;
vector<int> tree[maxn];
double cost[maxn][3];

void init(){
    for(int i = 0; i < maxn; ++i){
        level[i].clear();
        dfn[i] = 0;
        tree[i].clear();
    }
}

void DFS1(int v , int d){
    dfn[v] = ++tot;
    level[d].push_back(v);
    for(int u : tree[v]){
        DFS1(u , d + 1);
    }
    R[v] = tot;
}

void get(int step , int f){
    for(int i = 1; i <= N; ++i){
       cost[i][f] = 1;
    }
    for(int i = N; i >= 0; --i){
        if(i + step >= N)continue;
        if(level[i].empty())continue;
        if(level[i + step].empty()){ // base
            continue;
        }
        // i -> i + step
        for(int j = 0 , k = 0; j < level[i].size(); ++j){
            int v = level[i][j];
            for(; k < level[i + step].size(); ++k){
                int u = level[i + step][k];
                if(dfn[u] < dfn[v] || dfn[u] > R[v])break;
                cost[v][f] += cost[u][f];
            }
        }
    }
}

double solve(){
    init();
    scanf("%d %d %d" , &N , &A , &B);
    for(int i = 2; i <= N; ++i){
        int x; scanf("%d" , &x);
        tree[x].push_back(i);
    }
    tot = 0;
    DFS1(1 , 0);
    get(A , 0);
    get(B , 1);
    double ret = 0;
    for(int i = 1; i <= N; ++i){
        ret += cost[i][0] * N + cost[i][1] * N - cost[i][0] * cost[i][1];
    }
    return ret / ((double)N * N);
}

int main(){
    int T; scanf("%d" , &T);
    for(int t = 1; t <= T; ++t){
        printf("Case #%d: %lf\n" , t , solve());
    }
}
