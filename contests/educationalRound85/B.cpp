/*
    Greedy
    sort in reverse order
    easy
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;


int main(){
    int t; scanf("%d" , &t);
    while(t--){
        int N;
        double x;
        scanf("%d %lf" , &N , &x);
        vector<double> a;
        for(int i = 1; i <= N; ++i){
            double y; scanf("%lf" , &y); a.push_back(y);
        }
        sort(a.begin() , a.end());
        reverse(a.begin() , a.end());
        double sum = 0;
        int ret = 0;
        for(int i = 0; i < N; ++i){
            sum += a[i];
            if(sum / (i + 1) >= x){
                ret = i + 1;
            }
        }
        printf("%d\n" , ret);
    }
}
