#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int N;
int a[maxn];
vector<array<int , 2>> v[5000005]; 

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    // if number of pairs of (i , j) that sums to S
    // is at least 4, then there will be a solution
    for(int i = 1; i <= N; ++i)cin >> a[i];
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            int x = a[i] + a[j];
            v[x].push_back({i , j});
            if(v[x].size() <= 1)continue;
            for(int l = 0; l < v[x].size(); ++l){
                for(int r = l + 1; r < v[x].size(); ++r){
                    int x1 = v[x][l][0];
                    int y1 = v[x][l][1];
                    int x2 = v[x][r][0];
                    int y2 = v[x][r][1];
                    if(x1 == x2)continue;
                    if(x1 == y2)continue;
                    if(y1 == x2)continue;
                    if(y1 == y2)continue;
                    cout << "YES" << endl;
                    cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
                    exit(0);
                }
            }
            //x , a 
            //x , b 
            //x , c
            //x , d
            if(v[x].size() >= 4){
                for(int l = 0; l < 4; ++l){
                    int cnt = 0;
                    for(int r = 0; r < 4; ++r){
                        if(v[x][r][0] == v[x][l][0])++cnt;
                        if(v[x][r][1] == v[x][l][0])++cnt;
                    }
                    if(cnt >= 4){
                        vector<int> ans;
                        for(int r = 0; r < 4; ++r){
                            if(v[x][r][0] != v[x][l][0])ans.push_back(v[x][r][0]);
                            if(v[x][r][1] != v[x][l][0])ans.push_back(v[x][r][1]);
                        }
                        cout << "YES" << endl;
                        for(int jj : ans)cout << jj << " ";
                        cout << endl;
                        exit(0);
                    }
                    cnt = 0;
                    for(int r = 0; r < 4; ++r){
                        if(v[x][r][0] == v[x][l][1])++cnt;
                        if(v[x][r][1] == v[x][l][1])++cnt;
                    }
                    if(cnt >= 4){
                        vector<int> ans;
                        for(int r = 0; r < 4; ++r){
                            if(v[x][r][0] != v[x][l][1])ans.push_back(v[x][r][0]);
                            if(v[x][r][1] != v[x][l][1])ans.push_back(v[x][r][1]);
                        }
                        cout << "YES" << endl;
                        for(int jj : ans)cout << jj << " ";
                        cout << endl;
                        exit(0);
                    }
                }
            }
        }
    }    
    cout << "NO" << endl;
}