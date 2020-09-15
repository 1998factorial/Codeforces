//#pragma GCC optimize("O0")
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int N;
double v[maxn] , w[maxn];
double S1[maxn] , S2[maxn];
double vv[maxn] , ww[maxn];
// x = ((w + v) +- sqrt((w + v)^2 - 4v)) / 2
// y = v / x
int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%lf" , &v[i]);
    for(int i = 1; i <= N; ++i)scanf("%lf" , &w[i]);
    S1[1] = ((w[1] + v[1]) + sqrt(fabs((w[1] + v[1]) * (w[1] + v[1]) - 4.0 * v[1]))) / 2;
    S2[1] = ((w[1] + v[1]) - sqrt(fabs((w[1] + v[1]) * (w[1] + v[1]) - 4.0 * v[1]))) / 2;
    //printf("S1[%d] = %lf\n" ,1 , S1[1]);
    //printf("S2[%d] = %lf\n" ,1 , S2[1]);
    for(int i = 2; i <= N; ++i){
        vv[i] = v[i] + S1[i - 1] * S2[i - 1];
        ww[i] = w[i] + S1[i - 1] + S2[i - 1] - S1[i - 1] * S2[i - 1];
        S1[i] = ((ww[i] + vv[i]) + sqrt(fabs((ww[i] + vv[i]) * (ww[i] + vv[i]) - 4.0 * vv[i]))) / 2;
        S2[i] = ((ww[i] + vv[i]) - sqrt(fabs((ww[i] + vv[i]) * (ww[i] + vv[i]) - 4.0 * vv[i]))) / 2;
        //printf("S1[%d] = %lf\n" ,i , S1[i]);
        //printf("S2[%d] = %lf\n" ,i , S2[i]);
    }
    for(int i = 1; i <= N; ++i){
        printf("%lf " , S1[i] - S1[i - 1]);
    }printf("\n");
    for(int i = 1; i <= N; ++i){
        printf("%lf " , S2[i] - S2[i - 1]);
    }printf("\n");
}
/*
v[x] = P(max(a , b) = x)
w[x] = P(min(a , b) = x)
a[x] = P(a = x)
b[x] = P(b = x)
v[x] = sum{a[x] * b[y] | y < x} + sum{a[y] * b[x] | y < x} + a[x] * b[x]
w[x] = sum{a[x] * b[y] | y > x} + sum{a[y] * b[x] | y > x} + a[x] * b[x]
v[x] = (S1[x] - S1[x - 1]) * S2[x - 1] + (S2[x] - S2[x - 1]) * S1[x - 1] + (S1[x] - S1[x - 1]) * (S2[x] - S2[x - 1])
w[x] = (S1[x] - S1[x - 1]) * (S2[N] - S2[x]) + (S2[x] - S2[x - 1]) * (S1[N] - S1[x]) + (S1[x] - S1[x - 1]) * (S2[x] - S2[x - 1])
v[x] = S1[x] * S2[x] - S1[x - 1] * S2[x - 1]
(1) v[x] + S1[x - 1] * S2[x - 1] = S1[x] * S2[x]
w[x] = (S1[x] - S1[x - 1]) + (S2[x] - S2[x - 1]) - v[x]
vv[x] = v[x] + S1[x - 1] * S2[x - 1] = S1[x] * S2[x]
w[x] + S1[x - 1] + S2[x - 1] = S1[x] + S2[x] - v[x] = 
= S1[x] + S2[x] - S1[x] * S2[x] + S1[x - 1] * S2[x - 1]
w[x] + S1[x - 1] + S2[x - 1] - S1[x - 1] * S2[x - 1] = S1[x] + S2[x] - S1[x] * S2[x]
vv[x] = v[x] - S1[x - 1] * S2[x - 1] = S1[x] * S2[x]
ww[x] = w[x] + S1[x - 1] + S2[x - 1] - S1[x - 1] * S2[x - 1] = S1[x] + S2[x] - S1[x] * S2[x]
vv[x] = S1[x] * S2[x]
ww[x] = S1[x] + S2[x] - S1[x] * S2[x]
v[1] = S1[1] * S2[1]
w[1] = S1[1] + S2[1] - S1[1] * S2[1]
v[1] = S1[1] * S2[1]
w[1] = S1[1] + S2[1] - S1[1] * S2[1]
v[2] = S2[2] * S1[2] - S1[1] * S2[2]
w[2] = S
x = ((w + v) +- sqrt((w + v)^2 - 4v)) / 2
y = v / x
v[x] + w[x] = a[x] + b[x]
f[x] = v[x] + w[x]
b[x] = f[x] - a[x]
a[x]
S1[i] = a[1] + ... + a[i]
S2[i] = b[1] + ... + b[i]
f[1] + .. + f[N] = 2
*/
