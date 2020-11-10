#include <bits/stdc++.h>
#define MAXN 200005
#define ID if (0)
using namespace std;
int n, m, t, a, b;
int cnt[MAXN];
set<int>* tower[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    int answer = n-1;
    for (int i = 1; i <= n; i++) {
        cin >> t;
        if (tower[t] == NULL) tower[t] = new set<int>();
        if (tower[t]->count(i+1)) { answer -= 1; cnt[t] += 1; }
        if (tower[t]->count(i-1)) { answer -= 1; cnt[t] += 1; }
        tower[t]->insert(i);
        ID printf("disk %d belongs to tower %d\n", i, t);
    }
    cout << answer << endl;
    for (int j = 1; j <= m-1; j++) {
        scanf("%d %d", &a, &b); // merge towers a and b
        // if size_b > size_a, swap the two towers
        if (tower[b]->size() > tower[a]->size()) {
            set<int>* t1 = tower[a];
            tower[a] = tower[b];
            tower[b] = t1;
            int t2 = cnt[a];
            cnt[a] = cnt[b];
            cnt[b] = t2;
        }
        // merge tower b into tower a
        ID printf("cnt[%d] = %d\n", a, cnt[a]);
        ID printf("cnt[%d] = %d\n", b, cnt[b]);
        answer += cnt[a];
        answer += cnt[b];
        for (int i : *(tower[b])) {
            ID printf("moving disk %d from tower %d => %d\n", i, b, a);
            // insert into tower a, check
            if (tower[a]->count(i+1)) cnt[a] += 1;
            if (tower[a]->count(i-1)) cnt[a] += 1;
            tower[a]->insert(i);
        }
        answer -= cnt[a];
        ID printf("cnt[%d] = %d\n", a, cnt[a]);
        cout << answer << endl;
    }
}