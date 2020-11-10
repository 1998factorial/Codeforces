#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

char s[MAX_SIZE];
stack<char> st;
map<int, int> cnt;

int main() {
    int n, i, j, sz;
    scanf("%d", &n);
    for (i = 0 ; i < n; ++i) {
        scanf("%s", s);
        sz = strlen(s);
        for (j = 0 ; j < sz; ++j) {
            if (st.empty()) {
                st.push(s[j]);
            } else {
                if (st.top() == '(' && s[j] == ')') {
                    st.pop();
                    continue;
                }
                st.push(s[j]);
            }
        }

        if (st.empty()) {
            cnt[0]++;
        } else if (st.top() == '(') {
            int sz = st.size();
            bool valid = true;
            while (!st.empty()) {
                if (st.top() == ')') {
                    valid = false;
                }
                st.pop();
            }
            if (valid)
                cnt[sz]++;
        } else {
            int sz = st.size();
            bool valid = true;
            while (!st.empty()) {
                if (st.top() == '(') {
                    valid = false;
                }
                st.pop();
            }
            if (valid)
                cnt[-sz]++;
        }
    }
    long long ans = 0;
    auto iter = cnt.lower_bound(0);
    while (iter != cnt.end()) {
        if (iter->first == 0) {
            ans += 1ll * iter->second * iter->second;
        } else {
            ans += 1ll * iter->second * cnt[-iter->first];
        }

        iter++;
    }

    cout << ans << endl;
    return 0;
}
