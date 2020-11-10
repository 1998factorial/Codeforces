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
        set<ii> vis;
        has.push_back(0);
        vis.insert({F(0) , 0});
        //ID printf("for i = %d\n" , i);
        for(j = 1; j <= N; ++j){
            //ID printf("at j = %d\n" , j);
            while(!has.empty() && j - has.front() > hole[i].y){
                int id = has.front();
                //ID printf("poping out %d\n" , id);
                vis.erase(vis.find({F(id) , id}));
                has.pop_front();
            }
            DP[cur][j] = min(DP[cur][j] , DP[pre][j]);
            if(!has.empty()){
                DP[cur][j] = min(DP[cur][j] , vis.begin()->first + cost[cur][j]);
            }
            //ID printf("DP[%d][%d] = %lld\n" , i , j , DP[cur][j]);
            has.push_back(j);
            vis.insert({F(j) , j});
        }
    }
    printf("%lld\n" , DP[M % 2][N]);
}