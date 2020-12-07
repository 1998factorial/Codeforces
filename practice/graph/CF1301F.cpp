#include <bits/stdc++.h>
using namespace std;
// Hard graph problem, rating 2600
// in one second, we can go to any adjcent cell or
// any cell with the same colour as my current cell
// compute for each Q (1 <= 1e5) query that
// given a starting cell and ending cell
// the minimal time needed to go from start to end
const int INF = 1e9;
int N , M , K , Q;
vector<array<int , 2>> col_pos[41]; 
int dir[4][2] = {{0 , 1} , {0 , -1} , {1 , 0} , {-1 , 0}};
// Observation: we either do not use any of the second type edge
// or we use at least once
// the goal of using second type edge is to shorten the mamhatten distance
// so if we can "relax" on the intermidiate usage of the second type edge
// say we used colour k, then our answer will be:
// "min cost from start to some colour k vertex" + "min cost from some colour k to end" + 1
// let this be dis[k][start] + dis[k][end] + 1,
// now we need to find dis[i][j] for all colour and positions.
// we can do this for each colour k, use BFS with multiple sources to find the shortest distance
// from each cell to vertex of colour k.
int main(){
    scanf("%d %d %d" , &N , &M , &K);
    vector<vector<int>> a(N + 1 , vector<int>(M + 1));
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            scanf("%d" , &a[i][j]);
            col_pos[a[i][j]].push_back({i , j});
        }
    }
    vector<vector<vector<int>>> dis(K + 1 , vector<vector<int>>(N + 1 , vector<int>(M + 1 , INF)));
    //dis[k][r][c] = minimal cost from (r , c) to get to some vertex that have colour k
    //put all cells whose colour = k into source
    //run BFS to find shortest path
    for(int k = 1; k <= K; ++k){
        queue<array<int , 2>> q;
        vector<bool> col_vis(K + 1);
        for(array<int , 2>& e : col_pos[k]){
            dis[k][e[0]][e[1]] = 0;
            q.push({e[0] , e[1]});
        }
        col_vis[k] = 1;
        while(!q.empty()){
            array<int , 2> cur = q.front();
            int c = a[cur[0]][cur[1]];
            q.pop();
            if(!col_vis[c]){
                col_vis[c] = 1;
                for(array<int , 2>& e : col_pos[c]){
                    if(dis[k][e[0]][e[1]] == INF){
                        dis[k][e[0]][e[1]] = dis[k][cur[0]][cur[1]] + 1; 
                        q.push({e[0] , e[1]});
                    }
                }
            }
            for(int i = 0; i < 4; ++i){
                int nx = cur[0] + dir[i][0];
                int ny = cur[1] + dir[i][1];
                if(nx < 1 || nx > N || ny < 1 || ny > M)continue;
                if(dis[k][nx][ny] == INF){
                    dis[k][nx][ny] = dis[k][cur[0]][cur[1]] + 1;
                    q.push({nx , ny});
                }
            }
        }
    }
    scanf("%d" , &Q);
    while(Q--){
        int r1 , c1 , r2 , c2;
        scanf("%d %d %d %d" , &r1 , &c1 , &r2 , &c2);
        int ans = abs(r1 - r2) + abs(c1 - c2); // we do not take the second type
        for(int k = 1; k <= K; ++k){ // we take at least one of the second type
            ans = min(ans , dis[k][r1][c1] + dis[k][r2][c2] + 1);
            // if (r1 -> c1) -> (colour k) -> (r2 , c2)
            // does not have the colour k -> colour k intermdiate transfer
            // then we do not need to take this colour. (whats the point of using this colour?)
        }
        printf("%d\n" , ans);
    }
}