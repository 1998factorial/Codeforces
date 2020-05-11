#include <bits/stdc++.h>
using namespace std;


int N , M;
int row[105] , col[105];
int a[105][105];

int main(){
    cin >> N >> M;
    for(int i = 1; i <= N; ++i)cin >> row[i];
    for(int i = 1; i <= M; ++i)cin >> col[i];
    int S1 = 0 , S2 = 0;
    for(int i = 1; i <= N; ++i){
        S1 ^= row[i];
    }
    for(int i = 1; i <= M; ++i){
        S2 ^= col[i];
    }
    if(S1 != S2){
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    a[1][1] = S1 ^ col[1] ^ row[1];
    for(int i = 2; i <= N; ++i){
        a[i][1] = row[i];
    }
    for(int i = 2; i <= M; ++i){
        a[1][i] = col[i];
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
