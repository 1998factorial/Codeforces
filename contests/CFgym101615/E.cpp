#include <bits/stdc++.h>
using namespace std;
#define ID if (0)

// horizontal speed is constant
// assume takes 1s to cross 1m
// then will move up/down by x meters final

int n;
double xx;
double v0;
double l, r;
double v1;
double shift;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> xx >> v0;
	double prev = 0;
	for (int i = 1; i <= n; i++) {
		cin >> l >> r >> v1;
		shift += (r-l)*v1;
	}
	ID printf("shift = %lf, xx = %lf\n", shift, xx);

	double y = -(shift/xx);
	ID printf("y = %lf\n", y);
	double x2 = v0*v0-y*y;
	if (x2 <= 0) {
		cout << "Too hard" << endl;
		return 0;
	}
	double x = sqrt(x2);
	double t = xx / x;
	if (t > (xx/v0)*2) {
		cout << "Too hard" << endl;
		return 0;
	}

	printf("%.3lf\n", t);
}