/*
    Constructive algorithm

    It is not hard to see that, the grid can be transformed into a graph
    firstly, we can find what cases will lead to a Not unique solution
    If there exists empty cell, where it's degree is 0 then we have no solution
    If there is no empty cell who's degree is 1, then we know that there exists
    at least 2 configurations.
    Then, we can push all the cells who's degree is 1 into the queue and perform
    BFS, in each iteration of BFS, if the cell has not been visited, then we pick one of
    it's neighbour, assign values on them, now, set it's neighbour's degree to 0,
    and decrease each of it's neighbour's degree by 1. push them into queue if their degree
    is 1
    At the end, if there is still undecided cell, then we know there is no solution
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;

const int maxn = 2e3 + 10;
char a[maxn][maxn];
int N , M;
int g[maxn][maxn];
bool vis[maxn][maxn];
int dx[4] = {1 , -1 , 0 , 0};
int dy[4] = {0 , 0 , 1 , -1};

void NO(){
    cout << "Not unique\n";
}

int main(){
    cin >> N >> M;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            cin >> a[i][j];
            g[i][j] = 0;
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(a[i][j] == '*')continue;
            for(int k = 0; k < 4; ++k){
                int di = i + dx[k];
                int dj = j + dy[k];
                if(di < 1 || di > N || dj < 1 || dj > M)continue;
                if(a[di][dj] == '*')continue;
                ++g[i][j];
            }
        }
    }
    queue<ii> q;
    int cnt = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(a[i][j] != '*' && g[i][j] == 0){
                NO();
                return 0;
            }
            if(g[i][j] == 1){
                q.push(make_pair(i , j));
            }
            if(g[i][j] >= 1)++cnt;
        }
    }
    if(q.empty() && cnt){
        NO();
        return 0;
    }
    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;
        if(!vis[x][y]){
            vis[x][y] = 1;
            for(int i = 0; i < 4; ++i){
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx < 1 || nx > N || ny < 1 || ny > M)continue;
                if(g[nx][ny] <= 0)continue;
                if(vis[nx][ny])continue;
                --g[x][y];
                g[nx][ny] = 0;
                cnt -= 2;
                if(i == 0){
                    a[x][y] = '^';
                    a[nx][ny] = 'v';
                }
                if(i == 1){
                    a[x][y] = 'v';
                    a[nx][ny] = '^';
                }
                if(i == 2){
                    a[x][y] = '<';
                    a[nx][ny] = '>';
                }
                if(i == 3){
                    a[x][y] = '>';
                    a[nx][ny] = '<';
                }
                for(int j = 0; j < 4; ++j){
                    int nnx = nx + dx[j];
                    int nny = ny + dy[j];
                    if(nnx < 1 || nnx > N || nny < 1 || nny > M)continue;
                    if(vis[nnx][nny])continue;
                    --g[nnx][nny];
                    if(g[nnx][nny] == 1)q.push(make_pair(nnx , nny));
                }
                break;
            }
        }
    }
    if(cnt > 0){
        NO();
        return 0;
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            cout << a[i][j];
        }
        cout << endl;
    }
}
