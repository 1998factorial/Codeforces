#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ID if(0)
using namespace std;

const int mod = 1e9 + 7;
int N , M;
char s[505][505];
int DP[2][505][505];

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
    int i , ans = 0 , total , step , x1 , y1 , x2 , y2 , u , v;
    scanf("%d %d" , &N , &M);
    for(i = 1; i <= N; ++i){
        scanf("%s" , s[i] + 1);
    }
    total = dis(1 , 1 , N , M);
    DP[0][1][M] = (s[1][1] == s[N][M]);
    for(step = 1; step <= total / 2; ++step){
        for(y1 = 0; y1 <= M; ++y1){
            for(int y2 = 0; y2 <= M; ++y2){
                DP[step % 2][y1][y2] = 0;
            }
        }
        for(y1 = 1; y1 <= M; ++y1){
            x1 = step - y1 + 2;
            if(x1 < 1 || x1 > N)continue;
            for(y2 = 1; y2 <= M; ++y2){
                x2 = N + M - y2 - step;
                if(x2 < 1 || x2 > N)continue;
                if(s[x1][y1] != s[x2][y2])continue;
                for(u = 0; u <= 1; ++u){
                    if(y1 - u < 1)continue;
                    for(v = 0; v <= 1; ++v){
                        if(y2 + v > M)continue;
                        DP[step % 2][y1][y2] = add(DP[step % 2][y1][y2] , DP[(step - 1) % 2][y1 - u][y2 + v]);
                    }
                }
                ID printf("DP[%d][%d][%d][%d][%d] = %d\n" , step , x1 , y1 , x2 , y2 , DP[step % 2][y1][y2]);
            }
        }
    }
    for(x1 = 1; x1 <= N; ++x1){
        for(y1 = 1; y1 <= M; ++y1){
            if(dis(x1 , y1 , 1 , 1) != total / 2)continue;
            for(x2 = 1; x2 <= N; ++x2){
                for(y2 = 1; y2 <= M; ++y2){
                    if(dis(x2 , y2 , N , M) != total / 2)continue;
                    if(dis(x1 , y1 , x2 , y2) == total % 2){
                        ID printf("(%d %d) (%d %d)\n" , x1 , y1 , x2 , y2);
                        ans = add(ans , DP[(total / 2) % 2][y1][y2]);
                    }
                }
            }
        }
    }
    printf("%d\n" , ans);
}       