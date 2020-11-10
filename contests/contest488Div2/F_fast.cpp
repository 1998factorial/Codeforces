#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef long long ll;
const double eps = 1e-6;
const double INF = 1e12;
int N;
double a[55] , b[55] , DP[55][55];
// DP[i][j] = min total cost for first i groups, with j free spot 

bool check(double mid){
    ID printf("checking %lf\n" , mid);
    map<int , vector<double>> group;
    for(int i = 1; i <= N; ++i){
        group[(int)a[i]].push_back(a[i] - mid * b[i]);
    }
    vector<vector<double>> vec;
    for(auto& e : group){
        sort(e.y.begin() , e.y.end());
        reverse(e.y.begin() , e.y.end());
        vec.push_back(e.y);
    }
    reverse(vec.begin() , vec.end());
    int n = vec.size();
    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= N; ++j){
            DP[i][j] = INF;
        }
    }
    DP[0][0] = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j <= N; ++j){
            if(DP[i][j] >= INF)continue;
            double go_second = 0 , go_first = 0;
            int sz = vec[i].size();
            for(int k = 0; k < sz; ++k){
                go_first += vec[i][k];
            }
            DP[i + 1][j + sz] = min(DP[i + 1][j + sz] , DP[i][j] + go_first);
            for(int k = 0; k < sz && k + 1 <= j; ++k){
                go_second += vec[i][k];
                DP[i + 1][j + sz - 2 * (k + 1)] = min(DP[i + 1][j + sz - 2 * (k + 1)] , DP[i][j] + go_first - go_second);               
            }
        }
    }
    double ret = INF;
    for(int i = 0; i <= N; ++i){
        ret = min(ret , DP[n][i]);
    }
    return ret <= 0;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%lf" , &a[i]);
    for(int i = 1; i <= N; ++i)scanf("%lf" , &b[i]);
    double L = 0 , R = INF;
    while(R - L > eps){
        double mid = (L + R) / 2;
        if(check(mid)){
            R = mid;
        }
        else{
            L = mid;
        }
    }
    L *= 1000;
    ll ret = ceil(L);
    printf("%lld\n" , ret);
}