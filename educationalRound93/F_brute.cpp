[16:20] Tianyi Zheng
    
#include <bits/stdc++.h>
using namespace std;
 
int n;
string s;
 
int solve(int x) {
    int answer = 0;
    int prevU = 0; // immedately previous ?s count
    int consU = 0; // consecutive ?s can have 1 or 0, but not both
    int cons1 = 0; // consecutive 1s can have ?
    int cons0 = 0; // consecutive 1s can have ?
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '?') {
            prevU += 1;
            consU += 1;
        }
        if (s[i] == '1') {
            if (cons0 == 0) {
                prevU = 0;
                cons1 += 1;
            } else {
                consU = prevU;
                prevU = 0;
                cons0 = 0;
                cons1 += 1;
            }
        }
        if (s[i] == '0') {
            if (cons1 == 0) {
                prevU = 0;
                cons0 += 1;
            } else {
                consU = prevU;
                prevU = 0;
                cons1 = 0;
                cons0 += 1;
            }
        }
        if (consU + cons1 >= x || consU + cons0 >= x) {
            prevU = 0;
            consU = 0;
            cons1 = 0;
            cons0 = 0;
            answer += 1;
        }
    }
    return answer;
}
 
int main() {
    cin >> n >> s;
    for (int x = 1; x <= n; x++) {
        cout << solve(x) << endl;
    }
}



