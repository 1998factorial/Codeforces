#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;
const int maxn = 5e5 + 10;
int N , M;

struct edge{
    int v , u , l , r;
    edge(){}
    edge(int v_  , int u_ , int l_ , int r_ ) : v(v_) , u(u_) , l(l_) , r(r_) {}
    bool operator > (const edge& rhs) const {
        return l > rhs.l;
    }
};

priority_queue<edge , vector<edge> , greater<edge>> q;
vector<edge> adj[maxn][2]; // what edges are attached to (v , time & 1) 
int last[maxn][2]; // latest time when we get to (v , time & 1)

void relax(int v , int start , int end){
    last[v][start & 1] = max(last[v][start & 1] , end);
    for(auto& e : adj[v][start & 1]){
        edge t = e;
        t.l = start; // earlist time that we can use v as a starting point
        q.push(t);
    }
    adj[v][start & 1].clear();
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        int v , u , l , r;
        scanf("%d %d %d %d" , &v , &u , &l , &r);
        --r;
        q.push(edge(v , u , l , ((l & 1) == (r & 1) ? r : r - 1)));
        q.push(edge(u , v , l , ((l & 1) == (r & 1) ? r : r - 1)));
        q.push(edge(v , u , l + 1 , (((l + 1) & 1) == (r & 1) ? r : r - 1)));
        q.push(edge(u , v , l + 1 , (((l + 1) & 1) == (r & 1) ? r : r - 1)));
    }
    if(N == 1){
        printf("0\n");
        return 0;
    }
    for(int i = 1; i <= N; ++i)for(int j = 0; j < 2; ++j)last[i][j] = -1;
    last[1][0] = 0;
    while(!q.empty()){
        edge e = q.top();
        q.pop();
        if(e.l <= e.r){ // means edge e can be used for "loop" operation
            if(last[e.v][e.l & 1] >= e.l){
                if(e.u == N){
                    printf("%d\n" , e.l + 1);
                    return 0;
                }   
                // means we can use this edge
                relax(e.u , e.l + 1 , e.r + 1);
            }
            else{
                adj[e.v][e.l & 1].push_back(e);
            }
        }
    }
    printf("-1\n");
}