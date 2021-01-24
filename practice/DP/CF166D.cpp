#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const ll INF = 1e18;
int N , M;
array<int , 3> shoe[maxn] , cust[maxn];
array<int , 2> pre[maxn][2][2];
array<int , 2> best[maxn][2][2];
ll DP[maxn][2][2];
int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d" , &shoe[i][0] , &shoe[i][1]); // (c , s)
        shoe[i][2] = i;
    }
    scanf("%d" , &M);
    for(int i = 1; i <= M; ++i){
        scanf("%d %d" , &cust[i][0] , &cust[i][1]); // (d , l)
        cust[i][2] = i;
    }
    sort(shoe + 1 , shoe + 1 + N , [&](array<int , 3>& l , array<int , 3>& r){
        return l[1] < r[1];
    });
    sort(cust + 1 , cust + 1 + M , [&](array<int , 3>& l , array<int , 3>& r){
        return l[1] < r[1];
    });
    for(int i = 0; i <= M; ++i){
        for(int j = 0; j < 2; ++j){
            for(int k = 0; k < 2; ++k){
                DP[i][j][k] = -INF;
                pre[i][j][k] = {-1 , -1};
            }
        }
    }   
    /*printf("shoes\n");
    for(int i = 1; i <= N; ++i){
        printf("%d %d %d\n" , shoe[i][0] , shoe[i][1] , shoe[i][2]);
    }
    printf("cust\n");
    for(int i = 1; i <= M; ++i){
        printf("%d %d %d\n" , cust[i][0] , cust[i][1] , cust[i][2]);
    }*/
    DP[0][0][0] = 0;
    int x = 0;
    for(int i = 0; i < M; ++i){
        while(x + 1 <= N && shoe[x + 1][1] <= cust[i + 1][1] + 1)++x;
        for(int j = 0; j < 2; ++j){
            for(int k = 0; k < 2; ++k){
                if(DP[i][j][k] >= 0){
                    int msz1 = cust[i + 1][1];
                    int msz2 = cust[i + 1][1] + 1;
                    int nsz1 = x - 1 > 0 ? shoe[x - 1][1] : -100;
                    int nsz2 = x > 0 ? shoe[x][1] : -100;
                    int sz1 = (i > 0 ? cust[i][1] : -100);
                    int sz2 = (i > 0 ? cust[i][1] + 1 : -100);
                    int pz1 = x - 1 > 0 ? shoe[x - 1][0] : cust[i + 1][0] + 10;
                    int pz2 = x > 0 ? shoe[x][0] : cust[i + 1][0] + 10;
                    // j => exist shoe size = cust[i][1] 
                    // k => exist shoe size = cust[i][1] + 1
                    // can cust[i + 1] buy shoe[x - 1] ? 

                    // 4 , 5
                    // 5 , 6

                    if(msz1 == nsz2){
                        int f = (msz1 == nsz2) && pz2 <= cust[i + 1][0];
                        if(sz2 == nsz2 && !k)f = 0;
                        if(sz1 == nsz2 && !j)f = 0;
                        // DP[i + 1][f][0]
                        if(x && f && DP[i + 1][0][0] < DP[i][j][k] + (ll)shoe[x][0]){
                            DP[i + 1][0][0] = DP[i][j][k] + (ll)shoe[x][0];
                            pre[i + 1][0][0] = {j , k};
                            best[i + 1][0][0] = {cust[i + 1][2] , shoe[x][2]};
                        }

                        if(DP[i + 1][f][0] < DP[i][j][k]){
                            DP[i + 1][f][0] = DP[i][j][k];
                            best[i + 1][f][0] = {-1 , -1};
                            pre[i + 1][f][0] = {j , k};
                        }
                    }
                    else{
                        int f1 = (msz1 == nsz1) && pz1 <= cust[i + 1][0];
                        if(sz2 == nsz1 && !k)f1 = 0;
                        if(sz1 == nsz1 && !j)f1 = 0;
                        //printf("at(%d %d %d) , f1 = %d\n" , i , j , k , f1);
                        // can cust[i + 1] buy shoe[x] ? 
                        int f2 = (msz2 == nsz2) && pz2 <= cust[i + 1][0];
                        if(sz2 == nsz2 && !k)f2 = 0;
                        if(sz1 == nsz2 && !j)f2 = 0;
                        //printf("at(%d %d %d) , f2 = %d\n" , i , j , k , f2);
                        //DP[i + 1][f1][0] = max(DP[i + 1][f1][0] , DP[i][j][k] + (ll)shoe[x][0] * f2); // buy shoe[x]
                        //DP[i + 1][0][f2] = max(DP[i + 1][0][f2] , DP[i][j][k] + (ll)(x - 1 > 0 ? shoe[x - 1][0] : 0) * f1); // buy shoe[x - 1]
                        //DP[i + 1][f1][f2] = max(DP[i + 1][f1][f2] , DP[i][j][k]); // buy none

                        if(x && f2 && DP[i + 1][f1][0] < DP[i][j][k] + (ll)shoe[x][0]){
                            DP[i + 1][f1][0] = DP[i][j][k] + (ll)shoe[x][0];
                            pre[i + 1][f1][0] = {j , k};
                            best[i + 1][f1][0] = {cust[i + 1][2] , shoe[x][2]};
                        }

                        if(x - 1 > 0 && f1 && DP[i + 1][0][f2] < DP[i][j][k] + (ll)shoe[x - 1][0]){
                            DP[i + 1][0][f2] = DP[i][j][k] + (ll)shoe[x - 1][0];
                            pre[i + 1][0][f2] = {j , k};
                            best[i + 1][0][f2] = {cust[i + 1][2] , shoe[x - 1][2]};
                        }

                        if(DP[i + 1][f1][f2] < DP[i][j][k]){
                            DP[i + 1][f1][f2] = DP[i][j][k];
                            pre[i + 1][f1][f2] = {j , k};
                            best[i + 1][f1][f2] = {-1 , -1};
                        }
                    }
                }   
            }
        }
    }
    ll ret = 0;
    /*for(int i = 1; i <= M; ++i){
        for(int j = 0; j < 2; ++j){
            for(int k = 0; k < 2; ++k){
                printf("DP[%d][%d][%d] = %lld\n" , i , j , k , DP[i][j][k]);
            }
        }
    }*/
    int bi = 0 , bj = 0;
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 2; ++j){
            if(ret < DP[M][i][j]){
                ret = DP[M][i][j];
                bi = i;
                bj = j;
            }
        }
    }
    printf("%lld\n" , ret);
    if(ret == 0){
        printf("0\n");
        return 0;
    }
    vector<array<int , 2>> ans;
    while(M){   
        if(~best[M][bi][bj][0] && ~best[M][bi][bj][1]){
            ans.push_back({best[M][bi][bj][0] , best[M][bi][bj][1]});
        }
        int ni = pre[M][bi][bj][0];
        int nj = pre[M][bi][bj][1];
        bi = ni;
        bj = nj;
        --M;
    }
    printf("%d\n" , (int)ans.size());
    for(auto& e : ans){
        printf("%d %d\n" , e[0] , e[1]);
    }
}
