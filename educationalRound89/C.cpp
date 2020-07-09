#include <bits/stdc++.h>
using namespace std;

char s[50][50];

int main(){
    int t; cin >> t;
    while(t--){
        int N , M;
        cin >> N >> M;
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= M; ++j){
                cin >> s[i][j];
            }
        }
        vector<vector<int>> cnt(N + M + 100 , vector<int>(2));
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= M; ++j){
                if(abs(i - 1) + abs(j - 1) == abs(i - N) + abs(j - M)){
                    continue;
                }
                ++cnt[min(abs(i - 1) + abs(j - 1) , abs(i - N) + abs(j - M))][s[i][j] - '0'];
            }
        }
        int ans = 0;
        for(int i = 0; i <= N + M + 10; ++i){

            ans += min(cnt[i][0] , cnt[i][1]);
        }
        cout << ans << endl;
    }
}
