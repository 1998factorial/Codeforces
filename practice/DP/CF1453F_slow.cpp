#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
int a[3005] , N;

int solve(int i , int j){
    if(i <= 1)return 0;
    vector<int> pos;
    for(int k = 1; k < i; ++k){
        if(a[k] + k >= i && a[k] + k < j)pos.push_back(k);
    }
    int ret = INF;
    for(int k : pos){
        ret = min(ret , solve(k , i) + (int)pos.size() - 1);
    }
    return ret;
}

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        scanf("%d" , &N);
        for(int i = 1; i <= N; ++i){
            scanf("%d" , &a[i]);
        }
        a[N + 1] = INF;
        printf("%d\n" , solve(N , N + 1));
    }
}