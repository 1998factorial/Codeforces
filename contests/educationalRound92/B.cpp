#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;
int t;
int n, k, z;
int a[MAXN];
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> k >> z;
        for (int i = 1; i <= n; i++) cin >> a[i];
        a[n+1] = 0;
        int answer = 0;
        for (int usez = 0; usez <= z; usez++) {
            int cover = 1 + k - usez * 2; // maximum to the right reached
            ID printf("covered %d elements\n", cover);
            if (cover < 1) continue;
            // find maximum pair
            int best = 0;
            for (int i = 1; i <= cover; i++) {
                best = max(best, a[i] + a[i+1]);
            }
            best = best * usez;
            for (int i = 1; i <= cover; i++) {
                best += a[i];
            }
            answer = max(answer, best);
        }
        cout << answer << endl;
    }
}