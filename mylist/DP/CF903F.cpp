/*
    Dynamic programming on broken profil , rating 2200
    let DP[i][s] = the minimal cost to place k x k squares st
    col[0] .. col[i - 3] are all dot , col[i - 2] , col[i - 1] , col[i] have state s
    then we have very finicky implementation to go
*/
#include <bits/stdc++.h>
#define ID 0
using namespace std;

const int maxn = 1010;
const int INF = 1e9 + 10;

char s[4][maxn];
int a[5];
vector<int> D[5];
int DP[maxn][1 << 12];
int col[maxn]; // use bitmask to compress the ith col
int N;

void show(int v){
    for(int i = 0; i < 12; ++i){
        if((1 << i) & v)cout << 1;
        else cout << 0;
        if(i % 4 == 3)cout << endl;
    }
    cout << endl;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= 4; ++i)scanf("%d" , &a[i]);
    for(int i = 0; i < 4; ++i)scanf("%s" , s[i]);
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < 4; ++j){
            col[i] <<= 1;
            if(s[j][i] == '*')++col[i];
        }
        if(ID)printf("col[%d] = %d\n" , i , col[i]);
    }
    for(int i = 0; i < 3; ++i){ // get all possible single paste of d by d square
        for(int j = 0; j < 4; ++j){
            // top left conner
            for(int d = 1; d <= 4 && i + d - 1 < 3 && j + d - 1 < 4; ++d){
                int mask = (1 << 12) - 1;
                for(int x = i; x <= i + d - 1; ++x){
                    for(int y = j; y <= j + d - 1; ++y){
                        mask ^= 1 << (4 * x + y);
                    }
                }
                D[d].push_back(mask);
            }
        }
    }
    if(ID)for(int i = 1; i <= 4; ++i){
        cout << "i = " << i << endl;
        for(int j : D[i]){
            show(j);
            cout << endl;
        }
    }
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < (1 << 12); ++j){
            DP[i][j] = INF;
        }
    }
    DP[2][col[2] | col[1] << 4 | col[0] << 8] = 0;
    for(int i = 2; i < N; ++i){
        for(int j = (1 << 12) - 1; ~j; --j){
            if(DP[i][j] >= INF)continue;
            if(j < (1 << 8)){ // the i - 2 th col is all dots , so we can ignore it
                int& val = DP[i + 1][j << 4 | col[i + 1]]; // can just shift one col to i + 1
                val = min(val , DP[i][j]);
            }
            DP[i + 1][0] = min(DP[i + 1][0] , DP[i][j] + a[4]); // cover col[i - 2 .. i + 1]
            for(int d = 1; d <= 3; ++d){
                for(int s : D[d]){
                    int nj = j & s;
                    int& val = DP[i][nj];
                    val = min(val , DP[i][j] + a[d]);
                }
            }
        }
    }
    if(ID)for(int i = 2; i < N; ++i){
        for(int j = (1 << 12) - 1; ~j; --j){
            if(DP[i][j] < INF)printf("DP[%d][%d] = %d\n" , i , j , DP[i][j]);
        }
    }
    printf("%d\n" , DP[N - 1][0]); // the minimal cost to make all dots
}
