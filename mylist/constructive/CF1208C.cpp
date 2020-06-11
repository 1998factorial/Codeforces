#include <bits/stdc++.h>
using namespace std;

int N;

int tmp[4][4];
int a[1005][1005];
int row[1005] , col[1005];

int main(){
    cin >> N;
    deque<int> q;
    for(int i = 0; i < 4; ++i)q.push_back(i);
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            tmp[i][j] = q[j];
        }
        int j = q.front();
        q.pop_front();
        q.push_back(j);
    }
    int cnt = 0;
    for(int i = 1; i <= N; i += 4){
        for(int j = 1; j <= N; j += 4){
            for(int x = 0; x < 4; ++x){
                for(int y = 0; y < 4; ++y){
                    a[i + x][j + y] = cnt + tmp[x][y];
                }
                cnt += 4;
            }
        }
    }

    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    /*set<int> s;
    for(int i = 1; i <= N; ++i){
        int r = 0;
        for(int j = 1; j <= N; ++j){
            r ^= a[i][j];
        }
        s.insert(r);
    }
    for(int i = 1; i <= N; ++i){
        int r = 0;
        for(int j = 1; j <= N; ++j){
            r ^= a[j][i];
        }
        s.insert(r);
    }
    if(s.size() == 1){
        cout << "OK\n";
    }
    else{
        cout << "NO\n";
    }*/
}
