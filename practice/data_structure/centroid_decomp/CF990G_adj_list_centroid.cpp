#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
vector<int> g[maxn];
int N;
int max_size[maxn];
int val[maxn];
int sz[maxn];
int root;
ll ans[maxn];
bool dead[maxn];
inline int gcd(int a , int b){
    return a == 0 ? b : gcd(b % a , a);
}

void get_centroid(int v , int fa , int total_number){
    sz[v] = 1;
    max_size[v] = 0;
    for(int u : g[v]){
        if(!dead[u] && u != fa){
            get_centroid(u , v , total_number);
            sz[v] += sz[u];
            max_size[v] = max(max_size[v] , sz[u]);
        }
    }
    max_size[v] = max(max_size[v] , total_number - sz[v]);
    if(max_size[root] > max_size[v])root = v;
}

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

void solve(int v){
    //printf("centroid = %d\n" , root);
    dead[v] = 1;
    cal(v , val[v] , 1);
    for(int u : g[v]){
        if(!dead[u]){
            cal(u , val[v] , -1);
            root = 0;
            max_size[0] = sz[u];
            get_centroid(u , 0 , sz[u]); // solve on the subtree rooted at u
            solve(root);
        }
    }
}

int main(){
    int i , x , y;
    scanf("%d" , &N);
    for(i = 1; i <= N; ++i){
        scanf("%d" , &val[i]);
        ++ans[val[i]];
    }
    for(i = 1; i < N; ++i){
        scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    max_size[0] = N + 1;
    root = 0;
    get_centroid(1 , 0 , N);
    solve(root);
    for(i = 1; i <= 200000; ++i){
        if(ans[i])printf("%d %lld\n" , i , ans[i]);
    }
}