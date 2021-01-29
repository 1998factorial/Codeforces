#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
vector<array<int , 2>> g[maxn];
// check if there is deg >= 3 vertice, if so,
// assign 0 ~ deg[v] - 1 to each of its edges
// this we can make sure mex is at most 2
// else, it is a linked list , just assign whatever
int ans[maxn] , N;
int main(){
    scanf("%d" , &N);
    for(int i = 1; i < N; ++i){
        ans[i] = -1;
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].push_back({v , i});
        g[v].push_back({u , i});
    }
    for(int i = 1; i <= N; ++i){
        if(g[i].size() >= 3){
            int cnt = 0;
            for(auto& e : g[i]){
                int v = e[0] , id = e[1];
                ans[id] = cnt;
                ++cnt;
            }
            for(int j = 1; j < N; ++j){
                if(~ans[j])continue;
                ans[j] = cnt;
                ++cnt;
            }
            for(int j = 1; j < N; ++j){
                printf("%d\n" , ans[j]);
            }
            exit(0);
        }
    }
    for(int i = 1; i < N; ++i){
        printf("%d\n" , i - 1);
    }
}