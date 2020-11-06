#include <bits/stdc++.h>
#define MAX_SIZE 1001111
typedef long long ll;
using namespace std;
 
char st[MAX_SIZE];
vector<string> ss;
int visited[MAX_SIZE];
int d[MAX_SIZE];
vector<int> rid[MAX_SIZE];
int curr = 0, mx = 0;
void SplitString(const string& s, vector<string>& v, const string& c) {
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2) {
    	v.push_back(s.substr(pos1, pos2-pos1));
    	pos1 = pos2 + c.size();
    	pos2 = s.find(c, pos1);
  }
 
  if(pos1 != s.length())
    	v.push_back(s.substr(pos1));
}
 
void dfs(int v, int dep) {
	// cout << v << " " << dep << endl;
	visited[v] = 1;
	d[v] = dep;
	rid[d[v]].push_back(v);
	mx = max(mx, d[v]);
	curr += 2;
	int cnt = atoi(ss[v + 1].c_str());
	while (cnt > 0) {
		dfs(curr, dep + 1);
		--cnt;
	}
}
 
int main() {
	scanf("%s", st);
	string s = string(st);
	SplitString(s, ss, ",");
	int sz = ss.size();
	while (curr < sz) {
		dfs(curr, 0);
	}
	
	printf("%d\n", mx + 1);
	for (int i = 0 ; i <= mx; ++i) {
		for (auto v : rid[i]) {
			printf("%s ", ss[v].c_str());
		}
		printf("\n");
	}
	return 0;
}