#include <bits/stdc++.h>
using namespace std;


const int mod = 1e9;

int main(){
    srand(time(NULL));
    int N = 5000, M = 5000;
    printf("%d %d\n" , N , M);
    for(int i = 1; i <= N; ++i){
        printf("%d " , rand() % mod + 1);
    }
    printf("\n");
    for(int i = 1; i <= M; ++i){
        printf("%d %d\n" , rand() % mod + 1 , rand() % 5000 + 1);
    }
}