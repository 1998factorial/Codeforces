#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int maxn = 1010;
const int INF = 1e9;
vector<int> g[maxn * 2][2];
int cost[maxn][maxn][2] , L[maxn * 2][2] , R[maxn * 2][2] , DP[maxn] , sz[maxn * 2][2];
int N , A , B;

void DFS(int v , int f){
    sz[v][f] = v != 1;
    for(int u : g[v][f]){
        DFS(u , f);
        sz[v][f] += sz[u][f];
        L[v][f] = min(L[v][f] , L[u][f]);
        R[v][f] = max(R[v][f] , R[u][f]);
    }
    cost[L[v][f]][R[v][f]][f] = max(cost[L[v][f]][R[v][f]][f] , sz[v][f]);
    ID printf("cost[%d][%d][%d] = %d\n" , L[v][f] , R[v][f] , f , cost[L[v][f]][R[v][f]][f]);
}

int main(){
    int i , j;
    scanf("%d" , &N);
    scanf("%d" , &A);
    for(i = 1; i < maxn * 2; ++i){
        for(j = 0; j < 2; ++j){
            L[i][j] = INF; R[i][j] = -INF;
        }
    }
    for(i = 2; i <= A; ++i){
        int p; 
        scanf("%d" , &p);
        g[p][0].push_back(i);
    }
    for(i = 1; i <= N; ++i){
        int x;
        scanf("%d" , &x);
        L[x][0] = R[x][0] = i;
    }
    scanf("%d" , &B);
    for(i = 2; i <= B; ++i){
        int p; 
        scanf("%d" , &p);
        g[p][1].push_back(i);
    }
    for(i = 1; i <= N; ++i){
        int x;
        scanf("%d" , &x);
        L[x][1] = R[x][1] = i;
    }
    DFS(1 , 0);
    DFS(1 , 1);
    for(i = 1; i <= N; ++i){
        for(j = 0; j < i; ++j){
            DP[i] = max(DP[i] , DP[j] + max(cost[j + 1][i][0] , cost[j + 1][i][1]));
        }
        ID printf("DP[%d] = %d\n" , i , DP[i]);
    }
    printf("%d\n" , DP[N]);
}