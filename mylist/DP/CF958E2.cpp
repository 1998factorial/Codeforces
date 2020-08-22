/*
    We only take the smallest min(3K , N - 1) differences
    this can be done in O(K * min(K , N)) with DP
*/
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int , int> ii;
const int maxn = 500005;
const int INF = 1e9;
int K , N;
int t[maxn];
int diff[maxn];
int tmp[maxn];
int DP[2][5005][2];
vector<ii> D;

int main(){
    scanf("%d %d" , &K , &N);
    int up = min(3 * K , N - 1);
    for(int i = 1; i <= N; ++i)scanf("%d" , &t[i]);
    sort(t + 1 , t + 1 + N);
    for(int i = 1; i < N; ++i){
        diff[i] = t[i + 1] - t[i];
        tmp[i] = diff[i];
    }
    sort(tmp + 1 , tmp + N);
    set<int> vals;
    for(int i = 1; i <= up; ++i){
        vals.insert(tmp[i]);
    }
    D.emplace_back(0 , 0);
    for(int i = 1; i < N; ++i){
        if(vals.find(diff[i]) != vals.end()){
            D.emplace_back(diff[i] , i);
        }
    }
    for(int i : {0 , 1}){
        for(int j = 0; j <= K; ++j){
            for(int k : {0 , 1}){
                DP[i][j][k] = INF;
            }
        }
    }
    DP[0][0][0] = DP[0][0][1] = 0;
    int sz = D.size() - 1;
    for(int i = 1; i <= sz; ++i){
        //printf("D[%d] = %d , %d\n" , i , D[i].x , D[i].y);
        int ci = i % 2;
        int pi = (i - 1) % 2;
        for(int j = 0; j <= K; ++j){
            DP[ci][j][0] = min(DP[pi][j][0] , DP[pi][j][1]);
            if(j)DP[ci][j][1] = min(DP[ci][j][1] , DP[pi][j - 1][0] + D[i].x);
            if(j && D[i].y != D[i - 1].y + 1){
                DP[ci][j][1] = min(DP[ci][j][1] , DP[pi][j - 1][1] + D[i].x);
            }
            /*for(int k : {0 , 1}){
                if(DP[ci][j][k] < INF)printf("DP[%d][%d][%d] = %d\n" , i , j , k , DP[ci][j][k]);
            }*/
        }
    }
    printf("%d\n" , min(DP[sz % 2][K][0] , DP[sz % 2][K][1]));
}