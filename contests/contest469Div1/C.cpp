#include <bits/stdc++.h>
#define MAX_SIZE 110111
typedef long long ll;
using namespace std;
 
int N, M, H;
vector<int> g[MAX_SIZE];
pair<int, int> edg[MAX_SIZE];
int h[MAX_SIZE];
int visited[MAX_SIZE];
int cmpid[MAX_SIZE];
int instack[MAX_SIZE];
stack<int> st;
int low[MAX_SIZE];
int cnt = 0;
int sz[MAX_SIZE];
vector<int> cp[MAX_SIZE];
int id = 0;
int outlink[MAX_SIZE];
 
void tarjan(int v) {
	visited[v] = low[v] = ++cnt;
	st.push(v);
	instack[v] = 1;
	for (auto nv : g[v]) {
		if (!visited[nv]) {
			tarjan(nv);
			low[v] = min(low[v], low[nv]);
		} else if (instack[nv]) {
			low[v] = min(low[v], visited[nv]);
		}
	}
 
	if (low[v] == visited[v]) {
		while (st.top() != v) {
			instack[st.top()] = 0;
			cmpid[st.top()] = id;
			cp[id].push_back(st.top());
			st.pop();
		}
 
		instack[st.top()] = 0;
		cp[id].push_back(st.top());
		cmpid[st.top()] = id++;
		st.pop();
	}
}
 
int main() {
	int i;
	scanf("%d%d%d", &N, &M, &H);
	for (i = 1; i <= N; ++i) {
		scanf("%d", &h[i]);		
	}
 
	for (i = 1; i <= M; ++i) {
		scanf("%d%d", &edg[i].first, &edg[i].second);
		if ((h[edg[i].first] + 1) % H == h[edg[i].second]) {
			g[edg[i].first].push_back(edg[i].second);
		}
 
		if ((h[edg[i].second] + 1) % H == h[edg[i].first]) {
			g[edg[i].second].push_back(edg[i].first);
		}
	}
 
	for (i = 1; i <= N; ++i) {
		if (!visited[i]) {
			tarjan(i);
		}
	}
 
	for (i = 1; i <= N; ++i) {
		sz[cmpid[i]]++;
	}
 
	for (i = 1; i <= N; ++i) {
		for (auto nv : g[i]) {
			if (cmpid[nv] != cmpid[i]) {
				outlink[cmpid[i]]++;
			}
		}
	}
 
	int ans = N + 1, ret = 0;
	for (i = 0; i < id; ++i) {
		if (outlink[i] == 0) {
			if (ans >= sz[i]) {
				ans = sz[i];
				ret = i;
			}
		}
	}
 
	printf("%d\n", ans);
	for (auto v : cp[ret]) {
		printf("%d ", v);
	}
    return 0;
}