#include <bits/stdc++.h>
using namespace std;
#define len(x) ((int)(x).length())
#define ii pair<int, int>
#define x first
#define y second
 
bool opp(char a, char b) {
	return (
		(a == 'U' && b == 'D') ||
		(a == 'D' && b == 'U') ||
		(a == 'L' && b == 'R') ||
		(a == 'R' && b == 'L')
	);
}
 
string s;
int main() {
	cin >> s;
	if (len(s) >= 3) {
		if (s[len(s)-1] == s[len(s)-3]) {
			if (opp(s[len(s)-1], s[len(s)-2])) {
				cout << "impossible" << endl;
				return 0;
			}
		}
	}
 
	int step = (1<<28);
	int x = 0;
	int y = 0;
	vector<ii> pos;
	for (int i = len(s)-1; i >= 0;) {
		char c = s[i];
		if (c == 'U') {
			pos.push_back({x,y+1});
			y -= step;
			pos.push_back({x,y-2});
		}
		if (c == 'D') {
			pos.push_back({x,y-1});
			y += step;
			pos.push_back({x,y+2});
		}
		if (c == 'L') {
			pos.push_back({x-1,y});
			x += step;
			pos.push_back({x+2,y});
		}
		if (c == 'R') {
			pos.push_back({x+1,y});
			x -= step;
			pos.push_back({x-2,y});
		}
		while (i >= 0 && (s[i]==c||opp(s[i],c))) i -= 1;
		step = (step-5)/2;
	}
	cout << x << ' ' << y << endl;
	cout << pos.size() << endl;
	for (auto [x, y] : pos) {
		cout << x << ' ' << y << endl;
	}
}