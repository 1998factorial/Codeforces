#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 500011
using namespace std;
char st[MAX_SIZE], pt[MAX_SIZE];
int occ[2], p[MAX_SIZE];
char ans[MAX_SIZE];
 
int main() {
    int N, M, i, j = 0;
    scanf("%s", pt+1);
    M = strlen(pt+1);
    scanf("%s", st+1);
    N = strlen(st+1);
    for (i = 2; i <= N; ++i) {
        while (j > 0 && st[i] != st[j+1]) j = p[j];
        if (st[i] == st[j+1]) ++j;
        p[i] = j;
    }    
 
    for (i = 1; i <= M; ++i) {
        occ[pt[i] - '0']++;
    }
 
    j = 0;
    for (i = 1; i <= M; ++i) {
        if (occ[st[j+1] - '0'] > 0) {
            occ[st[j+1] - '0']--;
            ans[i] = st[j+1];
        } else {
            occ[1 - (st[j+1] - '0')]--;
            ans[i] = (1 - (st[j+1] - '0')) + '0';
        }
        ++j;
        if (j == N) j = p[j];
    }
 
    printf("%s\n", ans+1);
    return 0;
}