#include <bits/stdc++.h>
using namespace std;
#define MAXN 300005
#define ID if (0)
#define int long long int
 
// calculate the cumulative rank
// rank is either in the per person value, or per group value
// per group value should be added to every person in the group
 
// maintain invariant, after bumps for each week,
// cumulative_rank[i] = crank[i] + score_crank[score[i]] + (score_rank[score[i]]*(week-last_update[score[i]]))
 
// scoregroup based attributes
map<int, set<int>> score_group;
map<int, int> score_rank;
map<int, int> score_crank;
map<int, int> last_update;
 
// person based attributes
int score[MAXN]; // current score
int crank[MAXN]; // cumulative rank through weeks
 
int n, w, k, c;
int week; // current day at bump
 
void bump(int who) {
	ID {
		printf("bump %d in week %d\n", who, week);
	}
 
	// update either 1 or 2 groups
	int os = score[who];
	int ns = os+1;
	int rank = score_rank[os];
	score[who] = ns;
	if (score_group[os].size() == 1 && score_group[ns].empty()) {
		// special (simple) case, single person update
		// single to single
		crank[who] += score_rank[os]*(week-last_update[os]);
		crank[who] += score_crank[os];
 
		score_group[os].clear();
		score_rank[os] = 0;
		score_crank[os] = 0;
		last_update[os] = 0;
 
		// create a new group
		score_group[ns].insert(who);
		score_rank[ns] = rank;
		score_crank[ns] = 0;
		last_update[ns] = week;
	} else if (score_group[os].size() == 1 && score_group[ns].size()) {
		// single to group
		crank[who] += score_rank[os]*(week-last_update[os]);
		crank[who] += score_crank[os];
		crank[who] -= score_rank[ns]*(week-last_update[ns]);
		crank[who] -= score_crank[ns];
 
		// remove the old group
		score_group[os].clear();
		score_rank[os] = 0;
		score_crank[os] = 0;
		last_update[os] = 0;
 
		// join the new group (whose rank doesn't change)
		// not like the new person exceeded their score
		score_group[ns].insert(who);
	} else if (score_group[os].size() >= 2 && score_group[ns].empty()) {
		// group to single, group loses a rank
		crank[who] += score_rank[os]*(week-last_update[os]);
		crank[who] += score_crank[os];
		score_group[os].erase(who);
		score_crank[os] += score_rank[os]*(week-last_update[os]);
		score_rank[os] += 1;
		last_update[os] = week;
 
		// create the new group
		score_group[ns].insert(who);
		score_rank[ns] = rank;
		score_crank[ns] = 0;
		last_update[ns] = week;
	} else {
		// group to group
		crank[who] += score_rank[os]*(week-last_update[os]);
		crank[who] += score_crank[os];
		crank[who] -= score_rank[ns]*(week-last_update[ns]);
		crank[who] -= score_crank[ns];
 
		// group loses a rank
		score_group[os].erase(who);
		score_crank[os] += score_rank[os]*(week-last_update[os]);
		score_rank[os] += 1;
		last_update[os] = week;
 
		// join the new group (whose rank doesn't change)
		// not like the new person exceeded their score
		score_group[ns].insert(who);
	}
}
 
void print_debug() {
	printf("after week %d\n", week);
	for (int i = 1; i <= n; i++) {
		printf("score[%d] = %d, crank[%d] = %d\n", i, score[i], i, crank[i]);
	}
	for (auto& [k, v] : score_group) {
		printf("in score %d:", k);
		for (int who : v) {
			printf(" %d", who);
		}
		printf("\n");
		printf("\tscore_rank[%d] = %d\n", k, score_rank[k]);
		printf("\tscore_crank[%d] = %d\n", k, score_crank[k]);
		printf("\tlast_update[%d] = %d\n", k, last_update[k]);
	}
}
 
int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> w;
	last_update[1] = 1;
	score_rank[1] = 1;
	for (int i = 1; i <= n; i++) {
		score_group[1].insert(i);
		score[i] = 1;
	}
	for (week = 1; week <= w; week++) {
		cin >> k;
		while (k--) {
			cin >> c;
			bump(c);
		}
		ID print_debug();
	}
 
	for (auto& [k, v] : score_group) {
		for (int who : v) {
			crank[who] += ((week)-last_update[k])*score_rank[k];
			crank[who] += score_crank[k];
		}
	}
 
	for (int i = 1; i <= n; i++) {
		printf("%.12Lf\n", ((long double)crank[i])/w);
	}
}