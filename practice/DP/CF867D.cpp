#include <bits/stdc++.h>
using namespace std;

int N , R;
double DP[55][5150] , p[55] , F[55] , S[55];

// DP[i][j] = minimal expected amount of time to complete
// the game if we have done first i rounds and used j amount of time
// in total

// DP[i][j] = min(DP[1][0] , p[i] * (DP[i + 1][j + F[i]] + F[i]) + (1 - p[i]) * (DP[i + 1][j + S[i]] + S[i]));

bool check(double v){
    // assume *DP[1][0] = v
    for(int i = 1; i <= N + 1; ++i){
        for(int j = R + 1; j < 5150; ++j){
            DP[i][j] = v; // we have to restart in these cases
        }
    }
    for(int i = N; i >= 1; --i){
        for(int j = 0; j <= R; ++j){
            double ts = (DP[i + 1][j + (int)F[i]] + F[i]) * p[i];
            double tf = (DP[i + 1][j + (int)S[i]] + S[i]) * (1.0 - p[i]);
            DP[i][j] = min(v , ts + tf);
        }
    }
    // if DP[1][0] < v then we know *DP[1][0] < v
    return DP[1][0] < v;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> R;
    for(int i = 1; i <= N; ++i){
        cin >> F[i] >> S[i] >> p[i];
        p[i] /= 100.0;
    }
    double l = 0 , r = 1000000000.0;
    for(int i = 1; i <= 100; ++i){
        double mid = (l + r) / 2.0;
        if(check(mid)){
            r = mid;
        }
        else{
            l = mid;
        }
    }
    cout << setprecision(12) << (l + r) / 2 << endl;
}