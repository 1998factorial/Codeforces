#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4505;
const int base = 4505;
const ll MOD = 1e9 + 7;
ll power[maxn] , hashv[maxn];
vector<array<int , 2>> g[maxn];
int N , M , fa[maxn] , cpid[maxn] , dfn[maxn] , low[maxn] , cnt , ncp;
bool instack[maxn];
vector<int> st;

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x , int y){
    x = find(x);
    y = find(y);
    if(x != y){
        fa[x] = y;
    }
}

void init(){
    ncp = 0;
    cnt = 0;
    for(int i = 1; i <= N; ++i){
        dfn[i] = 0 , low[i] = 0 , cpid[i] = 0;
    }
}

void tarjan(int v , int p , int ban_edge){
    dfn[v] = ++cnt;
    low[v] = cnt;
    st.push_back(v);
    instack[v] = 1;
    for(auto& e : g[v]){
        int nv = e[0] , eid = e[1];
        if(nv == p)continue;
        if(eid == ban_edge)continue;
        if(!dfn[nv]){
            tarjan(nv , v , ban_edge);
            low[v] = min(low[v] , low[nv]);
        }
        else if(instack[nv]){
            low[v] = min(low[v] , dfn[nv]);
        }
    }
    if(low[v] == dfn[v]){
        ++ncp;
        while(st.back() != v){
            int c = st.back();
            st.pop_back();
            cpid[c] = ncp;
        }
        cpid[st.back()] = ncp;
        st.pop_back();
    }
}

int main(){
    int ans = 0;
    scanf("%d %d" , &N , &M);
    power[0] = 1;
    for(int i = 1; i < maxn; ++i)power[i] = power[i - 1] * base % MOD;
    for(int i = 1; i <= N; ++i)fa[i] = i;
    for(int i = 0; i < M; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].push_back({v , i});
        g[v].push_back({u , i});
        merge(u , v);
    }
    // flow >= 1 if 2 nodes in same connected component
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            if(find(i) == find(j)){
                ++ans;
            }
        }
    }
    init();
    for(int i = 1; i <= N; ++i){
        if(!dfn[i]){
            tarjan(i , i , -1);
        }
    }
    // flow >= 2 if 2 nodes in same biconnected component
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            if(cpid[i] == cpid[j]){
                ++ans;
            }
        }
    }
    // flow >= 3 if 2 nodes are in the same biconnected component when remove any 
    // edge
    for(int j = 0; j < M; ++j){
        init();
        for(int i = 1; i <= N; ++i){
            if(!dfn[i]){
                tarjan(i , i , j);
            }
        }
        for(int i = 1; i <= N; ++i){
            hashv[i] += power[j] * cpid[i] % MOD;
            hashv[i] %= MOD;
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            if(hashv[i] == hashv[j]){
                ++ans;
            }
        }
    }
    printf("%d\n" , ans);
}