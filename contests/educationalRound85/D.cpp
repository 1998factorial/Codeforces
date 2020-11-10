/*
// 0 as the start: (2*(n-1))-1 steps
// n-1 as the start: (2*(n-2))-1 steps
// n-2 as the start: (2*(n-3))-1 steps
// ..
// and ends with
// 1 to 2 to 3 .. to n-1
*/


#include <bits/stdc++.h>
#define int int64_t
#define INF 1152921504606847000L
#define ID if (false)
using namespace std;


int t, n, l, r;


int next_pivot(int pivot) {
    if (pivot == 0) return n-1;
    else return pivot - 1;
}

signed main() {
    cin >> t;
    while (t--) {
        cin >> n >> l >> r;
        l -= 1;
        r -= 1;
        int pivot = 0; // current vertex it branches out from
        int pivot_index = 0; // index in the sequence where this pivot appears
        int pivot_steps = (2*(n-1)); // number of steps using this pivot
        while (pivot_index + pivot_steps <= l) {
            // switch to the next pivot
            pivot = pivot + 1;
            pivot_index += pivot_steps;
            pivot_steps -= 2;
            if (pivot_steps < 0) break;
        }
        ID {
            cout << "the starting pivot is: " << (pivot+1) << endl;
            cout << "with steps: " << pivot_steps << endl;
            cout << "and pivot_index: " << pivot_index << endl;
        }
        // number of steps inside this pivot
        for (int i = l; i <= r; i++) {
            int vertex = -1;
            int inner_index = i-pivot_index;
            if (pivot != -1 && inner_index == pivot_steps) {
                pivot = pivot + 1;
                pivot_index += pivot_steps;
                pivot_steps -= 2;
            }
            if (i == n*(n-1)) vertex = 0;
            else if (inner_index % 2 == 0) vertex = pivot;
            else vertex = (inner_index / 2) + 1 + pivot;
            ID cout << (vertex+1) << endl;
            else cout << (vertex+1) << " ";
        }
        cout << endl;
    }
}
