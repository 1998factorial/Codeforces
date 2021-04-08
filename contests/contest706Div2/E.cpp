#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int N , M;
        cin >> N >> M;
        vector<vector<char>> s(N , vector<char>(M));
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                cin >> s[i][j];
            }
        }
        if(N == 1){
            for(int i = 0; i < M; ++i){
                cout << "X";
            }
            cout << endl;
            continue;
        }
        if(M == 1){
            for(int i = 0; i < N; ++i){
                cout << "X" << endl;
            }
            continue;
        }
        // no two cells touch 
        // so if we put X on all row[0] , row[3] , row[6] , ...
        // no cells on row[i + 1] , row[i + 2] touch (by edge or conner)
        for(int i = 0; i < N; i += 3){
            for(int j = 0; j < M; ++j){
                s[i][j] = 'X';
            }
            if(i + 1 < N && s[i + 1][1] == 'X'){
                // we can make col 1 brige connecting col[i] and col[i - 3]
                // as col[0] and col[3] must be cleared
                if(i + 1 < N)s[i + 1][1] = 'X';
                if(i + 2 < N)s[i + 2][1] = 'X';
                continue;
            }
            if(i + 2 < N && s[i + 2][1] == 'X'){
                // we can make col 1 brige connecting col[i] and col[i - 3]
                // as col[0] and col[3] must be cleared
                if(i + 1 < N)s[i + 1][1] = 'X';
                if(i + 2 < N)s[i + 2][1] = 'X';
                continue;
            }
            // if we make col[3] bridge, it might conflict with col[4]
            // but if we make col[0] bridge, it will conflict no one
            if(i + 1 < N)s[i + 1][0] = 'X';
            if(i + 2 < N)s[i + 2][0] = 'X';
        }
        if(N % 3 == 0){
            // edge case, where we might have some isolated X on last row
            for(int j = 0; j < M; ++j){
                if(s[N - 1][j] == 'X'){
                    s[N - 2][j] = 'X';
                }
            }
        }
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                cout << s[i][j];
            }
            cout << endl;
        }
    }
}