#include <bits/stdc++.h>
using namespace std;

int t, n, q, d[100005][2], s, k;

int main() {
    scanf("%d" , &t);
    for (int iter = 1; iter <= t; iter++) {
        scanf("%d %d" , &n , &q);
        for (int i = 1; i < n; i++) {
            int diff;
            cin >> diff;
            d[i][1] = diff;
            d[i+1][0] = diff;
        }
        printf("Case #%d:" , iter);
        while (q--) {
            scanf("%d %d" , &s , &k);
            vector<int> answer;
            answer.push_back(s);
            int l = s;
            int r = s;
            --k;
            while (k--) {
                if (r == n || (l != 1 && d[l][0] < d[r][1])) {
                    --l;
                    answer.push_back(l);
                } else {
                    ++r;
                    answer.push_back(r);
                }
            }
            printf(" %d" , answer[answer.size() - 1]);
        }
        printf("\n");
    }
}
