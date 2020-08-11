#include <bits/stdc++.h>
#define ID if(1)
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const int maxn = 5005;
const ll INF = 1e18;
int mice[maxn];
ii hole[maxn];
ll DP[2][maxn]; // DP[i][j] = answer for first i holes and j mices
ll cost[2][maxn]; // cost[i][j] = the total distance given mice[1..j] goes to hole[i]
int N , M;

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &mice[i]);
    }
    ll s = 0;
    for(int i = 1; i <= M; ++i){
        scanf("%d %d" , &hole[i].x , &hole[i].y);
        s += hole[i].y;
    }
    if(s < N){
        printf("-1\n");
        return 0;
    }
    sort(mice + 1 , mice + 1 + N);
    sort(hole + 1 , hole + 1 + M);
    for(int j = 1; j <= N; ++j)DP[0][j] = INF;  
    for(int i = 1; i <= M; ++i){
        int cur = i % 2 , pre = (i - 1) % 2;
        for(int j = 1; j <= N; ++j)DP[cur][j] = INF;
        for(int j = 1; j <= N; ++j)cost[cur][j] = cost[cur][j - 1] + abs(mice[j] - hole[i].x);
        for(int j = 1; j <= N; ++j){
            DP[cur][j] = min(DP[cur][j] , DP[pre][j]);
            for(int k = 1; k <= hole[i].y && k <= j; ++k){
                DP[cur][j] = min(DP[cur][j] , DP[pre][j - k] + cost[cur][j] - cost[cur][j - k]);
            }
        }
    }
    printf("%lld\n" , DP[M % 2][N]);
}