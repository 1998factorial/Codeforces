#include <bits/stdc++.h>
#define MAX_SIZE 524312
typedef long long ll;
using namespace std;
int main() {
	int n, i;
	scanf("%d", &n);
	int a = 1, b = n;
	for (i = 1; i <= sqrt(n); ++i) {
		if (n % i == 0) {
			a = i, b = n / i;
		}
	}
	cout << a << " " << b << endl;
	return 0;
}