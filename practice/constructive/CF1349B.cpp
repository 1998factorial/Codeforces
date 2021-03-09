#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int N , K;
        cin >> N >> K;
        vector<int> a(N + 1);
        vector<int> pos;
        for(int i = 1; i <= N; ++i){
            cin >> a[i];
            if(a[i] == K)pos.push_back(i);
        }
        if(pos.size() == 0){
            cout << "no" << endl;
            continue;
        }
        if(N == 1){
            cout << "yes" << endl;
            continue;
        }
        int ok = 0;
        for(int i = 1; i < pos.size(); ++i){
            if(pos[i] == pos[i - 1])ok = 1;
        }
        if(ok){
            cout << "yes" << endl;
            continue;
        }
        // if we can make 2 consecutive K , we are done
        // if we can make 2 consecutive K + x , then we can make 
        // a lot of K + x, and eventually it will touch some index with K
        // and we will make all of them K
        int ok2 = 0;
        for(int i = 1; i <= N; ++i){
            if(a[i] < K)continue;
            for(int j = 1; j <= 2; ++j){
                if(i - j >= 0 && a[i - j] >= K)ok2 = 1;
                if(i + j <= N && a[i + j] >= K)ok2 = 1;
            }
        }
        if(ok2){
            cout << "yes" << endl;
        }
        else{
            cout << "no" << endl;
        }
    }
}