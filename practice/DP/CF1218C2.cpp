#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(1)
using namespace std;
typedef long long ll;
typedef pair<int , int> pii;
const ll INF = 1e18;
ll a[505][505] , DP[505][505][2];
int N , M , K;
vector<pii> hor[505];
vector<pair<pii , int>> pos[505][505] , ver[505];
// DP[i][j][0] = minimal loss if we are ar (i , j) , given that our
// last move is horizontal
// DP[i][j][1] = minimal loss if we are ar (i , j) , given that our
// last move is vertical
// tl (x , y) , bl (x + d , y - d) , br (x + d , y) ,tr (x , y + d)

int ok(int x , int y , int t){ // check if we will ever encounter transformer at this spot
    return (x + y) >= t && (x + y) % 4 == t % 4;
}

int main(){
    scanf("%d %d %d" , &N , &M , &K);
    int i , j , k;
    for(i = 1; i <= K; ++i){
        int x , y , d , t , e;
        scanf("%d %d %d %d %d" , &x , &y , &d , &t , &e);
        int top_left = ok(x , y , t);
        int top_right = ok(x , y + d , t + 3);
        int bottom_left = ok(x + d , y - d , t + 1);
        int bottom_right = ok(x + d , y , t + 2);
        if(top_left) a[x][y] += e;
        if(top_right) a[x][y + d] += e;
        if(bottom_left) a[x + d][y - d] += e;
        if(bottom_right) a[x + d][y] += e;
        if(top_left && top_right){
            // trans[i] can go from top_left to top_right
            hor[x].emplace_back(y + d , e);
            pos[x][y].push_back({{x , y + d} , e});
        }
        if(top_left && bottom_right){
            // trans[i] can go from top_left to bottom_right
            a[x + d][y] -= e;
            ver[x].push_back({{x + d , y} , e});
        }
        if(bottom_left && bottom_right){
            // trans[i] can go from bottom_left to bottom_right
            hor[x + d].emplace_back(y , e);
            pos[x + d][y - d].push_back({{x + d , y} , e});
        }
    }
    for(i = 0; i < N; ++i){ 
        for(j = 0; j < M; ++j){
            for(k = 0; k < 2; ++k){
                DP[i][j][k] = INF;
            }
        }
    }
    for(k = 0; k < 2; ++k)DP[0][0][k] = a[0][0];
    for(i = 0; i < N; ++i){
        for(pii& e : hor[i])a[i][e.x] -= e.y;
        for(j = 0; j < M; ++j){
            ll cost = 0;
            for(k = i + 1; k < N; ++k){ // move vertically
                cost += a[k][j];
                DP[k][j][1] = min(DP[k][j][1] , DP[i][j][0] + cost);
            }
            cost = 0;
            for(k = j + 1; k < M; ++k){ // move horizontally
                cost += a[i][k];
                DP[i][k][0] = min(DP[i][k][0] , DP[i][j][1] + cost);
            }
            for(pair<pii , int>& e : pos[i][j])a[e.x.x][e.x.y] += e.y;
        }
        for(pair<pii , int>& e : ver[i])a[e.x.x][e.x.y] += e.y;
    }
    ll ret = min(DP[N - 1][M - 1][0] , DP[N - 1][M - 1][1]);
    printf("%lld\n" , ret);
}