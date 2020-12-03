#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int N = 1000 , M = 1000 , K = 40 , Q = 1e5;
    printf("%d %d %d\n" , N , M , K);
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            printf("%d " , (i + j) % 40 + 1);
        }
        printf("\n");
    }
    for(int i = 1; i <= Q; ++i){
        printf("%d %d %d %d\n" , rand() % N + 1 , rand() % M + 1 , rand() % N + 1 , rand() % M + 1);
    }
}
