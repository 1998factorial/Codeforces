#include <bits/stdc++.h>
using namespace std;
int k , r;

int main(){
    cin >> k >> r;
    int n = (1 << k);
    double ret = 0;
    for(int i = 1; i <= k; ++i){
        int v = (1 << i) - 1;
        if(v > n - r)break;
        double val = 1;
        for(int j = 0; j < v; ++j){
            val *= (double)(n - r - j) / (n - j - 1);
        }
        ret += val;
    }
    printf("%.5lf\n" , ret);
}