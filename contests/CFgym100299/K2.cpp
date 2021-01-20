#include <bits/stdc++.h>
using namespace std;
int N , fa[30] , depth[30] , DP[30] , pre[30] , indeg[30];
vector<int> g[26];
vector<int> cycle;
bool vis[30];
void init(){
 cycle.clear();
 for(int i = 0; i < 26; ++i)fa[i] = -1;
 for(int i = 0; i < 26; ++i)depth[i] = 0;
 for(int i = 0; i < 26; ++i)vis[i] = 0;
 for(int i = 0; i < 26; ++i)DP[i] = 0;
 for(int i = 0; i < 26; ++i)pre[i] = -1;
}
void DFS(int v , int p, int d , int root){
	int backv = -1;
	vis[v] = 1;
	//depth[v] = d + 1;
	fa[v] = p;
	for(int u : g[v]){
		if(depth[u] >= 1){
			if(backv == -1 && u == root){
				backv = u;
				break;
			}
		}
		if(!vis[u]){
			DFS(u , v, d + 1 , root);
		}
	}

	if(~backv){
		// cout << "back v= " << backv << endl;
		while(v != backv){
			// cout << v << endl;
			cycle.push_back(v);
			v = fa[v];
		}
		// cout << "ok\n";
		//cycle.push_back(v);
		reverse(cycle.begin() , cycle.end());
	}
}
void DFS2(int v , int p){
	DP[v] = 1;
	vis[v] = 1;
	for(int u : g[v]){
		if(!vis[u])DFS2(u , v);
		if(DP[v] < DP[u] + 1){
			DP[v] = DP[u] + 1;
			pre[v] = u;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t--){
	for(int i = 0; i < 26; ++i)g[i].clear();
	for(int i = 0; i < 26; ++i)indeg[i] = 0;
	cin >> N;
	map<string , int> ban;
	/*for(int i = 0; i < 26; ++i)for(int j = 0; j < 26; ++j){
	string t = "";
	t += ('a' + i);
	t += ('a' + j);
	ban[t] = 1;
	}*/
	for(int i = 1; i <= N; ++i){
	string x; 
	cin >> x; 
	//ban[x] = 0;
	ban[x] = 1; 
	}
	init();
	if(N == 26 * 26){
	cout << "a\n";
	continue;
	}
	if(N == 26 * 26 - 1){
	cout << "a\n";
	continue;
	}
	for(int i = 0; i < 26; ++i){
	for(int j = 0; j < 26; ++j){
	string t = "";
	t += ('a' + i);
	t += ('a' + j);
	if(ban[t])continue;
	g[i].push_back(j);
	++indeg[j];
	}
	}
	// check if we have cycle length 1
	int cycle1 = 0 , s = -1;
	for(int i = 0; i < 26; ++i){
	for(int j : g[i]){
	if(i == j){
	cycle1 = 1;
	s = i;
	}
	}
	}
	if(cycle1){
	for(int i = 1; i <= 20; ++i){
	for(int j = 1; j <= 20; ++j){
	char a = 'a' + s;
	cout << a;
	}
	cout << endl;
	}
	continue;
	}
	// check if we have cycle length >= 2
	for(int i = 0; i < 26; ++i){
	if(cycle.size())break;
	init();
	DFS(i , -1 , 0 , i);
	}
	// cout << "ok\n";
	if(cycle.size()){
	//cout << "cycle \n";
	//for(int i : cycle)cout << i << " ";
	//cout << endl;
	for(int i = 0; i < 20; ++i){
	for(int j = 0; j < 20; ++j){
	char a = 'a' + cycle[(i + j) % (int)cycle.size()];
	cout << a;
	}
	cout << endl;
	}
	continue;
	}
	init();
	for(int i = 0; i < 26; ++i){
	if(indeg[i] == 0){
	DFS2(i , i);
	}
	}
	int max_len = 0 , best = -1;
	for(int i = 0; i < 26; ++i){
	//if(DP[i])printf("DP[%d] = %d\n" , i , DP[i]);
	if(max_len < DP[i]){
	max_len = DP[i];
	best = i;
	}
	}
	//cout << "max_len = " << max_len << " best = " << best << endl; 
	vector<int> path;
	while(~best){
	path.push_back(best);
	best = pre[best];
	}
	/*cout << "path len = " << path.size() << endl;
	for(int i : path){
	cout << i << " ";
	}
	cout << endl;*/
	int sz = (path.size() + 1) / 2;
	for(int i = 0; i < sz; ++i){
	for(int j = 0; j < sz; ++j){
	char a = 'a' + path[(i + j)];
	cout << a;
	}
	cout << endl;
	}
	}
}