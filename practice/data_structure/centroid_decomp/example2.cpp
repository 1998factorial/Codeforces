/*
    how many paths go through centroid of T which has length k ?
*/

#include <bits/stdc++.h>
#define x first
#define y second
#define mk make_pair
#define INF 1e9 + 10
#define ID if(0)
#define ii pair<int , int>
#define ll long long
#define maxn 5e5 + 10
using namespace std;


ll delta , k , ans;
struct CentroidDecomp{
    vector<vector<int>> &g , centroid_tree;
    vector<int> size , p , cnt;
    vector<bool> tocheck;
    int root;
    int N;
    CentroidDecomp(vector<vector<int>>& tree) : g(tree){
        N = tree.size();
        tocheck.assign(N , 1);
        centroid_tree.assign(N , vector<int>());
        p.assign(N , -1);
        cnt.assign(maxn , 0);
        size.assign(N , 0);
        getsz(0);
        root = decompose(0 , N , -1);
    }

    void getsz(int v){
        size[v] = 1;
        for(int u : g[v]){
            if(u != p[v]){
                p[u] = v;
                getsz(u);
                size[v] += size[u];
            }
        }
        ID printf("size[%d] = %d\n" , v + 1 , size[v]);
    }

    void DFS2(int v , int p , int val , bool f){
        if(f) ++cnt[val];
        else --cnt[val];
        for(int u : g[v]){
            if(tocheck[u] && u != p){
                DFS2(u , v , val + 1 , f);
            }
        }
    }

    void solve(int v , int p , int val){
        if(val > k) return;
        delta += cnt[k - val];
        for(int u : g[v]){
            if(tocheck[u] && u != p){
                solve(u , v , val + 1);
            }
        }
    }

    // finiding centroid and get answer for this centroid
    int decompose(int u_ , int sz , int fa){
        int u = u_;
        for(;;){
            int nu = -1;
            for(int v : g[u]){
                if(!tocheck[v] || v == p[u])continue;
                if(size[v] > sz / 2)nu = v;
            }
            if(sz - size[u] > sz / 2 && p[u] != -1 && tocheck[p[u]])nu = p[u];
            if(nu != -1)u = nu;
            else break;
        }
        for(int v = p[u];  v != -1 && tocheck[v]; v = p[v]){
            size[v] -= size[u];
        }
        delta = 0;
        DFS2(u , fa , 0 , 1);
        delta += cnt[k];
        for(int x : g[u]){
            if(tocheck[x]){
                DFS2(x , u , 1 , 0);
                solve(x , u , 1);
                DFS2(x , u , 1 , 1);
            }
        }
        ans += delta / 2;
        DFS2(u , fa , 0 , 0);
        tocheck[u] = 0;
        for(int v : g[u]){
            if(tocheck[v]){
                int sz2 = size[v];
                if(p[u] == v)sz2 = sz - size[u];
                centroid_tree[u].push_back(decompose(v , sz2 , u));
            }
        }
        return u;
    }

    void show_centroid_tree(int v){
        for(int u : centroid_tree[v]){
            cout << v + 1 << " -- " << u + 1 << endl;
            show_centroid_tree(u);
        }
    }

};

int main(){
    int n; scanf("%d %lld" , &n , &k);
    vector<vector<int>> g(n);
    for(int i = 1; i < n; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        --x , --y;
        g[x].push_back(y); g[y].push_back(x);
    }
    struct CentroidDecomp C(g);
    //cout << "centroid = " << C.root + 1 << endl;
    //C.show_centroid_tree(C.root);
    //cout << "#(path lenght = k) = " << ans << endl;
    cout << ans << endl;
}