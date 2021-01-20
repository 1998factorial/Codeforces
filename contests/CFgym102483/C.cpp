#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
#define PI 3.1415926535897
#define double long double
#define dd pair<double, double>
#define x first
#define y second
#define EPS 1e-9
#define ID if (0)
 
int n, a, b;
vector<int> e[MAXN];
int cc[MAXN];
double ax[MAXN];
double ay[MAXN];
 
void dfs(int at, int prev) {
	cc[at] = 1;
	for (int next : e[at]) {
		if (next == prev) continue;
		dfs(next, at);
		cc[at] += cc[next];
	}
}
 
// finds child coordinate for a node at (x,y)
// such it is on the line (angle) from the origin
// further from origin than (x,y)
// and has euclidian distance eq to 1 to (x,y)
dd find_child(double x, double y, double angle) {
	double ca = cosl(angle);
	double sa = sinl(angle);
	return {x+ca,y+sa};
	// auto test = [&](double d) {
	// 	double x1 = ca*d;
	// 	double y1 = sa*d;
	// 	double dx = x1 - x;
	// 	double dy = y1 - y;
	// 	return (dx*dx+dy*dy) >= 1;
	// };
	// double lo = sqrt(x*x+y*y);
	// double hi = lo+2;
	// double best = -1;
	// while ((hi-lo) >= EPS) {
	// 	double mid = (hi+lo)/2;
	// 	if (test(mid)) {
	// 		best = mid;
	// 		hi = mid-EPS;
	// 	} else {
	// 		lo = mid+EPS;
	// 	}
	// }
	// ID if (best == -1) {
	// 	printf("failed to find child for (%f,%f) on line (a=%f)\n", x, y, angle);
	// }
	// assert(best != -1);
	// return {ca*best,sa*best};
}
 
void mkanswer(int at, int prev, double x, double y, double start_angle, double end_angle) {
	ID printf("answer[%d] = (%f, %f)\n", at, x, y);
	ax[at] = x;
	ay[at] = y;
	int cells = cc[at]-1;
	double unit = (end_angle-start_angle)/cells;
	double child_start = start_angle;
	for (int next : e[at]) {
		if (next == prev) continue;
		double child_end = child_start + (cc[next]-1)*unit;
		double child_angle = (child_start + child_end) / 2;
		dd child = find_child(x, y, child_angle);
		mkanswer(next, at, child.x, child.y, child_start, child_end);
		child_start += cc[next]*unit;
	}
}
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 2; i <= n; i++) {
		cin >> a >> b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs(1, 0);
	mkanswer(1, 0, 0, 0, -3.0, 3.0);
	cout << setprecision(15);
	for (int i = 1; i <= n; i++) {
		printf("%.10Lf %.10Lf\n", ax[i], ay[i]);
	}
}