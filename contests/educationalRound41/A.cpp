#include <bits/stdc++.h>
using namespace std;

int v[1005];

int main(){
    int N , M , ret = 0; 
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        int c; scanf("%d" , &c); ++v[c];
        int ok = 1;
        for(int j = 1; j <= N; ++j)if(!v[j])ok = 0;
        if(ok){
            ++ret;
            for(int j = 1; j <= N; ++j)--v[j];
        }
    }
    printf("%d\n" , ret);
}