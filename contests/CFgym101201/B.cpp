#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a  , b) for(int i = a; i >= b; --i)
#define ID if(0)
using namespace std;
const int INF = 1e9;
int N , M , L;
int ex , ey; // ending 
int sx , sy;
int dir[4][2] = {{0 , 1} , {0 , -1} , {1 , 0} , {-1 , 0}};
int dis[55][55][55];
char s[55][55] , command[55];

int main(){
    cin >> N >> M;
    rep(i , 1,  N){
        rep(j , 1 , M){
            cin >> s[i][j];
            if(s[i][j] == 'R')sx = i , sy = j;
            else if(s[i][j] == 'E')ex = i , ey = j;
        }
    }   
    cin >> (command + 1);
    L = strlen(command + 1);
    rep(i , 1 , N){
        rep(j , 1 , M){
            rep(k , 0 , L){
                dis[i][j][k] = INF;
            }
        }
    }
    auto inside = [&](int x , int y){
        return 1 <= x && x <= N && 1 <= y && y <= M;
    };
    auto wall = [&](int x , int y){
        return s[x][y] == '#';
    };
    deque<array<int , 3>> q;
    q.push_back({sx , sy , 0});
    dis[sx][sy][0] = 0;
    while(!q.empty()){
        array<int , 3> cur = q.front();
        q.pop_front();
        int x = cur[0] , y = cur[1] , l = cur[2] , d = dis[x][y][l];
        // ignore 
        if(l < L){
            if(dis[x][y][l + 1] > d + 1){
                dis[x][y][l + 1] = d + 1;
                q.push_back({x , y , l + 1});
            }
        }
        // use extra L
        if(inside(x , y - 1) && !wall(x , y - 1)){
            if(dis[x][y - 1][l] > d + 1){
                dis[x][y - 1][l] = d + 1;
                q.push_back({x , y - 1 , l});
            }
        }
        // use extra R
        if(inside(x , y + 1) && !wall(x , y + 1)){
            if(dis[x][y + 1][l] > d + 1){
                dis[x][y + 1][l] = d + 1;
                q.push_back({x , y + 1 , l});
            }
        }
        // use extra U
        if(inside(x - 1 , y) && !wall(x - 1 , y)){
            if(dis[x - 1][y][l] > d + 1){
                dis[x - 1][y][l] = d + 1;
                q.push_back({x - 1 , y , l});
            }
        }
        // use extra D
        if(inside(x + 1 , y) && !wall(x + 1 , y)){
            if(dis[x + 1][y][l] > d + 1){
                dis[x + 1][y][l] = d + 1;
                q.push_back({x + 1 , y , l});
            }
        }
        if(l + 1 <= L){
            if(command[l + 1] == 'L'){
                if(inside(x , y - 1) && !wall(x , y - 1)){
                    if(dis[x][y - 1][l + 1] > d){
                        dis[x][y - 1][l + 1] = d;
                        q.push_front({x , y - 1 , l + 1});
                    }
                }
                else{
                    if(dis[x][y][l + 1] > d){
                        dis[x][y][l + 1] = d;
                        q.push_front({x , y , l + 1});
                    }
                }
            }
            if(command[l + 1] == 'R'){
                if(inside(x , y + 1) && !wall(x , y + 1)){
                    if(dis[x][y + 1][l + 1] > d){
                        dis[x][y + 1][l + 1] = d;
                        q.push_front({x , y + 1 , l + 1});
                    }
                }
                else{
                    if(dis[x][y][l + 1] > d){
                        dis[x][y][l + 1] = d;
                        q.push_front({x , y , l + 1});
                    }
                }
            }
            if(command[l + 1] == 'U'){
                if(inside(x - 1 , y) && !wall(x - 1 , y)){
                    if(dis[x - 1][y][l + 1] > d){
                        dis[x - 1][y][l + 1] = d;
                        q.push_front({x - 1 , y , l + 1});
                    }
                }
                else{
                    if(dis[x][y][l + 1] > d){
                        dis[x][y][l + 1] = d;
                        q.push_front({x , y , l + 1});
                    }
                }
            }
            if(command[l + 1] == 'D'){
                if(inside(x + 1 , y) && !wall(x + 1 , y)){
                    if(dis[x + 1][y][l + 1] > d){
                        dis[x + 1][y][l + 1] = d;
                        q.push_front({x + 1 , y , l + 1});
                    }
                }
                else{
                    if(dis[x][y][l + 1] > d){
                        dis[x][y][l + 1] = d;
                        q.push_front({x , y , l + 1});
                    }
                }
            }
        }
    }
    int ret = INF;
    rep(i , 0 , L){
        ret = min(ret , dis[ex][ey][i]);
    }
    printf("%d\n" , ret);
}   