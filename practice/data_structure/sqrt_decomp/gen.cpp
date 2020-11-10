#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int N = 1e5, K = 100;
    printf("%d %d" , N , K);
    for(int i = 1; i <= N; ++i){
        printf("%d " , rand() % N + 1);
    }
    printf("\n");
}