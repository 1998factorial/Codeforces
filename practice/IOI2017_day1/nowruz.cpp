#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define endl '\n'

ll n, m, k;

char grid[1200][1200];
char grid2[1200][1200];
char bestGrid[1200][1200];
ll visited[1200][1200];
ll printed[1200];

ld bestScore, score, lastDone;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	cerr << setprecision(5) << endl;


	cin >> n >> m >> k;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> grid[i][j];
		}
	}
	for(int i = 0; i <= n+1-1000+1000; i++) {
		for(int j = 0; j <= m+1-1000+1000; j++) {
			if(i==0||i==n+1-1000+1000||j==0||j==m+1-1000+1000)
				grid[i][j] = '#';
			if(grid[i][j] != '#')
				grid[i][j] = 'X';
		}
	}

	for(int i = 0; i <= n+1; i++)
		for(int j = 0; j <= m+1; j++)
			grid2[i][j] = grid[i][j];

//	for(int I = 1; I <= n; I++) {
//		for(int J = 1; J <= m; J++) {
	srand(time(NULL));
	ll toDo = 200000000/((n*m));
	ll totalToDo = toDo;
	while((toDo-->0)&&bestScore<100) {
			ll I = (rand()%n) + 1;
			ll J = (rand()%m) + 1;
			for(int i = 0; i <= n+1; i++)
				for(int j = 0; j <= m+1; j++)
					grid[i][j] = grid2[i][j];
			memset(visited, 0, sizeof(visited));
			queue<pair<ll,ll>> q;
			q.push({I, J});
			while(!q.empty()) {
				ll i = q.front().first;
				ll j = q.front().second;
				q.pop();

				if(grid[i][j] == '#' || grid[i][j] == '.' || ((ll)(rand()*0.9))%(((max(n, m)*3)))==1) continue;

				if(visited[i+1][j  ]+
				   visited[i-1][j  ]+
				   visited[i  ][j+1]+
				   visited[i  ][j-1] > 1) {
					grid[i][j] = 'X';
					continue;
				} else {
					visited[i][j]=1;
					grid[i][j]='.';
					q.push({i+1, j  });
					q.push({i  , j+1});
					q.push({i-1, j  });
					q.push({i  , j-1});
				}
			}

			ll cnt = 0;
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					if(grid[i][j]=='.' &&
					   visited[i  ][j-1]+
					   visited[i-1][j  ]+
					   visited[i+1][j  ]+
					   visited[i  ][j+1] == 1)
						cnt++;
				}
			}
			ld score = min((ld)100, 100*(ld)cnt/k);

			if(score>bestScore) {
				bestScore = score;
				for(int i = 0; i <= n+1; i++)
					for(int j = 0; j <= m+1; j++)
						bestGrid[i][j] = grid[i][j];
			}
			if((ll)(((ld)toDo/totalToDo*100))/10>(ll)(((ld)(toDo-1)/totalToDo*100))/10) {
				cerr << (ll)((ld)toDo/totalToDo*100) << "%: " << bestScore << endl;
			}

			ll done = (((ld)I*m)+J)/(((ld)n*m)+m)*100;
			//if((ll)lastDone/10<(ll)done/10)
			lastDone = done;
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cout << bestGrid[i][j];
		}
		cout << endl;
	}
}
