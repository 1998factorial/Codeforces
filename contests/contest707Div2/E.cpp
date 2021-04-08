#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int N , M;
    cin >> N >> M;
    vector<vector<int>> a(N , vector<int>(M));
    vector<vector<int>> b(N , vector<int>(M));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cin >> b[i][j];
        }
    }
    int same = 1;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(a[i][j] != b[i][j])same = 0;
        }
    }
    if(same == 1){
        cout << 0 << endl;
        exit(0);
    }
    for(int i = 0; i < M; ++i){
        vector<int> t1 , t2;
        for(int j = 0; j < N; ++j){
            t1.push_back(a[j][i]);
            t2.push_back(b[j][i]);
        }
        sort(t1.begin() , t1.end());
        sort(t2.begin() , t2.end());
        for(int j = 0; j < N; ++j){
            if(t1[j] != t2[j]){
                cout << -1 << endl;
                exit(0);
            }
        }
    }
    vector<int> deg(M) , vis(N);
    queue<int> q;
    for(int i = 0; i < M; ++i){
        for(int j = 1; j < N; ++j){
            if(b[j - 1][i] > b[j][i]){
                ++deg[i];
            }
        }
        if(deg[i] == 0)q.push(i);
    }
    vector<int> ans;
    while(!q.empty()){
        int c = q.front();
        q.pop();
        ans.push_back(c);
        for(int i = 0; i < N - 1; ++i){
            if(vis[i] == 0 && b[i][c] < b[i + 1][c]){
                for(int j = 0; j < M; ++j){
                    if(b[i][j] > b[i + 1][j]){
                        --deg[j];
                        if(deg[j] == 0){
                            q.push(j);
                        }
                    }
                }
                vis[i] = 1;
            }
        }
    }
    reverse(ans.begin() , ans.end());
    vector<int> id;
    for(int i = 0; i < N; ++i)id.push_back(i);
    for(int i : ans){
        vector<int> nid = id;
        vector<array<int , 3>> t;
        int cn = 0;
        for(int j : id){
            t.push_back({a[j][i] , j , cn});
            ++cn;
        }
        sort(nid.begin() , nid.end() , [&](int l , int r){
            if(t[l][0] == t[r][0]){
                return t[l][2] < t[r][2];
            }
            return t[l][0] < t[r][0];
        });
        id.clear();
        for(int i : nid){
            id.push_back(t[i][1]);
        }
    }
    vector<vector<int>> c;
    for(int i : id){
        c.push_back(a[i]);
    }
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(c[i][j] != b[i][j]){
                cout << -1 << endl;
                exit(0);
            }
        }
    }
    cout << (int)ans.size() << endl;
    for(int i : ans)cout << i + 1 << " ";
    cout << endl;
}




/*

2 3 2
1 3 3
1 1 2

2 3 2 
1 1 2 
1 3 3 

1 1 2
2 3 2
1 3 3

1 1 2
1 3 3
2 3 2

*/