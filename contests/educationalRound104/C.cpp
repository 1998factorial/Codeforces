#include <bits/stdc++.h>
using namespace std;

bool vis[105];
int deg[105];
int g[105][105];
int ans[105][105];
int score[105];
int N;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        cin >> N;
        for(int i = 1; i <= N; ++i){
            score[i] = 0;
            deg[i] = N - 1;
            for(int j = 1; j <= N; ++j){
                if(i != j)g[i][j] = 1;
                ans[i][j] = 0;
            }
        }
        // we want indeg[v] = outdeg[v] for all v
        for(int d = 1; d <= N; ++d){
            //printf("for d = %d\n" , d);
            for(int i = 1; i <= N; ++i)vis[i] = 0;
            int ok = 1;
            for(int i = 1; i <= N; ++i)ok &= deg[i] >= 2;
            if(!ok)break;
            for(int v = 1; v <= N; ++v){
                if(vis[v])continue;
                int f = 0 , cv = v;
                while(1){
                    int nv = (cv + d - 1) % N + 1;
                    //printf("cv = %d , nv = %d\n" , cv , nv);
                    if(vis[cv])break;
                    --deg[cv];
                    --deg[nv];
                    vis[cv] = 1;
                    ans[cv][nv] = 1;
                    ans[nv][cv] = -1;
                    cv = nv;
                }
            }
        }
        for(int i = 1; i <= N; ++i){
            for(int j = i + 1; j <= N; ++j){
                if(ans[i][j] == 1){
                    score[i] += 3;
                }
                else if(ans[i][j] == -1){
                    score[j] += 3;
                }
                else score[i] += 1 , score[j] += 1;
            }
        }
        for(int i = 2; i <= N; ++i){
            assert(score[i] == score[i - 1]);
        }
        for(int i = 1; i <= N; ++i){
            for(int j = i + 1; j <= N; ++j){
                cout << ans[i][j] << " ";
            }
        }
        cout << endl;
    }
}       