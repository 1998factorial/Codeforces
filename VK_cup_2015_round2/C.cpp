#include <bits/stdc++.h>
using namespace std;
int vm(int x, int y) {
    return x + y - min(x, y);
}
int px, py, vx, vy;
int main() {
    cin >> px >> py >> vx >> vy;
    if (vx <= px && vy <= py) {
        cout << "Vasiliy" << endl;
        return 0;
    }
    // check if vasily can reach (px, 0) or (0, py) first
    if (vm(abs(vx-px),vy) < py || vm(vx,abs(vy-py)) < px) {
        cout << "Vasiliy" << endl;
    } else {
        cout << "Polycarp" << endl;
    }
}


