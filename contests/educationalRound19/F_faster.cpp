/*
    DP
    O(N * M)
    DP[i][j] = min{DP[i - 1][k] + cost[i][j] - cost[i][k]}
    if x < y and y is better , then DP[i - 1][x] + cost[i][j] - cost[i][x] > DP[i - 1][y] + cost[i][j] - cost[i][y]
    DP[i - 1][x] - cost[i][x] > DP[i - 1][y] - cost[i][y]
    F[x] > F[y]
    always choose the smallest F[y] st j - y <= C[i]
    this can be done by maintaining a monotonic queue
    q[i] <= q[i + 1] and F[q[i]] <= F[q[i + 1]]
    when insert j into q, we pop until F[q.back()] <= F[j]
    we also need to delete from front until j - q.front() <= C[i]
    update DP[i][j] = min(DP[i][j] , F[q.front()] + cost[i][j])
*/
#include <bits/stdc++.h>
#define ID if(0)
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
const int maxn = 5005;
const ll INF = 1e18;
ll mice[maxn];
ii hole[maxn];
ll DP[2][maxn]; // DP[i][j] = answer for first i holes and j mices
ll cost[2][maxn]; // cost[i][j] = the total distance given mice[1..j] goes to hole[i]
int N , M;

int main(){
    int i , j , cur , pre;
    scanf("%d %d" , &N , &M);
    for(i = 1; i <= N; ++i){
        scanf("%lld" , &mice[i]);
    }
    ll s = 0;
    for(i = 1; i <= M; ++i){
        scanf("%lld %lld" , &hole[i].x , &hole[i].y);
        s += hole[i].y;
    }
    if(s < N){
        printf("-1\n");
        return 0;
    }
    sort(mice + 1 , mice + 1 + N);
    sort(hole + 1 , hole + 1 + M);
    for(j = 1; j <= N; ++j)DP[0][j] = INF;  
    for(i = 1; i <= M; ++i){
        cur = i % 2 , pre = (i - 1) % 2;
        for(j = 1; j <= N; ++j)DP[cur][j] = INF;
        for(j = 1; j <= N; ++j)cost[cur][j] = cost[cur][j - 1] + abs(mice[j] - hole[i].x);
        auto F = [&](int x){ // return F[j] = DP[i - 1][j] - cost[i][j]
            return DP[pre][x] - cost[cur][x];
        };
        deque<int> has;
        has.push_back(0);
        for(j = 1; j <= N; ++j){
            while(!has.empty() && j - has.front() > hole[i].y)has.pop_front();
            while(!has.empty() && F(j) < F(has.back()))has.pop_back();
            has.push_back(j);
            DP[cur][j] = min(DP[cur][j] , DP[pre][j]);
            if(!has.empty()){
                DP[cur][j] = min(DP[cur][j] , F(has.front()) + cost[cur][j]);
            }
        }
    }
    printf("%lld\n" , DP[M % 2][N]);
}