#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e2;
int main(){
    srand(time(NULL));
    int N = 10;
    int A = 1 , B = 6;
    printf("%d %d %d\n" , N , A , B);
    for(int i = 1; i <= N; ++i){
        printf("%d %d\n" , rand() % MOD + 1 , rand() % MOD + 1);
    }
}