#include <bits/stdc++.h>
#define MAXN 1000005
#define ii pair<int, int>
#define x first
#define y second
#define ID if (0)
using namespace std;
 
struct node {
	// t = (concat, shuffle, sorted, list, repeat)
	int t;
	vector<int> c;
};
 
node tree[MAXN];
int last_node = 0;
int new_node() {
	++last_node;
	tree[last_node].t = 0;
	tree[last_node].c.clear();
	return last_node;
}
 
ii parse_str(string& s, int start = 0) {
	int at = new_node();
	int pos = start;
	if (s.substr(pos, 6) == "concat") {
		tree[at].t = 1;
		pos += 7;
		ii child1 = parse_str(s, pos);
		pos = child1.y+1;
		ii child2 = parse_str(s, pos);
		pos = child2.y+1;
		tree[at].c = {child1.x, child2.x};
	}
	else if (s.substr(pos, 7) == "shuffle") {
		ID cout << "is shuffle " << at <<  endl;
		tree[at].t = 2;
		pos += 8;
		ii child = parse_str(s, pos);
		pos = child.y+1;
		tree[at].c = {child.x};
	}
	else if (s.substr(pos, 6) == "sorted") {
		tree[at].t = 3;
		pos += 7;
		ii child = parse_str(s, pos);
		pos = child.y+1;
		tree[at].c = {child.x};
	}
	else if (s.substr(pos, 1) == "[") {
		tree[at].t = 4;
		pos += 1;
		int val = 0;
		for (int i = pos; true; i++) {
			if (s[i] == ',') {
				tree[at].c.push_back(val);
				val = 0;
				continue;
			}
			if (s[i] == ']') {
				tree[at].c.push_back(val);
				pos = i+1;
				break;
			}
			val *= 10;
			val += (s[i]-'0');
		}
	}
	return {at,pos};
}
 
void dfs_push(int at, vector<int>& sv) {
	ID cout << "push " << at << endl;
	if (tree[at].t == 1) {
		dfs_push(tree[at].c[0],sv);
		dfs_push(tree[at].c[1],sv);
	}
	if (tree[at].t == 2) {
		dfs_push(tree[at].c[0],sv);
	}
	if (tree[at].t == 3) {
		dfs_push(tree[at].c[0],sv);
	}
	if (tree[at].t == 4) {
		for (int x : tree[at].c) sv.push_back(x);
	}
}
 
// simplify to a set of static regions and a set of shuffled regions
// values
// "shuffled regions" [s,e) with uniform probability
int simplify(int at, int s, vector<int>& v, vector<ii>& sr) {
	ID cout << "simplify " << at << endl;
	if (tree[at].t == 1) {
		int e0 = simplify(tree[at].c[0], s, v, sr);
		return simplify(tree[at].c[1], e0, v, sr);
	}
	if (tree[at].t == 2) {
		// become uniform distribution
		vector<int> sv;
		dfs_push(at, sv);
		sort(sv.begin(), sv.end());
		for (int i = 0; i < sv.size(); i++) v[i+s] = sv[i];
		if (sv[0] != sv.back()) {
			sr.push_back({s,s+sv.size()});
		}
		return s + sv.size();
	}
	if (tree[at].t == 3) {
		// become static region
		vector<int> sv;
		dfs_push(at, sv);
		sort(sv.begin(), sv.end());
		for (int i = 0; i < sv.size(); i++) v[i+s] = sv[i];
		return s + sv.size();
	}
	if (tree[at].t == 4) {
		// become static region
		for (int i = 0; i < tree[at].c.size(); i++) v[i+s] = tree[at].c[i];
		return s + tree[at].c.size();
	}
	return -1;
}
 
void dbgprint(int at) {
	cout << "["<<at<<"]";
	if (tree[at].t == 1) {
		cout << "concat(";
		dbgprint(tree[at].c[0]);
		cout << ",";
		dbgprint(tree[at].c[1]);
		cout << ")";
	}
	if (tree[at].t == 2) {
		cout << "shuffle(";
		dbgprint(tree[at].c[0]);
		cout << ")";
	}
	if (tree[at].t == 3) {
		cout << "sorted(";
		dbgprint(tree[at].c[0]);
		cout << ")";
	}
	if (tree[at].t == 4) {
		cout << "[";
		for (int i = 0; i < tree[at].c.size(); i++) {
			if (i) cout << ",";
			cout << tree[at].c[i];
		}
		cout << "]";
	}
	if (tree[at].t == 5) {
		cout << "repeat(";
		cout << ")";
	}
}
 
bool compare(int a, int b) {
	// case-bash 25 cases
	ID {
		dbgprint(a);
		cout << endl;
		dbgprint(b);
		cout << endl;
	}
	vector<int> av(1000000,-1);
	vector<ii> asr;
	vector<int> bv(1000000,-1);
	vector<ii> bsr;
	simplify(a,0,av,asr);
	simplify(b,0,bv,bsr);
	sort(asr.begin(), asr.end());
	sort(bsr.begin(), bsr.end());
	for (int i = 0; i < av.size(); i++) {
		if (av[i] != bv[i]) return false;
	}
	if (asr.size() != bsr.size()) return false;
	for (int i = 0; i < asr.size(); i++) {
		if (asr[i].x != bsr[i].x) return false;
		if (asr[i].y != bsr[i].y) return false;
	}
	return true;
}
 
string a, b;
int main() {
	getline(cin, a);
	getline(cin, b);
	int ax = parse_str(a).x;
	int bx = parse_str(b).x;
	if (!compare(ax, bx)) cout << "not ";
	cout << "equal" << endl;
}