#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 200111
typedef long long ll;
const ll INF = 1e18;
int N, M, K;
int x, y;
int a[MAX_SIZE], b[MAX_SIZE];
vector<int> ret;
bool good[MAX_SIZE];
int mp[MAX_SIZE];


int main() {
    int i, j;
    scanf("%d %d", &N, &M);
    scanf("%d %d %d" , &x , &K , &y);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= M; ++i) scanf("%d", &b[i]);
    ret.push_back(0);
    for (i = 1, j = 1; i <= M; ++i) {
        while (j <= N && a[j] != b[i]) {
            mp[j] = i - 1;
            ++j;
        }
        if (j == N + 1) {
            printf("-1\n");
            return 0;
        }
        ret.push_back(j);
        good[j] = 1;
        mp[j] = i;
    }
    for(; j <= N; ++j)mp[j] = M;
    for(int i = 1; i <= N; ++i){
        printf("mp[%d] = %d\n" , i , mp[i]);
    }


    /*
    DP[i] = min : convert a[1 ... i] -> b[1 .. j]   
    if a[i] == good
        DP[i] = DP[i - 1]
    else
        if(a[i - K + 1 ... i] all not good) // use operation 1
            DP[i] = min(DP[i] , DP[i - K] + x);
        if(a[i] < a[i - 1]) // use operation 2
            DP[i] = min(DP[i] , DP[i - 1] + x)
        else // left with  a[1 ... i - 2] + a[i]
            if(b[k] > a[i])DP[i] = min(DP[i - 2] + 2 * x , DP[i])


    DP[i - 2] : min convert a[1 ... i] -> b[1 .. k]
    */
    
}   