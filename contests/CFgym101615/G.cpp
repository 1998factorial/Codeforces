#include <bits/stdc++.h>
using namespace std;

// break employees into intervals 
// check if given intervals can go from s to t
// # intervals <= 10000
// for each interval, run DFS , O(M * (N + M)) is ok

vector<array<int , 3>> g[1005];
int N , M , K , s , t;
bool vis[1005];

void DFS(int v , int val){
    vis[v] = 1;
    for(auto& e : g[v]){
        int nv = e[0] , l = e[1] , r = e[2];
        if(!vis[nv] && val >= l && val <= r){
            DFS(nv , val);
        }
    }
}

int main(){
    scanf("%d %d %d" , &N , &M , &K);
    scanf("%d %d" , &s , &t);
    vector<int> tmp;
    for(int i = 1; i <= M; ++i){
        int u , v , a , b;
        scanf("%d %d %d %d" , &u , &v , &a , &b);
        g[u].push_back({v , a , b});
        tmp.push_back(a - 1);
        tmp.push_back(b);
    }  
    sort(tmp.begin() , tmp.end());
    int ret = 0;
    for(int i = 1; i < tmp.size(); ++i){
        if(tmp[i] != tmp[i - 1]){
            for(int j = 1; j <= N; ++j)vis[j] = 0;
            DFS(s , tmp[i]);
            if(vis[t])ret += tmp[i] - tmp[i - 1];
        }
    }
    printf("%d\n" , ret);
}