#include <bits/stdc++.h>
#define INF 18889465931478580854784.0
using namespace std;
typedef long double ld;
typedef long long ll;

int N;
ll K;
ld f[55];
bool used[55];

int main(){
    scanf("%d %lld" , &N , &K);
    f[0] = f[1] = 1;
    for(int i = 2; i <= N; ++i){
        if(f[i - 1] > INF || f[i - 2] > INF)f[i] = INF;
        else{
            f[i] = f[i - 1] + f[i - 2];
            if(f[i] > INF)f[i] = INF;
        }
    }
    int j = 1;
    for(int i = 1; i <= N;){
        if(f[N - i] >= K){
            printf("%d " , j);
            ++j; ++i;
        }
        else{
            printf("%d %d " , j + 1 , j);
            K -= f[N - i];
            i += 2;
            j += 2;
        }
    }
    printf("\n");
}