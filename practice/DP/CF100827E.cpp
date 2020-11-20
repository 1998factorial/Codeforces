#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

char s[75];
int a[75] , N;
ll DP[75][10][2][2];
// DP[length = i][last digit][have we decreased ?][is the current number = a?]

int check(){
    // check if v is a hill number
    // once it decrease, it can never increase again
    N = strlen(s + 1);
    for(int i = 1; i <= N; ++i){
        a[i] = s[i] - '0';
    }
    bool dec = 0;
    for(int i = 2; i <= N; ++i){
        if(a[i] == a[i - 1])continue;
        if(a[i] > a[i - 1]){
            if(dec){
                return 0;
            }
        }
        if(a[i] < a[i - 1])dec = 1;
    }
    return 1;
}

ll solve(){
    memset(DP , 0 , sizeof(DP));
    DP[0][0][0][1] = 1;
    for(int i = 0; i < N; ++i){
        for(int d = 0; d < 10; ++d){
            for(int x = 0; x < 2; ++x){
                for(int y = 0; y < 2; ++y){
                    if(DP[i][d][x][y] == 0)continue;
                    for(int nd = 0; nd < 10; ++nd){
                        // !x => we have not decreased yet , so we can still increase
                        // x => we have decreased , so we can not increase again
                        // y => current number = a
                        // !y => current number < a
                        if(x && nd > d)continue;
                        if(y && nd > a[i + 1])continue;
                        int nx = x || nd < d;
                        int ny = y && nd == a[i + 1];
                        DP[i + 1][nd][nx][ny] += DP[i][d][x][y];
                    }
                }
            }
        }
    }
    ll ret = 0;
    for(int i = 0; i < 10; ++i){
        for(int x = 0; x < 2; ++x){
            for(int y = 0; y < 2; ++y){
                ret += DP[N][i][x][y];
            }
        }
    }
    return ret - 1; // exclude zero
}

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        scanf("%s" , (s + 1));
        if(check()){
            printf("%lld\n" , solve());
        }
        else{
            printf("-1\n");
        }
    }
}