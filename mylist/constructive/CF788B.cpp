/*
    Constructive , rating 2100 , Eular path
    M - 2 edges used twice , 2 edges used once.
    duplicate all edges , if all M edges used twice , it is just Eular path
    now , we need to choose which 2 edges to delete. And check after deleting 
    them , we will have an Eular path.
    Consider 4 cases:
    2 self loop , ok
    1 self loop , 1 normal edge , ok
    2 normal edge , no common point , not ok
    2 normal edge , with common point , ok

    a lot of cases regarding connectivity needs to be checked
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 10;
int N , M;
int loop[maxn];
int fa[maxn];
int cnt;
int sz[maxn];
ll deg[maxn];
ll nloop;

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int merge(int x , int y){
    x = find(x); y = find(y);
    if(x != y){
        fa[x] = y;
        return 1;
    }
    return 0;
}

int main(){
    scanf("%d %d" , &N , &M);
    nloop = 0;
    cnt = N; // # connected component
    for(int i = 1; i <= N; ++i)fa[i] = i;
    for(int i = 1; i <= M; ++i){
        int x , y; scanf("%d %d" , &x ,&y);
        if(x != y){
            cnt -= merge(x , y);
            ++deg[x]; ++deg[y];
        }
        else{
            ++nloop;
            ++loop[x];
        }
    }
    ll ret = 0;
    if(nloop)ret += nloop * (nloop - 1) / 2; // case 1
    if(nloop)ret += nloop * (M - nloop); // case 2
    for(int i = 1; i <= N; ++i){ // case 3
        if(deg[i] > 1){
            ret += deg[i] * (deg[i] - 1) / 2;
        }
    }
    for(int i = 1; i <= N; ++i){
        fa[i] = find(fa[i]);
        ++sz[fa[i]];
    }
    if(cnt == 1)printf("%lld\n" , ret);
    else{
        bool ok = 1;
        int nsz = 0;
        for(int i = 1; i <= N; ++i){
            nsz += sz[i] > 1;
        }
        if(nsz > 1)ok = 0; // disconnected
        for(int i = 1; i <= N; ++i){
            if(sz[fa[i]] == 1){
                if(deg[i] || loop[i])ok = 0; // self loop on CC with 1 vertex , which is not good
            }
        }
        if(ok)printf("%lld\n" , ret);
        else printf("0\n");
    }
}