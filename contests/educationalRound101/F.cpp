#include <bits/stdc++.h>
using namespace std;
// say we use t chains
// it is always optimal to attach the mid point of a chain to some white vertice
// it is always optimal to use the longest t chains
const int maxn = 2e5 + 10;
int cnt[maxn * 5] , l[maxn] , N , K;
// cnt[d] = current number of white vertices at depth d
int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &l[i]);
    }
    sort(l + 1 , l + 1 + N);
    reverse(l + 1 , l + 1 + N);
    cnt[0] = 1; cnt[1] = -1;
    int nw = 0;
    for(int d = 0 , t = 1; d < maxn; ++d){
        nw += cnt[d];
        cnt[d + 1] += cnt[d];
        if(nw + cnt[d + 1] >= K){
            printf("%d\n" , d + 1);
            return 0;
        }
        while(t <= N && cnt[d]){
            // attach chain[t]'s mid point to current highest white point
            int L = l[t] / 2 , R = (l[t] - 1) / 2;
            cnt[d + 2] += 2;
            cnt[d + 2 + L]--;
            cnt[d + 2 + R]--;
            ++t;
            --nw;
            --cnt[d];
        }
    }
    printf("-1\n");
}