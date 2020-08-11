#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int N , K; 
    N = 10000;
    printf("%d\n" , N);
    for(int i = 1; i <= N; ++i)printf("%d " , rand() % 200000 + 1);
    printf("\n");
    for(int i = 1; i < N; ++i){
        printf("%d %d\n" , i , i + 1);
    }
}