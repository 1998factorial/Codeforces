#include <bits/stdc++.h>
using namespace std;
int DP[1 << 20] , N;
char s[1000005];
// find substring a and b, st a and b do not contain same character
// and our goal is to maximise |a| + |b| 
int main(){
    scanf("%s" , (s + 1));
    N = strlen(s + 1);
    for(int i = 1; i <= N; ++i){
        int mask = 0;
        for(int j = i; j <= N; ++j){
            int v = s[j] - 'a';
            if((1 << v) & mask)break;
            mask |= (1 << v);
            DP[mask] = j - i + 1;
        }
    }
    for(int mask = 0; mask < (1 << 20); ++mask){
        for(int i = 0; i < 20; ++i){
            if(mask & (1 << i)){
                DP[mask] = max(DP[mask] , DP[mask ^ (1 << i)]);
            }
        }
    }
    int ret = 0;
    for(int mask = 0; mask < (1 << 20); ++mask){
        ret = max(ret , DP[mask] + DP[((1 << 20) - 1) ^ mask]);
    }
    printf("%d\n" , ret);
}