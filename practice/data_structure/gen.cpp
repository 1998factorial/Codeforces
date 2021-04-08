#include <bits/stdc++.h>
using namespace std;
int main(){
    srand(time(NULL));
    int N = 2e5 , M = 2e4 , K = 10;
    printf("%d %d %d" , N , M , K);
    for(int i = 1; i <= N; ++i){
        int v = rand() % K;
        printf("%c" , 'a' + v);
    }
    for(int i = 1; i <= M; ++i){
        if(i & 1){
            int v = rand() % 10;
            printf("1 %d %d b\n" , 500 , 500 + v);
        }   
        else{
            printf("2 abcdefghij\n");
        }
    }
}