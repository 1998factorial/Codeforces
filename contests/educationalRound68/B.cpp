#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        int N , M;
        cin >> N >> M;
        vector<vector<char>> a(N + 1 , vector<char>(M + 1));
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= M; ++j){
                cin >> a[i][j];
            }
        }
        vector<int> row(N + 1) , col(M + 1);
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= M; ++j){
                row[i] += a[i][j] == '.';
            }
        }
        for(int j = 1; j <= M; ++j){
            int cnt = 0;
            for(int i = 1; i <= N; ++i){
                col[j] += a[i][j] == '.';
            }
        }
        int tot = N * M;
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= M; ++j){
                int cnt = row[i] + col[j];
                if(a[i][j] == '.')--cnt;
                tot = min(tot , cnt);
            }
        }
        cout << tot << endl;
    }
}
