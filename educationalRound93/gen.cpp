#include <bits/stdc++.h>
using namespace std;

int main(){
    int N = 1e6;
    printf("%d\n" , N);
    for(int i = 1; i <= N; ++i){
        printf("%d" , (i % 3 == 0) ? 0 : 1);
    }
}