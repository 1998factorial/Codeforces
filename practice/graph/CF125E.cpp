/*
    Kruskal , special technique [玄学] , rating 2400

    this technique exists, thats all I know so far ....
    each edges incident to 1 will be assigned with an additional weight "mid"
    and we can binary search mid, in [-1e5 , 1e5] , when using Kruskal to find MST
    and deg[1] is exactly K, we are done.

    intuition: when mid is too large, deg[1] < K , when mid is too small, deg[1] > K
    So, we need to find a sweet spot where deg[1] is exactly K
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5010;
const int maxm = 1e5 + 10;
const double eps = 1e-5;
int N , M , K;
int x[maxm] , y[maxm] , w[maxm] , p[maxm] , id[maxn];
double mid;
int cnt , tot;
int ans[maxm];

int find(int i){
    return id[i] == i ? i : id[i] = find(id[i]);
}

void solve(int flag){
    cnt = tot = 0;
    for(int i = 1; i <= N; ++i)id[i] = i;
    sort(p + 1 , p + 1 + M , [&](int a , int b){
        return mid * (x[a] == 1) + w[a] < mid * (x[b] == 1) + w[b];
    });
    for(int i = 1; i <= M; ++i){
        int j = p[i];
        int u = find(x[j]) , v = find(y[j]);
        if(u != v && (flag || cnt + (x[j] == 1) <= K)){
            id[u] = v;
            ans[tot++] = j;
            cnt += x[j] == 1;
        }
    }
}

int main(){
    int deg = 0;
    scanf("%d %d %d" , &N , &M , &K);
    for(int i = 1; i <= M; ++i){
        scanf("%d %d %d" , &x[i] , &y[i] , &w[i]);
        if(x[i] > y[i])swap(x[i] , y[i]);
        if(x[i] == 1)++deg;
        p[i] = i;
    }
    if(deg < K || (K == 0 && N > 1)){ // impossible to have a spanning tree where 1 has exactly degree = K
        printf("-1\n");
        return 0;
    }
    double l = -1e5 , r = 1e5;
    cnt = 0;
    while(r - l > eps && cnt != K){ // binary search the weight attached to vertex 1
        mid = (l + r) / 2;
        solve(1);
        if(cnt < K){
            r = mid;
        }
        else{
            l = mid;
        }
    }
    if(cnt != K)mid = (l + r) / 2;
    solve(0);
    printf("%d\n" , tot);
    for(int i = 0; i < tot; ++i){
        printf("%d " , ans[i]);
    }
    printf("\n");
}
