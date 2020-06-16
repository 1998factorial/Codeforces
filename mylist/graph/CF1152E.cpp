/*
    Graph , Eular path , rating 2400

    Firstly, if b[i] > c[i] , we have no solution
    either a[p[i]] = b[i] , a[p[i + 1]] = c[i] or a[p[i]] = c[i] , a[p[i + 1]] = b[i].
    so at the end, all b's and c's should form a chain, like b[1]->c[1]->c[2]->b[2]->c[3]->b[3].
    and if we connect for each b[i] with c[i], and the euler path will be our answer.
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

int b[maxn] , c[maxn] , N , tot;



struct Indexer{
    unordered_map<int , int> mp;
    vector<int> num;

    int getID(int x){
        if(!mp.count(x)){
            mp[x] = num.size();
            num.push_back(x);
        }
        return mp[x];
    }

    int getNum(int x){
        return num[x];
    }

    int size(){
        return mp.size();
    }

};

struct Edge{
    int x , y;
    bool f;
    Edge(){}
    Edge(int x_ , int y_ , bool f_) : x(x_) , y(y_) , f(f_) {}
};

struct Graph{
    // index start with 0
    int n;
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> pos;
    list<int> path;

    void DFS(list<int> :: iterator it , int u){ // DFS (with euler path finding purpose)
        for(; pos[u] < g[u].size(); ++pos[u]){
            int id = g[u][pos[u]];
            if(edges[id].f){
                edges[id].f = 0;
                int v = edges[id].x + edges[id].y - u;
                DFS(path.insert(it , u) , v);
            }
        }
    }

    Graph(int n_) : n(n_) {
        g.assign(n , vector<int>());
    }

    void addEdge(int v , int u){ // add undirected edge
        g[v].push_back(edges.size());
        g[u].push_back(edges.size());
        edges.emplace_back(v , u , 0);
    }

    vector<int> eulerPath(){ // find euler path
        for(auto& e : edges){
            e.f = 1;
        }
        path.clear();
        pos.assign(n , 0);
        vector<int> odd;
        for(int u = 0; u < n; ++u){
            if(g[u].size() % 2 == 1)
                odd.push_back(u);
        }
        if(odd.empty()){
            odd.push_back(0);
            odd.push_back(0);
        }
        if(odd.size() > 2){
            return {};
        }
        DFS(path.begin() , odd[0]);
        path.insert(path.begin() , odd[1]);
        return vector<int>(path.begin() , path.end());
    }

};

int main(){
    Indexer I;
    scanf("%d" , &N);
    for(int i = 1; i < N; ++i)scanf("%d" , &b[i]);
    for(int i = 1; i < N; ++i)scanf("%d" , &c[i]);
    int notok = 0;
    for(int i = 1; i < N; ++i)if(b[i] > c[i])notok = 1;
    if(notok){
        printf("-1\n");
        return 0;
    }
    for(int i = 1; i < N; ++i){
        b[i] = I.getID(b[i]);
        c[i] = I.getID(c[i]);
    }
    int sz = I.size();
    Graph G(sz);
    for(int i = 1; i < N; ++i){
        G.addEdge(b[i] , c[i]);
    }
    vector<int> path = G.eulerPath();
    if(path.size() < N){
        printf("-1\n");
    }
    else{
        for(int i : path){
            printf("%d " , I.getNum(i));
        }
        printf("\n");
    }
}
