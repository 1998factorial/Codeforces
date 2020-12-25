#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int p[maxn] , N , A , B , fa[maxn];

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x , int y){
    x = find(x);
    y = find(y);
    fa[x] = y;
}

int main(){
    map<int , int> mp;
    scanf("%d %d %d" , &N , &A , &B);
    int a = N + 1 , b = N + 2;
    for(int i = 1; i <= N; ++i)scanf("%d" , &p[i]) , mp[p[i]] = i;
    for(int i = 1; i <= N + 2; ++i)fa[i] = i;
    for(int i = 1; i <= N; ++i){
        if(mp.find(A - p[i]) != mp.end())merge(mp[A - p[i]] , i);
        else merge(i , a);
        if(mp.find(B - p[i]) != mp.end())merge(mp[B - p[i]] , i);
        else merge(i , b);
    }
    a = find(a);
    b = find(b);
    if(a == b){
        printf("NO\n");
    }
    else{
        printf("YES\n");
        for(int i = 1; i <= N; ++i){
            if(find(i) == a)printf("1 ");
            else printf("0 ");
        }
        printf("\n");
    }
}