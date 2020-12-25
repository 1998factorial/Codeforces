#include <bits/stdc++.h>
using namespace std;

vector<double> a[5];

int main(){
    int t;
    double v;
    while(1){
        cin >> t >> v;
        if(t == -1)break;
        a[t].push_back(v);
    }
    double base = 0 , up = 0;
    for(int i = 1; i <= 4; ++i){
        for(double& x : a[i]){
            base += (double)i * 100;
            up += (double)i * x;
        }
    }
    printf("%.5lf\n" , up / base);
}