#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e3 + 10;
int N;
double p[maxn];
double DP[maxn][maxn * 2];


int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%lf" , &p[i]);
    }
    DP[0][3000] = 1.0;
    for(int i = 1; i <= N; ++i){
        for(int j = 3000 - N; j <= 3000 + N; ++j){
            DP[i][j] = p[i] * DP[i - 1][j - 1] + (1.0 - p[i]) * DP[i - 1][j + 1];
        }
    }
    double ret = 0;
    for(int i = 1; i <= N; ++i){
        ret += DP[N][3000 + i];
    }
    printf("%.12lf\n" , ret);
}
