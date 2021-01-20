#include <bits/stdc++.h>
#define MAX_SIZE 500011
 
int a[MAX_SIZE], N, C, B;
 
int main() {
	int i;
	scanf("%d%d%d", &N, &C, &B);
	for (i = 1; i <= N; ++i) a[i] = -1;
	for (i = 1; i <= B; ++i) {
		int v;
		scanf("%d", &v);
		a[v] = 0;
	}
 
	for (i = N; i >= 1 && C >= 2; --i) {
		if (a[i] == -1) {
			a[i] = 1, a[i-1] = 0;
			C -= 2;
		}
	}
 
	if (C == 1) {
		for (i = 1; i <= N && a[i] != 0; ++i) {
			a[i] = 1;
		}
	}
 
	for (i = 1; i <= N; ++i) {
		if (a[i] == -1) a[i] = 0;
	}
 
	for (i = 1; i <= N; ++i) {
		printf("%d", a[i]);
	}
	return 0;
}