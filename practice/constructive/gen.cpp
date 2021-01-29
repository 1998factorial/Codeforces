#include <bits/stdc++.h>
using namespace std;
int main(){
    srand(time(NULL));
    int N = 1e5 , M = N - 1;
    printf("%d %d" , N , M);
    for(int i = 1; i <= M; ++i){
        printf("1 %d\n" , i + 1);
    }
}