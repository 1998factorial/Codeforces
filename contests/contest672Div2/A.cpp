#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
 
int a[MAX_SIZE];
 
int main(){
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, i;
        scanf("%d", &n);
        for (i = 0 ; i < n; ++i) scanf("%d", &a[i]);
        int ok = 0;
        for (i = 1; i < n; ++i) {
            if (a[i] >= a[i-1]) ok++;
        }
 
        if (ok > 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}