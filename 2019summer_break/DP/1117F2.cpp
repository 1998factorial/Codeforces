#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

const int N = 100 * 1000 + 13;
const int P = 17;

int n, p;
string s;
int A[P][P];
vector<int> pos[P];
int pr[P][N];
bitset<(1 << P)> legal, cur, dp;
int cnt[P];

void print_state(int s){
  for(int i = 0; i < p; ++i){
    if(s & (1 << i))cout << 1;
    else cout << 0;
  }
  cout << endl;
}

int main() {
	scanf("%d%d", &n, &p);
	char buf[N];
	scanf("%s", buf);
	s = buf;
	forn(i, p) forn(j, p)
		scanf("%d", &A[i][j]);

	forn(i, n){
		pos[s[i] - 'a'].push_back(i);
		forn(j, p)
			pr[j][i + 1] = pr[j][i] + (s[i] == 'a' + j);
	}

	legal.reset();
	legal.flip();

	int fl = (1 << p) - 1;
	forn(c, p) forn(d, c + 1){
		if (A[c][d]) continue;
		cur.reset();
		cur.flip();
		int i = 0, j = 0;
		while (i < pos[c].size() && j < pos[d].size()){
			if (c == d && i == j){
				++j;
				continue;
			}
			int mask = 0;
			if (pos[c][i] < pos[d][j]){
				forn(e, p) if ((pr[e][pos[d][j]] - pr[e][pos[c][i] + 1]) != 0)
					mask |= (1 << e);
				++i;
			}
			else{
				forn(e, p) if ((pr[e][pos[c][i]] - pr[e][pos[d][j] + 1]) != 0)
					mask |= (1 << e);
				++j;
			}
			if ((mask >> c) & 1) continue;
			if ((mask >> d) & 1) continue;
			cur[mask ^ fl] = 0;
		}
		for (int mask = fl; mask > 0; --mask){
			if (cur[mask]) continue;
			forn(e, p) if (c != e && d != e && ((mask >> e) & 1))
				cur[mask ^ (1 << e)] = 0;
		}
		legal &= cur;
	}

  for(int mask = 0; mask <= fl; ++mask){
    if(legal[mask])print_state(mask);
  }

	dp[fl] = 1;
	for (int mask = fl; mask > 0; --mask){
		if (!dp[mask]) continue;
		forn(i, p) if ((mask >> i) & 1){
			int nmask = mask ^ (1 << i);
			if (dp[nmask]) continue;
			dp[nmask] = legal[nmask];
		}
	}

	forn(i, n)
		++cnt[s[i] - 'a'];

	int ans = n;
	forn(mask, 1 << p) if (dp[mask]){
    //print_state(mask);
		int cur = 0;
		forn(i, p) if ((mask >> i) & 1)
			cur += cnt[i];
		ans = min(ans, cur);
	}

	printf("%d\n", ans);

	return 0;
}
