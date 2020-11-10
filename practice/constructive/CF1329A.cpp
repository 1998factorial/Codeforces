/*
    Constructive
    When dealing constructive problem, always think about cases where it fails to give a solution
    In this problem, it is when l[1]+..+l[M] < N , or N - l[i] < i - 1
    first one means, we can not use M operations to fill all cells
    second one means, when we do ith operation, the at least one of the previous i - 1 colors will be overwritten.
    Now we have, l[1]+..+l[M] >= N , l[i] <= N - i + 1
    One easy way to ensure that each color will appear at least once is : p[i] = i
    But some cells might be left blank.
    we can also paint from right to left, being , p[i] = N - (l[i]+..+l[M]) + 1
    But this might go over the array as p[i] could be negative
    So we want something in the middle
    Each time, for p[i], the left most position that we can put is i, but as long as
    N - (l[i]+...+l[M]) + 1 >= i, we should let p[i] equals such as it gurantees we will not have any
    blank cells at the end, so p[i] = max(i , N - (l[i]+..+l[M]) + 1)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int l[maxn];
int N , M;

int main(){
    scanf("%d %d" , &N , &M);
    vector<ii> a;
    ll sum = 0;
    for(int i = 1; i <= M; ++i){
        scanf("%d" , &l[i]);
    }
    for(int i = 1; i <= M; ++i){
        if(N - l[i] < i - 1){
            printf("-1\n");
            return 0;
        }
        sum += l[i];
    }
    if(sum < N){
        printf("-1\n");
        return 0;
    }
    for(int i = 1; i <= M; ++i){
        printf("%lld " , max((ll)i , (ll)N - sum + 1));
        sum -= l[i];
    }
    printf("\n");
}
