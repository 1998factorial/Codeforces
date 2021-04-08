#include <bits/stdc++.h>
using namespace std;

int main(){
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    //cout.tie(NULL);
    int t;
    //cin >> t;
    scanf("%d" , &t);
    while(t--){
        int N;
        //cin >> N;
        scanf("%d" , &N);
        vector<double> xs(N) , ys(N);
        int xn = 0 , yn = 0;
        for(int i = 0; i < 2 * N; ++i){
            double x , y;
            scanf("%lf %lf" , &x , &y);
            //cin >> x >> y;
            if(x == 0)ys[yn++] = y;
            if(y == 0)xs[xn++] = x;
        }
        sort(xs.begin() , xs.end() , [&](double l , double r){
            return abs(l) < abs(r);
        });
        sort(ys.begin() , ys.end() , [&](double l , double r){
            return abs(l) < abs(r);
        });
        double ans = 0;
        for(int i = 0; i < N; ++i){
            ans += sqrt(xs[i] * xs[i] + ys[i] * ys[i]);
        }
        printf("%.15lf\n" , ans);
        //cout << setprecision(18) << ans << endl;
    }
}