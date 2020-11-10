/*
    TLE
*/
#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
#define FOR(i , a , b) for(int i = a; i <= b; ++i)
using namespace std;
typedef long long ll;
inline int gcd(int a , int b){
    return a == 0 ? b : gcd(b % a , a);
}
const int maxn = 2e5 + 10;
vector<int> g[maxn]; // old graph
vector<int> ct[maxn]; // centroid tree
bool dead[maxn]; // deleted ?
int val[maxn]; // value at vertex v
int sz[maxn]; // size of subtree rooted at v
int p[maxn]; // parent in old graph
int gcds[maxn];
int len;
int N , root;
ll ans[maxn];
 
void getsz(int v , int fa){
    p[v] = fa;
    sz[v] = 1;
    for(int u : g[v]){
        if(u != fa){
            getsz(u , v);
            sz[v] += sz[u];
        }
    }
}
/*
void DFS(int v , int fa , int gcd_val){
    gcd_val = gcd(gcd_val , val[v]);
    gcds[++len] = gcd_val;
    for(int u : g[v]){
        if(u != fa && !dead[u]){
            DFS(u , v , gcd_val);
        }
    }
}
 
void solve(int v , int fa , int mul , int flag){
    len = 0;
    DFS(v , fa , mul);
    sort(gcds + 1 , gcds + 1 + len);
    vector<int> t1 , t2;
    for(int x = 1; x <= len; ++x){
        int i = gcds[x];
        if(t1.empty() || t1.back() != i)t1.push_back(i) , t2.push_back(1);
        else ++t2.back();
    }
    int nn = t1.size();
    for(int i = 0; i < nn; ++i){
        if(t2[i] > 1){
            ans[t1[i]] += 1ll * flag * t2[i] * (t2[i] - 1) / 2;
        }
        for(int j = i + 1; j < nn; ++j){
            ans[gcd(t1[i] , t1[j])] += 1ll * flag * t2[i] * t2[j];
        }
    }
}*/

void DFS(int v , int fa , int gcd_val , vector<int>& gcds){
    gcd_val = gcd(gcd_val , val[v]);
    gcds.push_back(gcd_val);
    for(int u : g[v]){
        if(u != fa && !dead[u]){
            DFS(u , v , gcd_val , gcds);
        }
    }
}

void cal(int v , int gcd_val , int flag){
    vector<int> gcds;
    DFS(v , 0 , gcd_val , gcds);
    sort(gcds.begin() , gcds.end());
    vector<int> t1 , t2;
    for(int i : gcds){
        if(t1.empty() || t1.back() != i){
            t1.push_back(i); t2.push_back(1);
        }
        else ++t2.back();
    }
    int n = t1.size();
    for(int i = 0; i < n; ++i){
        if(t2[i] > 1){
            ans[t1[i]] += 1ll * flag * t2[i] * (t2[i] - 1) / 2;
        }
        for(int j = i + 1; j < n; ++j){
            ans[gcd(t1[i] , t1[j])] += 1ll * flag * t2[i] * t2[j];
        }
    }
}

int decompose(int vv , int size , int fa){
    int v = vv;
    for(;;){
        int nv = -1;
        for(int u : g[v]){
            if(dead[u] || p[v] == u)continue;
            if(sz[u] > size / 2)nv = u;
        }
        if(size - sz[v] > size / 2 && p[v] != -1 && !dead[p[v]])nv = p[v];
        if(nv != -1)v = nv;
        else break; 
    }
    dead[v] = 1;
    cal(v , val[v] , 1);
    for(int u : g[v]){
        if(!dead[u]){
            cal(u , val[v] , -1);
            int nsize = sz[u];
            if(u == p[v])nsize = size - sz[u];
            int nc = decompose(u , nsize , v);
            ct[v].push_back(nc);
        }
    }
    return v;
}
 
void show_centroid_tree(int v){
    for(int u : ct[v]){
        printf("%d -- %d\n" , v , u);
        show_centroid_tree(u);
    }
}
 
int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &val[i]);
        ++ans[val[i]];
        p[i] = -1;
    }
    for(int i = 1; i < N; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    getsz(1 , 1);
    root = decompose(1 , N , -1);
    ID {
        printf("centroid = %d\n" , root);
        show_centroid_tree(root);
    }
    for(int i = 1; i <= 200000; ++i){
        if(ans[i])printf("%d %lld\n" , i , ans[i]);
    }
}