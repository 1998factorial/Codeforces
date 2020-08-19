#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int t = 10;
    printf("%d\n" , t);
    while(t--){
        int N = 5 , S = 5;
        printf("%d %d\n" , N , S);
        for(int i = 1; i < N; ++i){
            printf("%d %d %d\n" , i , i + 1 , rand() % 10 + 1);
        }
    }
}