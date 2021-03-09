#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        int N , K , M;
        scanf("%d %d %d" , &N , &K , &M);
        vector<int> good(N + 1);
        for(int i = 1; i <= M; ++i){
            int x;
            scanf("%d" , &x);
            good[x] = 1;
        }
        if((N - M) % (K - 1) != 0){
            printf("NO\n");
            continue;
        }
        int ok = 0 , nerase = 0;
        // as long as the last operation is on some good number
        // we do not care about where the rest of the operations are on
        for(int i = 1; i <= N && !ok; ++i){
            if(!good[i])++nerase;
            else if(nerase >= K / 2 && (N - M - nerase) >= K / 2)ok = 1;
        }
        printf("%s" , ok ? "YES\n" : "NO\n");
    }
}