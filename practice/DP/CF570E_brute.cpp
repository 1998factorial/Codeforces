#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ID if(0)
using namespace std;

const int mod = 1e9 + 7;
int N , M;
char s[505][505];
int DP[20][20][20][20][20];

int add(int x , int y){
    return (x + y) % mod;
}

int mul(int x , int y){
    return x * y % mod;
}

int dis(int x1 , int y1 , int x2 , int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i){
        scanf("%s" , s[i] + 1);
    }
    DP[0][1][1][N][M] = (s[1][1] == s[N][M]);
    int total = dis(1 , 1 , N , M);
    for(int step = 1; step <= total / 2; ++step){
        for(int x1 = 1; x1 <= N; ++x1){
            for(int y1 = 1; y1 <= M; ++y1){
                if(dis(1 , 1 , x1 , y1) != step)continue;
                for(int x2 = 1; x2 <= N; ++x2){
                    for(int y2 = 1; y2 <= M; ++y2){
                        if(dis(x2 , y2 , N , M) != step)continue;
                        if(s[x1][y1] != s[x2][y2])continue;
                        for(int a : {0 , 1}){
                            int b = 1 - a;
                            for(int c : {0 , 1}){
                                int d = 1 - c;
                                if(x1 - a < 1 || y1 - b < 1 || x2 + c > N || y2 + d > M)continue;
                                ID printf("(%d %d %d %d) -> (%d %d %d %d)\n" , x1 , y1 , x2 , y2 , x1 - a , y1 - b , x2 + c , y2 + d);
                                DP[step][x1][y1][x2][y2] = add(DP[step][x1][y1][x2][y2] , DP[step - 1][x1 - a][y1 - b][x2 + c][y2 + d]);
                            }
                        }
                        ID printf("DP[%d][%d][%d][%d][%d] = %d\n" , step , x1 , y1 , x2 , y2 , DP[step][x1][y1][x2][y2]);
                    }   
                }
            }
        }
    }
    int ans = 0;
    for(int x1 = 1; x1 <= N; ++x1){
        for(int y1 = 1; y1 <= M; ++y1){
            if(dis(x1 , y1 , 1 , 1) != total / 2)continue;
            for(int x2 = 1; x2 <= N; ++x2){
                for(int y2 = 1; y2 <= M; ++y2){
                    if(dis(x2 , y2 , N , M) != total / 2)continue;
                    if(dis(x1 , y1 , x2 , y2) == total % 2){
                        ID if(DP[total / 2][x1][y1][x2][y2])printf("(%d %d) , (%d %d)\n" , x1 , y1 , x2 , y2);
                        printf("(%d %d) (%d %d)\n" , x1 , y1 , x2 , y2);
                        ans = add(ans , DP[total / 2][x1][y1][x2][y2]);
                    }
                }
            }
        }
    }
    printf("%d\n" , ans);
}       