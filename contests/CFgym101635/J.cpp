#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> A[3] , B[3];
ll sa[3] , sb[3] , ans[3];
int N;
int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        int x;
        scanf("%d" , &x);
        A[i % 3].push_back(x);
        sa[i % 3] += x;
    }
    for(int i = 1; i <= N; ++i){
        int x;
        scanf("%d" , &x);
        B[i % 3].push_back(x);
        sb[i % 3] += x;
    }
    for(int i = 0; i < 3; ++i){
        for(int x : A[i]){
            for(int j = 0; j < 3; ++j){
                ans[(i + j) % 3] += sb[j] * x;
            }
        }
    }
    printf("%lld %lld %lld\n" , ans[0] , ans[1] , ans[2]);
}