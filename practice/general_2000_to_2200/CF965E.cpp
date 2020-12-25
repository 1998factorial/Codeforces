#include <bits/stdc++.h>
using namespace std;

// build a trie first, move each point towards root, 
// stop right before there exist points that meet at some vertex

const int maxn = 1e5 + 10;
int nex[maxn][26] , total = 1 , depth[maxn];
char s[maxn];
multiset<int> ds[maxn * 26];

void add(){
    int cur = 1;
    int sz = strlen(s + 1);
    for(int i = 1; i <= sz; ++i){
        if(!nex[cur][s[i] - 'a']){
            nex[cur][s[i] - 'a'] = ++total;
            depth[total] = depth[cur] + 1;
        }
        cur = nex[cur][s[i] - 'a'];
    }
    ds[cur].insert(depth[cur]);
}

void DFS(int v){
    int isempty = ds[v].empty();
    for(int i = 0; i < 26; ++i){
        int nv = nex[v][i];
        if(!nv)continue;
        DFS(nv);
        for(int j : ds[nv]){
            ds[v].insert(j);
        }
        ds[nv].clear();
    }
    if(isempty && v != 1){
        auto it = ds[v].rbegin();
        ds[v].erase(ds[v].find(*it));
        ds[v].insert(depth[v]);
    }
}

int main(){
    int N;
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%s" , (s + 1));
        add();
    }
    int ret = 0;
    DFS(1);
    for(int x : ds[1]){
        ret += x;
    }
    printf("%d\n" , ret);
}