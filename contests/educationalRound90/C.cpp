#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int cnt[MAX_SIZE];
char s[MAX_SIZE];
int pos[MAX_SIZE];

int main() {
    int T, i;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int sz = strlen(s);
        for (i = 0 ; i < sz; ++i) {
            cnt[i] = 0;
            pos[i] = -1;
        }

        pos[sz] = -1;
        pos[sz + 1] = -1;
        cnt[0] = (s[0] == '+' ? 1 : -1);

        for (i = 1; i < sz; ++i) {
            int curr = (s[i] == '+' ? 1 : -1);
            cnt[i] = curr + cnt[i - 1];
        }

        for (i = 0 ; i < sz; ++i) {
            if (cnt[i] < 0 && pos[-cnt[i]] == -1) {
                pos[-cnt[i]] = i + 1;
            }
        }
        long long cnt = 0;
        for (i = 1; i <= sz; ++i) {
            if (pos[i] != -1) {
                cnt += pos[i];
            }
        }
        cnt += sz;
        printf("%lld\n", cnt);
    }
    return 0;
}
