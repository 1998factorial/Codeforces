#include <bits/stdc++.h>
#define MAX_SIZE 1000011
typedef long long ll;
using namespace std;
 
int a[MAX_SIZE], b[MAX_SIZE];
int N;
 
int main() {
    int i, fst = N + 1, lst = -1;
    scanf("%d", &N);    
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= N; ++i) b[i] = a[i];
    sort(a + 1, a + 1 + N);
    for (i = 1; i <= N; ++i) {
        if (a[i] != b[i]) {
            fst = i;
            break;
        }
    }
 
    for (i = N; i >= 1; --i) {
        if (a[i] != b[i]) {
            lst = i;
            break;
        }
    }
 
    if (fst > lst) {
        printf("1 1\n");
        return 0;
    }
 
    reverse(b + fst, b + 1 + lst);
/*    printf("%d %d\n", fst, lst);
    for (i = 1; i <= N; ++i) {
        printf("%d ", b[i]);
    }
    printf("\n");
*/
    for (i = 1; i <= N; ++i) {
        if (a[i] != b[i]) {
            printf("impossible\n");
            return 0;
        }
    }
 
    printf("%d %d\n", fst, lst);
    return 0;
}