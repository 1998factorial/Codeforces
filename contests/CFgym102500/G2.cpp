#include <bits/stdc++.h>
using namespace std;
#define MAXN 505
#define ID if (0)
#define double long double
 
int n, k;
double s[MAXN];
double prob[MAXN]; // logarithmic probability of a monster eating i monsters before it
 
// logarithmic probability
double choose(int n, int r) {
	double ans = 0;
	for (int i = 1; i <= n; i++) ans += logl(i);
	for (int i = 1; i <= r; i++) ans -= logl(i);
	for (int i = 1; i <= (n-r); i++) ans -= logl(i);
	return ans;
}
 
int main() {
	cin >> n >> k;
	double prob1 = choose(n-1, k-1) - choose(n, k);
	if (k == 1) {
		prob1 = -logl(n);
	}
	ID cout << expl(prob1) << endl;
	for (int i = 0; i <= (n-k); i++) {
		// prob[i] = choose(n-(i+2), (k-2)) / choose(n-1, k-1);
		prob[i] = choose(n-(i+2), (k-2)) - choose(n-1, k-1);
		ID printf("prob[%d] = %Lf\n", i, prob[i]);
	}
 
	for (int i = 0; i < n; i++) cin >> s[i];
	for (int i = 0; i < n; i++) {
		double cs = s[i]; // cumulative score
		double ans = 0;
		if (k == 1) {
			ans = expl(prob1+logl(100.0));
		} else {
			for (int j = 0; j <= (n-k); j++) {
				// let monster i "eat" the j monsters before it
				if (j) cs += s[((i-j)+n)%n];
				ID printf("eat(%d,%d) = %Lf\n", i, j, cs);
				ans += expl(prob[j]+prob1+logl(cs));
			}
		}
		printf("%.12Lf ", ans);
	}
	printf("\n");
}