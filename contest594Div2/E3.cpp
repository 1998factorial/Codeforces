#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int Maxn = 100000;

struct Node {
	int t;
	int id;
};
bool cmp(Node lhs, Node rhs) {return lhs.t == rhs.t ? lhs.id < rhs.id : lhs.t < rhs.t;}

int N, P;
Node A[Maxn + 5];
queue<int> q1;
priority_queue<int, vector<int>, greater<int> > q2;
ll ans[Maxn + 5];

int main() {
#ifdef LOACL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	scanf("%d %d", &N, &P);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &A[i].t);
		A[i].id = i;
	}
	sort(A + 1, A + N + 1, cmp);
	ll now = 0;
	int last = N + 1;
	for(int i = 1; i <= N;) {
		if(!q1.empty()) {
			int id = q1.front();
			q1.pop();
			ans[id] = now + P;
			now += P, last = id;
		} else if(A[i].t <= now) {
			if(q1.empty() && A[i].id < last)
				q1.push(A[i].id);
			else if(!q1.empty() && q1.back() > A[i].id && A[i].id < last)
				q1.push(A[i].id);
			else q2.push(A[i].id);
			i++;
		} else {
			if(!q2.empty()) {
				int id = q2.top();
				q2.pop();
				ans[id] = now + P;
				now += P, last = id;
			} else now = A[i].t, last = N + 1;
		}
	}
	while(!q1.empty()) {
		int id = q1.front();
		q1.pop(), ans[id] = now + P;
		now += P;
	}
	while(!q2.empty()) {
		int id = q2.top();
		q2.pop(), ans[id] = now + P;
		now += P;
	}
	for(int i = 1; i <= N; i++)
		printf("%lld ", ans[i]);
  printf("\n");
	return 0;
}
