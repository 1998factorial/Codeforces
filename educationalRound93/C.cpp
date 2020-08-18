#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
char s[MAX_SIZE];
int f[MAX_SIZE];
map<int, int> mp;
int T, n;
ll cnt = 0;
int main() {
    int i;
    scanf("%d", &T);
    while (T-- > 0) {
        cnt = 0;
        mp.clear();
        scanf("%d", &n);
        scanf("%s", s + 1);
        for (i = 1; i <= n; ++i) {
            f[i] = s[i] - '0' - 1;
        }
        ll p = 0;
        mp[0] = 1;
        for (i = 1; i <= n; ++i) {
            p += f[i];
            cnt += mp[p];
            mp[p]++;
        }
 
        cout << cnt << endl;
    }   
    return 0;
}