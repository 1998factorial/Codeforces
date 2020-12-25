#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int A , B , N , p[maxn] , dfn[maxn * 2] , low[maxn * 2] , mark[maxn * 2] , tot = 0 , scc = 0;
vector<int> g[maxn * 2];
vector<int> st;
bool instack[maxn * 2];

void tarjan(int v){
    low[v] = dfn[v] = ++tot;
    instack[v] = 1;
    st.push_back(v);
    for(int u : g[v]){
        if(!dfn[u]){
            tarjan(u);
            low[v] = min(low[v] , low[u]);
        }
        else if(instack[u]){
            low[v] = min(low[v] , dfn[u]);
        }
    }
    if(low[v] == dfn[v]){
        ++scc;
        for(;;){
            int u = st.back();
            st.pop_back();
            instack[u] = 0;
            mark[u] = scc;
            if(u == v)break;
        }
    }
}

void solve(){
    for(int i = 0; i < 2 * N; ++i){
        if(!dfn[i]){
            tarjan(i);
        }
    }
}

int main(){
    map<int , int> mp;
    scanf("%d %d %d" , &N , &A , &B);
    for(int i = 0; i < N; ++i){
        scanf("%d" , &p[i]);
        mp[p[i]] = i;
    }
    for(int j = 0; j < N; ++j){
        int i = p[j];
        if(mp.find(A - i) == mp.end() && mp.find(B - i) == mp.end()){
            printf("NO\n");
            return 0;
        }
        if(mp.find(A - i) != mp.end()){
            g[2 * j].push_back(2 * mp[A - i]);
            g[2 * j + 1].push_back(2 * mp[A - i] + 1);
        }
        else g[2 * j].push_back(2 * j + 1);
        if(mp.find(B - i) != mp.end()){
            g[2 * j + 1].push_back(2 * mp[B - i] + 1);
            g[2 * j].push_back(2 * mp[B - i]);
        }
        else{
            g[2 * j + 1].push_back(2 * j);
        }
    }
    solve();
    for(int i = 0; i < 2 * N; i += 2){
        if(mark[i] == mark[i + 1]){
            printf("NO\n");
            return 0;
        }
    }   
    printf("YES\n");
    for(int i = 0; i < 2 * N; i += 2){
        if(mark[i] < mark[i + 1]){
            printf("0 ");
        }
        else printf("1 ");
    }
    printf("\n");
}   