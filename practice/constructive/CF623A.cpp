/*
    Constructive
    only invalid pair (a , c) , invalid case is much less than valid case
    we should consider then complement graph
*/
#include <bits/stdc++.h>
using namespace std;

int N , M;
int g[505][505];
vector<int> g2[505];
char ans[505];
int isOK;

void DFS(int v , char c){
    ans[v] = c;
    for(int u : g2[v]){
        if(!ans[u]){
            char nc = (c == 'a') ? 'c' : 'a';
            DFS(u , nc);
        }
        else if(ans[u] == c){
            isOK = 0;
        }
    }
}

int main(){
    cin >> N >> M;
    for(int i = 1; i <= M; ++i){
        int x , y; cin >> x >> y;
        ++g[x][y]; ++g[y][x];
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            if(i != j && g[i][j] == 0){
                g2[i].push_back(j);
            }
        }
    }
    isOK = 1;
    for(int i = 1; i <= N; ++i){
        if(g2[i].size() && !ans[i]){
            DFS(i , 'a');
        }
        else if(g2[i].size() == 0){
            ans[i] = 'b';
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            if(g[i][j] && abs(ans[i] - ans[j]) > 1){
                isOK = 0;
            }
        }
    }
    if(isOK){
        cout << "YES" << endl;
        for(int i = 1; i <= N; ++i){
            cout << ans[i];
        }
        cout << endl;
    }
    else{
        cout << "NO" << endl;
    }
}
