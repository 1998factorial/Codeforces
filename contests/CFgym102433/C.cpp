#include <bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define INF (1<<29)
 
int n, m, a, b;
vector<int> e[MAXN];
bool seen[MAXN];
int dist[MAXN];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
 
	fill(dist,dist+MAXN,INF);
	deque<int> q;
	seen[1] = true;
	dist[1] = 0;
	q.push_back(1);
	while (q.size()) {
		int at = q.front();
		q.pop_front();
		for (int next : e[at]) {
			if (seen[next]) continue;
			seen[next] = true;
			dist[next] = dist[at]+1;
			q.push_back(next);
		}
	}
 
	cout << (dist[n]-1) << endl;
}