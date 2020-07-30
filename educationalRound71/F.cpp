/*
    if x > sqrt(N) , query can be done in O(N / sqrt(N)) , just brute force sum of all a[x* k + y]
    else , we can store the answer by : sum[x][y] = sum of all a[i] st i % x = y

    for update , for each i <= sqrt(N) , we do sum[i][x % i] += y and a[x] += y
    this can be done in O(sqrt(N))
    so overrall the time complexity is O(q * sqrt(N))
*/
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

const int maxn = 711;

int sum[maxn][maxn];
int a[maxn * maxn];
int q;
int block_sz;
int t , x , y;

int main() {
    int block_sz = sqrt(500000) , i , ret;
    scanf("%d" , &q);
    while(q--){
        scanf("%d %d %d" , &t , &x , &y);
        if(t == 1){
            a[x] += y;
            for(i = 1; i <= block_sz; ++i){
                sum[i][x % i] += y;
            }
        }
        else{
            if(x <= block_sz){
                printf("%d\n" , sum[x][y]);
            }
            else{
                ret = 0;
                for(; y <= 500000; y += x){
                    ret += a[y];
                }
                printf("%d\n" , ret);
            }
        }
    }
}