#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int N , M , K , K2;
vector<int> g[maxn];
int dep[maxn] , fa[maxn] , vis[maxn];

void DFS(int v , int p , int d){
    vis[v] = 1;
    dep[v] = d;
    for(int nv : g[v]){
        if(vis[nv] && dep[v] - dep[nv] < K && dep[v] - dep[nv] > 1){
            vector<int> ans;
            int x = v;
            while(x != nv){
                ans.push_back(x);
                x = fa[x];
            }
            ans.push_back(nv);
            cout << 2 << endl;
            cout << (int)ans.size() << endl;
            for(int i : ans)cout << i << " ";
            cout << endl;
            exit(0);
        }
        else if(!vis[nv]){
            fa[nv] = v;
            DFS(nv , v , d + 1);
        }
    }
}

void DFS2(int v , int p , int d){
    //cout << "at " <<v<<endl;
    vis[v] = 1;
    dep[v] = d;
    for(int nv : g[v]){
        if(vis[nv] && dep[v] - dep[nv] > 1){
            vector<int> ans;
            int x = v;
            while(x != nv){
                ans.push_back(x);
                x = fa[x];
            }
            ans.push_back(nv);
            vector<int> e , o;
            for(int i = 0; i < ans.size(); ++i){
                if(i & 1)o.push_back(ans[i]);
                else e.push_back(ans[i]);
            }
            if(e.size() < o.size())swap(e , o);
            for(int i = 0; i < e.size() && K2; ++i){
                cout << e[i] << " ";
                --K2;
            }
            exit(0);
        }
        else if(!vis[nv]){
            fa[nv] = v;
            DFS2(nv , v , d + 1);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> K;
    for(int i = 1; i <= M; ++i){
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // try to solve for task 2 , simple cycle of length at most K
    DFS(1 , 1 , 1);
    // now we try to solve for task 1
    memset(dep , 0 , sizeof(dep));
    memset(fa , 0 , sizeof(fa));
    memset(vis , 0 , sizeof(vis));
    cout << 1 << endl;
    K2 = K / 2 + (K % 2 == 1);
    if(M > N - 1){
        //cout<<"here\n";
        // not a tree
        DFS2(1 , 1 , 1);
    }
    else{
        // a tree
        vector<int> col(N + 1 , 0) , cnt(2 , 0);
        queue<array<int , 2>> q;
        q.push({1 , 0});
        while(!q.empty()){
            auto cur = q.front();
            int v = cur[0] , c = cur[1];
            q.pop();
            if(vis[v])continue;
            vis[v] = 1;
            col[v] = c;
            ++cnt[c];
            for(int nv : g[v]){
                if(!vis[nv]){
                    q.push({nv , c ^ 1});
                }
            }
        }
        int c = (cnt[0] > cnt[1]) ? 0 : 1;
        vector<int> ans;
        for(int i = 1; i <= N && K2; ++i){
            if(col[i] == c){
                ans.push_back(i);
                --K2;
            }
        }
        for(int i : ans)cout << i << " ";
        cout << endl;
    }
}