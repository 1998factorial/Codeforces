#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int T, N;

int main() {
    cin >> T;
    for (int t = 1; t <= T; t++) {
        printf("Case #%d:\n", t);
        cin >> N;
        int pos = 0;
        for(pos = 32; pos >= 0; --pos){
          if((1ll << pos) & N){
            break;
          }
        }
        ++pos;
        bool left = true;
        int touse = N - pos;
        int row = 0;
        int fullused = 0;
        for (row = 0; row < pos; row++) {
            int mask = (1 << row);
            if (touse & mask) {
                fullused += 1;
                if (left) {
                    for (int col = 0; col <= row; col++) {
                        cout << (row+1) << " " << (col+1) << endl;
                    }
                    left = false;
                } else {
                    for (int col = row; col >= 0; col--) {
                        cout << (row+1) << " " << (col+1) << endl;
                    }
                    left = true;
                }
            } else {
                if (left) {
                    cout << (row + 1) << " 1" << endl;
                } else {
                    cout << (row + 1) << " " << (row + 1) << endl;
                }
            }
        }

        for (int i = 0; i < fullused; i++) {
            if (left) {
                cout << (row + 1) << " 1" << endl;
            } else {
                cout << (row + 1) << " " << (row + 1) << endl;
            }
            row += 1;
        }
    }
}
