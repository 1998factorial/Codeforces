#include <bits/stdc++.h>
using namespace std;
#define MAXN 45
#define lli int64_t
#define INF ((double)(1e10))

namespace geometry {
	const double EPS = 1e-15;
	struct vec2d {
		double x, y;
		vec2d () {}
		vec2d(double x, double y) : x(x), y(y) {}
		void operator=(const vec2d &p) { x = p.x, y = p.y; }
		vec2d operator*(double scl) const { return vec2d(x * scl, y * scl); }
		vec2d operator+(const vec2d&p) const { return vec2d(x + p.x, y + p.y); }
		vec2d operator-(const vec2d&p) const { return vec2d(x - p.x, y - p.y); }
		double crs(const vec2d &p) const { return x * p.y - y * p.x; }
		double dot(const vec2d &p) const { return x * p.x + y * p.y; }
		double len2() { return x * x + y * y; }
		vec2d rotateLeft() const { return vec2d(-y, x); }
	};

	ostream& operator<<(ostream& out, vec2d& v) {
		return out << '(' << v.x << ',' << v.y << ')';
	}

	struct line2d {
		double a, b, c;
		line2d(vec2d p, vec2d q) {
			if(abs(p.x - q.x) < EPS) {
				a = 1;
				b = 0;
				c = -p.x;
			}
			else {
				a = (p.y - q.y) / (q.x - p.x);
				b = 1.0;
				c = -(a * p.x + p.y);
			}
		}

		bool parallel(line2d l) {
			return abs(a - l.a) < EPS && abs(b - l.b) < EPS;
		}

		vec2d intersect(line2d l) {
			if (parallel(l)) return vec2d();	
			double x = (b * l.c - c * l.b) / (a * l.b - b * l.a);
			double y;
			if (abs(b) < EPS) y = -l.a * x - l.c;
			else y = -a * x - c;
			return vec2d(x, y);
		}
	};
}

using namespace geometry;

int n, x[MAXN], y[MAXN];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i];
	}
	int best = max(1, n-1);
	for (int a = 1; a <= n; a++) {
		for (int b = a+1; b <= n; b++) {
			for (int c = a; c <= n; c++) {
				for (int d = c+1; d <= n; d++) {
	// for (int a = 1; a <= n; a++) {
	// 	for (int b = 1; b <= n; b++) {
	// 		for (int c = 1; c <= n; c++) {
	// 			for (int d = 1; d <= n; d++) {
					if (a == b) continue;
					if (c == d) continue;
					if (a == c && b == d) continue;

					// ab and cd bisector intersection
					vec2d pa(x[a], y[a]);
					vec2d pb(x[b], y[b]);
					vec2d pc(x[c], y[c]);
					vec2d pd(x[d], y[d]);
					vec2d mab = (pa+pb)*0.5;
					vec2d mcd = (pc+pd)*0.5;
					vec2d center;
					if ((mab-mcd).len2() < EPS) {
						center = mab;
					} else {
						line2d secab(mab, mab+(pb-pa).rotateLeft());
						line2d seccd(mcd, mcd+(pd-pc).rotateLeft());
						if (secab.parallel(seccd)) continue;
						center = secab.intersect(seccd);
					}

					vector<double> dist2s;
					for (int i = 1; i <= n; i++) {
						double dist2 = (center-vec2d(x[i], y[i])).len2();
						dist2s.push_back(dist2);
					}
					sort(dist2s.begin(), dist2s.end());
					int count = 0;
					double prev = INF;
					for (double x : dist2s) {
						count += abs(x-prev) > EPS;
						prev = x;
					}
					best = min(best, count);
				}
			}
		}
	}

	// otherwise n-1
	cout << best << endl;
}