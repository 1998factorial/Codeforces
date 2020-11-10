#include <bits/stdc++.h>
using namespace std;
int hi, lo;
int main() {
    int mask = (1 << 7) - 1;
    cout << "? ";
    for (int i = 1; i <= 100; i++) {
        cout << i << ' ';
    }
    cout << endl;
    fflush(stdout);
    cout << "? ";
    for (int i = 1; i <= 100; i++) {
        cout << (i << 7) << ' ';
    }
    cout << endl;
    fflush(stdout);
    cin >> hi >> lo;
    cout << "! " << (hi & (mask << 7)) + (lo & mask) << endl;
    fflush(stdout);
}