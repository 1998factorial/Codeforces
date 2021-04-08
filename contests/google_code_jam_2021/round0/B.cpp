#include <bits/stdc++.h>
using namespace std;
const int inf = 1e8;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    for(int kase = 1; kase <= t; ++kase){
        cout << "Case #" << kase << ": ";
        int X , Y;
        cin >> X >> Y;
        string a;
        cin >> a;
        int N = a.size();
        vector<vector<int>> dp(N , vector<int>(2 , inf));
        // 0 : C , 1 : J
        // CJ -> X , JC -> Y
        if(a[0] == 'C')dp[0][0] = 0;
        if(a[0] == 'J')dp[0][1] = 0;
        if(a[0] == '?')dp[0][0] = dp[0][1] = 0;
        for(int i = 1; i < N; ++i){
            if(a[i] == 'C'){
                dp[i][0] = min(dp[i - 1][0] , dp[i - 1][1] + Y);
            }
            if(a[i] == 'J'){
                dp[i][1] = min(dp[i - 1][0] + X , dp[i - 1][1]);
            }
            if(a[i] == '?'){
                dp[i][0] = min(dp[i - 1][0] , dp[i - 1][1] + Y);
                dp[i][1] = min(dp[i - 1][0] + X , dp[i - 1][1]);
            }
        }   
        cout << min(dp[N - 1][0] , dp[N - 1][1]) << endl;
    }
}