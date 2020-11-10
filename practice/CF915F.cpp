#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const int maxn = 1e6 + 10;

vector<int> g[maxn];
vector<int> heap[maxn][2]; // 0->min , 1->max
int id[maxn][2];
int val[maxn];
ll sz[maxn][2];
ll DP[maxn][2];
int N;
ii p[maxn];

void init(){
    for(int i = 1; i <= N; ++i){
        id[i][0] = id[i][1] = i;
    }
}

int find(int x , int f){
    return id[x][f] == x ? x : id[x][f] = find(id[x][f] , f);
}

void DFS(int v , int p , int f){
    sz[v][f] = 1;
    DP[v][f] = 1;
    for(int u : heap[v][f]){
        if(p != u){
            DFS(u , v , f);
            DP[v][f] += sz[v][f] * sz[u][f];
            sz[v][f] += sz[u][f];
        }
    }
}

ll solve(){
    init();
    sort(p + 1 , p + 1 + N);
    // build min heap
    for(int i = N; i >= 1; --i){
        int v = p[i].second;
        for(int j : g[v]){
            if(val[j] > val[v] || (val[j] == val[v] && j > v)){
                int x = find(j , 0);
                if(x != v){
                    id[x][0] = v;
                    heap[v][0].push_back(x);
                }
            }
        }
    }
    // build max heap
    for(int i = 1; i <= N; ++i){
        int v = p[i].second;
        for(int j : g[v]){
            if(val[j] < val[v] || (val[v] == val[j] && j < v)){
                int x = find(j , 1);
                if(x != v){
                    id[x][1] = v;
                    heap[v][1].push_back(x);
                }
            }
        }
    }
    // traverse minHeap
    DFS(p[1].second , -1 , 0);
    // traverse maxHeap
    DFS(p[N].second , -1 , 1);
    ll ret = 0;
    for(int v = 1; v <= N; ++v){
        ret += (DP[v][1] - DP[v][0]) * val[v];
    }
    return ret;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &val[i]);
        p[i] = make_pair(val[i] , i);
    }
    for(int i = 1; i < N; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    printf("%lld\n" , solve());
}
