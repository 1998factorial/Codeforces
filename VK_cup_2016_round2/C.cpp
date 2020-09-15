#include <bits/stdc++.h>
using namespace std;
 
int n, q, t, x;
int fix_shift(int v) {
    if (v < 0) return v + n;
    if (v >= n) return v - n;
    return v;
}
 
int fix_answer(int v) {
    if (v < 1) return v + n;
    if (v > n) return v - n;
    return v;
}
 
int answer[1000005];
int shift_odd;
int shift_evn;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    shift_odd = 0;
    shift_evn = 0;
    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> x;
            shift_odd = fix_shift(shift_odd + x);
            shift_evn = fix_shift(shift_evn + x);
        }
        if (t == 2) {
            if (shift_odd % 2 == 0) {
                // shift_odd will be moved right
                shift_odd += 1;
                shift_evn -= 1;
            } else {
                shift_odd -= 1;
                shift_evn += 1;
            }
            shift_odd = fix_shift(shift_odd);
            shift_evn = fix_shift(shift_evn);
        }
    }
 
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) answer[fix_answer(i + shift_odd)] = i;
        else answer[fix_answer(i + shift_evn)] = i;
    }
    for (int i = 1; i <= n; i++) {
        cout << answer[i] << ' ';
    }
    cout << endl;
}