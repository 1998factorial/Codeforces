#include <bits/stdc++.h>
#define MAX_SIZE 400011
using namespace std;
 
struct node {
    int id, v;
    bool operator < (node other) const {
        return v > other.v;
    }
};
 
vector<int> g[MAX_SIZE];
node nd[MAX_SIZE];
int N, indegree[MAX_SIZE];
 
int main() {
	int i;
    scanf("%d", &N);
	for (i = 1; i <= N; ++i) {
		scanf("%d", &nd[i].v);
		nd[i].id = i;
		int v;
		scanf("%d", &v);
		while (v-- > 0) {
			int u;
			scanf("%d", &u);
			g[i].push_back(u);
		}
	}
 
    for (i = 1; i <= N; ++i) {
        for (auto nv : g[i]) {
            indegree[nv]++;
        }
    }
 
    priority_queue<node> q;
    for (i = 1; i <= N; ++i) {
        if (indegree[i] == 0) {
            q.push(nd[i]);
        }
    }
 
    vector<int> ret;
    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        ret.push_back(curr.id);
        for (auto nv : g[curr.id]) {
            indegree[nv]--;
            if (indegree[nv] == 0) {
                q.push(nd[nv]);
            }
        }
    }
 
	reverse(ret.begin(), ret.end());
	int sz = ret.size();
	int ans = 0;
	for (i = 0 ; i < sz; ++i) {
		// cout << ret[i] << endl;
		ans = max(ans, nd[ret[i]].v + i);
	}
 
	printf("%d\n", ans);
    return 0;
}