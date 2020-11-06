#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
int a[3][100005] , N;
ll DP[100005][4];
// we turn left by 1
// and it is the same as filling col[i] and col[i - 1]
// if we turn left by 2 or more
// it can be reduced to some normal no left turn path combine with some turn left by 1 path at the end (depends on parity)
// DP[i][j] = maximal sum if we are at col i , row = j
// if j = 3, means we get the whole col i

ll cost(int col , int l , int r){
    ll ret = 0;
    if(l > r)swap(l , r);
    for(int i = l; i <= r; ++i){
        ret += a[i][col];
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cin >> N;
    for(int i = 0; i < 3; ++i){
        for(int j = 1; j <= N; ++j){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i <= 3; ++i){
        for(int j = 0; j <= N; ++j){
            DP[j][i] = -INF;
        }
    }
    DP[0][0] = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 3; ++j){
            for(int k = 0; k < 3; ++k){
                DP[i][j] = max(DP[i][j] , DP[i - 1][k] + cost(i , j , k)); // do not turn left
            }
        }
        DP[i][0] = max(DP[i][0] , DP[i - 1][3] + cost(i , 0 , 2)); // turn back and arrive at (0 , i)
        DP[i][2] = max(DP[i][2] , DP[i - 1][3] + cost(i , 0 , 2)); // turn back and arrive at (2 , i)
        DP[i][3] = max(DP[i][3] , max(DP[i - 1][0] , DP[i - 1][2]) + cost(i , 0 , 2)); // if we fill col i
        //for(int j = 0; j < 4; ++j)printf("DP[%d][%d] = %lld\n" , i , j ,DP[i][j]);
    }
    cout << DP[N][2] << endl;
}