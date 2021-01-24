#include <bits/stdc++.h>
using namespace std;
#define lli long long int
 
lli a, b;
int main() {
	cin >> a >> b;
	lli answer = 0;
	while (a > b) {
		if (a % 2 == 0) {
			answer += 1;
			a /= 2;
		} else {
			answer += 2;
			a += 1;
			a /= 2;
		}
	}
 
	answer += (b-a);
	cout << answer << endl;
}