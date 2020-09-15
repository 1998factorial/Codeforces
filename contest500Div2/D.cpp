#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int fa[maxn * 2];
int N , M , Q;
int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int main(){
    scanf("%d %d %d" , &N , &M , &Q);
    for(int i = 1; i <= N + M; ++i)fa[i] = i;
    while(Q--){
        int x , y; 
        scanf("%d %d" , &x , &y);
        x = find(x);
        y = find(y + N);
        fa[x] = y;
    }
    set<int> vis;
    for(int i = 1; i <= N + M; ++i)vis.insert(find(fa[i]));
    printf("%d\n" , (int)vis.size() - 1);
}