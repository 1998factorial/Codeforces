#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
ll X , Y;
int N , d = 0 , deg[maxn];
vector<int> g[maxn];

int DFS(int v , int p){
    int can = 2;
    for(int nv : g[v]){
        if(nv == p)continue;
        int c = DFS(nv , v);
        if(c && can > 0){
            ++d;
            --can;
        }
    }
    return can > 0;
}

int main(){
    scanf("%d %lld %lld" , &N , &X , &Y);
    for(int i = 1; i < N; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        ++deg[u]; 
        ++deg[v];
        g[v].push_back(u);
        g[u].push_back(v);
    }
    if(Y <= X){
        int ok = 1; 
        for(int i = 1; i <= N; ++i){
            if(deg[i] == N - 1)ok = 0;
        }
        if(ok) printf("%lld\n" , Y * (N - 1));
        else printf("%lld\n" , Y * (N - 2) + X);
    }
    else{
        DFS(1 , -1);
        //printf("d = %d\n" , d);
        printf("%lld\n" , Y * (N - 1 - d) + X * d);
    }
}
