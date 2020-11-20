#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int INF = 1e9;
int N , M , K;
int a[5005] , b[5005] , c[5005] , DP[5005][5005];
int to[5005];
vector<int> g[5005];
// DP[i][j] = maximal sum when we conqure first i city defends j city
 
int main(){
    scanf("%d %d %d" , &N , &M , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d %d" , &a[i] , &b[i] , &c[i]);
    }
    for(int i = 1; i <= M; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        to[v] = max(u , to[v]);
    }    
    for(int i = 1; i <= N; ++i){
        if(to[i]){
            g[to[i]].push_back(i);
        }
    }
    for(int i = 1; i <= N; ++i){
        sort(g[i].begin() , g[i].end() , [&](int x , int y){
            return c[x] > c[y];
        });
    }
    ID for(int i = 1; i <= N; ++i){
        cout << "show for i = " << i << endl;
        for(int j  : g[i]){
            cout << j << " ";
        }
        cout << endl;
    }
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            DP[i][j] = -INF;
        }
    }
    DP[0][0] = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j <= i; ++j){
            if(DP[i][j] <= -INF)continue;
            ID printf("DP[%d][%d] = %d\n" , i , j , DP[i][j]);
            int nw = K - j;
            if(nw < a[i + 1])break;
            // can not take over c[i + 1]
            if(to[i + 1]){
                // we can go back to city c[i + 1] in the future
                DP[i + 1][j] = max(DP[i + 1][j] , DP[i][j]);
            }
            else{
                // can not move back
                DP[i + 1][j] = max(DP[i + 1][j] , DP[i][j]);
                if(nw + b[i + 1] >= 1)DP[i + 1][j + 1] = max(DP[i + 1][j + 1] , DP[i][j] + c[i + 1]);
            }
            // we go back to previous ones once conquer c[i + 1]
            int v = 0;
            for(int k = 0; k < g[i + 1].size(); ++k){
                v += c[g[i + 1][k]];
                if(nw + b[i + 1] >= k + 1)DP[i + 1][j + k + 1] = max(DP[i + 1][j + k + 1] , DP[i][j] + v);
                if(to[i + 1] == 0 && nw + b[i + 1] >= k + 2)DP[i + 1][j + k + 2] = max(DP[i + 1][j + k + 2] , DP[i][j] + v + c[i + 1]);
            }
        }
        K += b[i + 1];
    }
    int ret = -INF;
    for(int i = 0; i <= N; ++i){
        ret = max(ret , DP[N][i]);
    }
    if(ret == -INF){
        printf("-1\n");
    }
    else{
        printf("%d\n" , ret);
    }
}