#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n, k, num, i;
    vector<int> ret;
    int K;
    scanf("%d%d", &n, &k);
    num = n;
    K = k;
    for (i = 2; i <= n; ++i) {
        while (num % i == 0 && k > 1) {
            ret.push_back(i);
            num = num / i;
            k--;
        }
    }
    if (num > 1) ret.push_back(num);
    if (ret.size() == K) {
        for (auto v : ret) {
            cout << v << " ";
        }
    } else {
        cout << -1 << endl;
    }
    return 0;
}