/*
    Dynamic programming , rating 2700

    DP[l][r][h] = maximal profit we can get from a[l..r] , where the tallest building is at most h
    DP[l][r][h] = max{DP[l][x - 1][h] + DP[x + 1][r][h] + h * h - cost}
    where cost is the total fees you need to pay for putting a building with height = h in [l , r]
    and the restriction [li , ri] must be fully covered in [l,r] , so that we are avoiding double counting
    O(N ^ 5)
*/
#include <bits/stdc++.h>
using namespace std;

int N , M , H;
int L[55] , R[55] , X[55] , C[55];
int DP[55][55][55];

int main(){
    cin >> N >> H >> M;
    for(int i = 1; i <= M; ++i){
        cin >> L[i] >> R[i] >> X[i] >> C[i];
    }
    for(int h = 1; h <= H; ++h){
        for(int len = 1; len <= N; ++len){
            for(int i = 1; i + len - 1 <= N; ++i){
                int j = i + len - 1;
                DP[i][j][h] = max(DP[i][j][h] , DP[i][j][h - 1]);
                for(int x = i; x <= j; ++x){ // try to build h on a[x]
                    int val = DP[i][x - 1][h] + DP[x + 1][j][h] + h * h;
                    for(int y = 1; y <= M; ++y){
                        if(i <= L[y] && R[y] <= j && X[y] < h && L[y] <= x && R[y] >= x){
                            val -= C[y];
                        }
                    }
                    DP[i][j][h] = max(DP[i][j][h] , val);
                }
            }
        }
    }
    cout << DP[1][N][H] << endl;
}
