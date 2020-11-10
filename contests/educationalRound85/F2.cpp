/*
    Dynamic programming
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 10;



const ll inf = 1e18;
int N , M;
int a[maxn] , b[maxn] , p[maxn] , lb[maxn];
ll DP[maxn] , ccost[maxn];

int main(){
    scanf("%d" , &N);
    for(int i = 0; i < N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int i = 0; i < N; ++i){
        scanf("%d" , &p[i]);
    }
    scanf("%d" , &M);
    for(int i = 0; i < M; ++i){
        scanf("%d" , &b[i]);
    }
    for(int i = 0; i < M; ++i){
        lb[b[i] + 1] = i + 1;
    }
    for(int i = 1; i <= N; ++i){
        lb[i] = max(lb[i] , lb[i - 1]);
    }
    for(int i = 1; i <= N; ++i){
        DP[i] = inf;
    }
    ll negs = 0;
    for(int i = 0; i < N; ++i){
        int id = lb[a[i]];
        if(p[i] > 0)
            ccost[id] += p[i];
        else
            negs += p[i];
        if(id < M && b[id] == a[i] && DP[id] != inf){
            DP[id + 1] = min(DP[id + 1] , DP[id] + ccost[id] - p[i]);
        }
    }
    if(DP[M] == inf){
        printf("NO\n");
    }
    else{
        printf("YES\n");
        printf("%lld\n" , DP[M] + ccost[M] + negs);
    }
}


/*
case 1

11
4 1 3 3 7 8 7 9 10 7 11
3 5 0 -2 5 3 6 7 8 2 4
3
3 7 10

3(4) + 5(1) + 3(8) + 7(9) + 4(11) - 2(3)

ans = 20
*/
