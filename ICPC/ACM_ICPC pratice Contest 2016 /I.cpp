#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e3 + 10;

/*
	number of good triples is at most O(N) due to the probablity
*/

struct triple{
    int x , y , z;
    triple(){}
    triple(int a , int b , int c) : x(a) , y(b) , z(c) {}
    bool operator < (const triple& rhs) const {
        if(rhs.x != x)return x < rhs.x;
        if(rhs.y != y)return y < rhs.y;
        return z < rhs.z;
    }
};

int A[maxn][3];
int DP[maxn];
int N;

int main() {
    int t; cin >> t;
    while(t--){
        cin >> N;
        vector<int> pos[maxn][3];
        vector<triple> ts;
        for(int j = 0; j < 3; ++j){
            for(int i = 1; i <= N; ++i){
                cin >> A[i][j];
                pos[A[i][j]][j].push_back(i);
            }
        }
        for(int i = 1; i <= N; ++i){
            for(int x : pos[i][0]){
                for(int y : pos[i][1]){
                    for(int z : pos[i][2]){
                        ts.emplace_back(x , y , z);
                    }
                }
            }
        }
        sort(ts.begin() , ts.end());
        int ans = 0;
        for(int i = 0; i < ts.size(); ++i){
            DP[i + 1] = 1;
            for(int j = i - 1; j >= 0; --j){
                if(
                    ts[i].x > ts[j].x &&
                    ts[i].y > ts[j].y &&
                    ts[i].z > ts[j].z
                ){
                    DP[i + 1] = max(DP[i + 1] , DP[j + 1] + 1);
                }
            }
            ans = max(ans , DP[i + 1]);
        }
        cout << ans << endl;
    }
}
