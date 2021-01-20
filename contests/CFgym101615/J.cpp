#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N , M;
char a[50][50];
int rb[50] , rr[50];
bool vis[50][50];
ll DP[50][50];

int main(){
    cin >> N >> M;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            cin >> a[i][j];
        }
    }
    if(a[1][1] == 'R'){
        int ok = 1;
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= M; ++j){
                if(a[i][j] == 'B')ok = 0;
            }
        }
        cout << ok << endl;
        return 0;
    }
    for(int i = 1; i <= N; ++i){
        rb[i] = 0 , rr[i] = M + 1;
        for(int j = M; j >= 1; --j){
            if(a[i][j] == 'B'){
                rb[i] = j;
                break;
            }
        }
        for(int j = 1; j <= M; ++j){
            if(a[i][j] == 'R'){
                rr[i] = j;
                break;
            }
        }
        //printf("rb[%d] = %d , rr[%d] = %d\n" , i , rb[i] , i , rr[i]);
    }
    DP[0][M] = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = rb[i]; j < rr[i]; ++j){ 
            for(int pj = j; pj <= M; ++pj){
                DP[i][j] += DP[i - 1][pj];
            }
            //printf("DP[%d][%d] = %lld\n" , i , j , DP[i][j]);
        }
    }
    ll ret = 0;
    for(int i = 0; i <= M; ++i){
        ret += DP[N][i];
    }
    cout << ret << endl;
}