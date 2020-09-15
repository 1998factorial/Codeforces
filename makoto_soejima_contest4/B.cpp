#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int maxn = 1e5 + 10;
const int INF = 2e9 + 10;
int X[maxn] , Y[maxn] , N , tot = 0;
struct edge{
    int x , y , w;
    edge(){}
    edge(int x_ , int y_ , int w_) : x(x_) , y(y_) , w(w_) {}
    bool operator < (const edge& rhs) const {
        return w > rhs.w;
    }
};
int fa[maxn];

void init(){
    for(int i = 1; i <= N; ++i)fa[i] = i;
}

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main(){
    scanf("%d" , &N);
    vector<int> id;
    for(int i = 1; i <= N; ++i){
        scanf("%d %d" , &X[i] , &Y[i]);
        id.push_back(i);
    }
    vector<edge> edges;
    sort(id.begin() , id.end() , [&](int x , int y){
        return X[x] + Y[x] > X[y] + Y[y];
    });
    int head = id[0] , tail = id.back();
    for(int i : id){
        edges.emplace_back(head , i , -(X[i] + Y[i]) + (X[head] + Y[head]));
        edges.emplace_back(tail , i , -(X[tail] + Y[tail]) + (X[i] + Y[i]));
    }
    sort(id.begin() , id.end() , [&](int x , int y){
        return X[x] - Y[x] > X[y] - Y[y];
    });
    head = id[0] , tail = id.back();
    for(int i : id){
        edges.emplace_back(head , i , -(X[i] - Y[i]) + (X[head] - Y[head]));
        edges.emplace_back(tail , i , -(X[tail] - Y[tail]) + (X[i] - Y[i]));
    }
    sort(edges.begin() , edges.end());
    init();
    int ans = INF;
    for(auto& e : edges){
        int x = e.x , y = e.y , w = e.w;
        x = find(x); y = find(y);
        if(x != y){
            fa[x] = y;
            ans = min(ans , w);
        }
    }
    printf("%d\n" , ans);
}