#include <bits/stdc++.h>
using namespace std;

int main() {
    int t, n;
    scanf("%d " , &t);
    double pi = 3.14159265358979323846;
    while (t--) {
        scanf("%d" , &n);
        double r = 0.5 / sin(pi / (2 * n));
        double step = pi / n;
        double at = -pi / 4 + step / 2;
        double best = at;
        for (int i = 0; i < n; i++) {
    	    at = at + step;
    	    if (abs(at) < abs(best)) best = at;
        }
        printf("%.20lf\n" , r * cos(best) * 2);
    }
}
