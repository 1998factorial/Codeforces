#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int N;
int a[maxn];
int step[maxn][320];

int main(){
    int i , j;
    scanf("%d" , &N);
    for(i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    int block_size = sqrt(N);
    for(j = 1; j <= block_size; ++j){
        for(i = N; i >= 1; --i){
            int ni = i + a[i] + j;
            if(ni > N)step[i][j] = 1;
            else step[i][j] = step[ni][j] + 1;
            // printf("step[%d][%d] = %d\n" , i , j , step[i][j]);
        }
    }
    int Q;
    scanf("%d" , &Q);
    while(Q--){
        int p , k;
        scanf("%d %d" , &p , &k);
        if(k > block_size){
            // brute force
            int ans = 0;
            while(p <= N){
                p += a[p] + k;
                ++ans;
            }
            printf("%d\n" , ans);
        }
        else{
            printf("%d\n" , step[p][k]);
        }
    }
}