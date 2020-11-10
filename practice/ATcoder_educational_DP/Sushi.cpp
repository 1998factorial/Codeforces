#include <bits/stdc++.h>
using namespace std;

const int maxn = 310;
int N;
int cnt[4];
double DP[maxn][maxn][maxn];

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        int x; scanf("%d" , &x); ++cnt[x];
    }
    for(int c = 0; c <= N; ++c){
        for(int b = 0; b <= N; ++b){
            for(int a = 0; a <= N; ++a){
                if(a == 0 && b == 0 && c == 0)continue;
                if(a + b + c > N)continue;
                DP[a][b][c] += (double)N / (a + b + c);
                // get 1
                if(a - 1 >= 0){
                    DP[a][b][c] += (double)a / (a + b + c) * DP[a - 1][b][c];
                }
                // get 2
                if(b - 1 >= 0){
                    DP[a][b][c] += (double)b / (a + b + c) * DP[a + 1][b - 1][c];
                }
                // get 3
                if(c - 1 >= 0){
                    DP[a][b][c] += (double)c / (a + b + c) * DP[a][b + 1][c - 1];
                }
            }
        }
    }
    printf("%.12lf\n" , DP[cnt[1]][cnt[2]][cnt[3]]);
}
