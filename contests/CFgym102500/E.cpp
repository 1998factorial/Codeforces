#include <bits/stdc++.h>
#define MAX_SIZE 5
typedef long long ll;
using namespace std;
const double eps = 1e-9;
 
double a[MAX_SIZE];
double target;
 
int sgn(double x) {
    if (fabs(x) <= eps) return 0;
    if (x > 0) return 1;
    return -1;
}
 
bool check(double val) {
    vector<double> score;
    for (int i = 0 ; i < 4; ++i) score.push_back(a[i]);
    score.push_back(val);
    sort(score.begin(), score.end());
    double avg = (score[1] + score[2] + score[3]) / 3;
    if (sgn(target - avg) >= 0) return true;
    return false;
}
 
int main() {
    scanf("%lf%lf%lf%lf", &a[0], &a[1], &a[2], &a[3]);
    scanf("%lf", &target);
    double ans = 0.0;
    for (double j = 1.00; sgn(j - 20.10) <= 0; j = j + 0.01) {
        if (check(j)) {
            ans = j;
        }
    }
 
    if (ans == 0.0) {
        printf("impossible\n");
        return 0;
    }
 
    if (sgn(ans - 20.01) >= 0) {
        printf("infinite\n");
        return 0;
    }
 
    printf("%.2lf\n", ans);
    return 0;
}