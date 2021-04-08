#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int N , K;
        cin >> N >> K;
        string a;
        cin >> a;
        vector<int> pos[K];
        vector<vector<int>> cnt(K , vector<int> (2));
        for(int i = 0; i < N; ++i){
            pos[i % K].push_back(a[i] - '0');
            ++cnt[i % K][a[i] - '0'];
        }
        int sum = 0;
        for(int i = 0; i < K; ++i){
            sum += cnt[i][1];
        }
        int ret = sum;
        for(int i = 0; i < K; ++i){
            int m = pos[i].size();
            vector<int> dp(m , m) , pre(m);
            for(int j = 0; j < m; ++j){
                pre[j] = pos[i][j];
                if(j > 0)pre[j] += pre[j - 1];
            }
            for(int j = 0; j < m; ++j){
                if(j == 0){
                    dp[j] = (int)(pos[i][j] != 1);
                }
                else{
                    dp[j] = pre[j - 1] + (int)(pos[i][j] != 1);
                    dp[j] = min(dp[j] , dp[j - 1] + (int)(pos[i][j] != 1));
                }
                ret = min(ret , dp[j] - cnt[i][1] + pre[m - 1] - pre[j] + sum);
            }
        }
        cout << ret << endl;
    }
}