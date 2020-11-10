#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int N , a[maxn];

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d"  , &a[i]);
    }
    double ans = 0;
    for(int i = 1; i <= N; ++i){
        double v = 0;
        for(int l = 1; l <= i; ++l){
            double x = 0;
            for(int j = 1; j < l; ++j)x += a[j] > a[i];
            for(int j = l; j <= i; ++j)if(a[j] > a[i])x += 0.5;
            for(int r = i; r <= N; ++r){
                double y = 0;
                for(int j = r + 1; j <= N; ++j)y += a[j] > a[i];
                for(int j = i; j <= r; ++j)if(a[j] > a[i])y += 0.5;
                v += x + y;
            }
        }
        v /= i;
        v /= N - i + 1;
        ans += v;
    }
    printf("%lf\n" , ans);
}