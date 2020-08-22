#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9;
int main(){
    srand(time(NULL));
    int N = 2000 , K = 50;
    printf("%d %d\n" , N , K);
    for(int i = 1; i <= N; ++i){
        printf("%d " , rand() % mod + 1);
    }
    printf("\n");
    int Q = 10;
    printf("%d\n" , Q);
    for(int i = 1; i <= Q; ++i){
        int q , L , R , d;
        q = rand() % mod + 1;
        L = 1 , R = N;
        d = 40;
        printf("2 %d %d %d %d\n" , q , L , R , d);
    }
}