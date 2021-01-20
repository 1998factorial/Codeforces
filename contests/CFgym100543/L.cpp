#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        int N;
        scanf("%d" , &N);
        // DP[i][j] = min cost to destory all segments that are fully covered in [i , j]
        vector<vector<int>> a(N + 1 , vector<int> (3));
        vector<int> tmp;
        for(int i = 1; i <= N; ++i){
            scanf("%d %d %d" , &a[i][0] , &a[i][1] , &a[i][2]);
            tmp.push_back(a[i][0]);
            tmp.push_back(a[i][1]);
        }
        sort(tmp.begin() , tmp.end());
        int M = 0;
        map<int , int> mp;
        for(int i : tmp){
            if(!mp[i])mp[i] = ++M;
        }
        for(int i = 1; i <= N; ++i){
            a[i][0] = mp[a[i][0]];
            a[i][1] = mp[a[i][1]];
            //printf("[%d %d]\n" , a[i][0] , a[i][1]);
        }
        vector<vector<int>> DP(M + 2 , vector<int> (M + 2 , INF));
        for(int i = 1; i <= M + 1; ++i){
            DP[i][i - 1] = 0;
        }
        for(int len = 1; len <= M; ++len){
            for(int i = 1; i + len - 1 <= M; ++i){
                int j = i + len - 1 , maxv = 0 , id = -1;
                for(int k = 1; k <= N; ++k){
                    if(i <= a[k][0] && a[k][1] <= j){
                        if(maxv < a[k][2]){
                            maxv = a[k][2];
                            id = k;
                        }
                    }
                }
                if(id == -1){
                    DP[i][j] = 0;
                }
                else{
                    for(int k = a[id][0]; k <= a[id][1]; ++k){
                        DP[i][j] = min(DP[i][j] , DP[i][k - 1] + DP[k + 1][j] + maxv);
                    }
                }
                //printf("DP[%d][%d] = %d\n" , i , j , DP[i][j]);
            }
        }
        printf("%d\n" , DP[1][M]);
    }
}
