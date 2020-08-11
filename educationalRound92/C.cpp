#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 200111
typedef long long ll;
 
int N;
char st[MAX_SIZE];
int getlen(int x, int y) {
    int i, ret = 0, tp = 0;
    for (i = 0; i < N; ++i) {
        if(tp == 0){
            if(st[i] - '0' == x){
                ++ret;
                tp = 1;
            }
        }
        else{
            if(st[i] - '0' == y){
                ++ret;
                tp = 0;
            }
        }
    }
 
    if (x != y) ret = ret / 2 * 2;
    return ret;
}
 
int main(){
    int i, j, T;
    scanf("%d", &T);
    while (T--) {
        int ans = 1;
        scanf("%s", st);
        N = strlen(st);
        for (i = 0 ; i <= 9; ++i) {
            for (j = 0 ; j <= 9; ++j) {
                ans = max(ans, getlen(i, j));
            }
        }
        printf("%d\n", N - ans);
    }
    return 0;
}