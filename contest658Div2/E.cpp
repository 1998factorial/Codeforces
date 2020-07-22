#include <bits/stdc++.h>
#define ID 1
using namespace std;
typedef pair<int , int> ii;

int N , X , Y;
int b[100005];
int a[100005];

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        vector<ii> ps;
        map<int , int> cnt;
        scanf("%d %d %d" , &N , &X , &Y);
        for(int i = 1; i <= N; ++i){
            scanf("%d" , &b[i]);
        }
        int unseen = 0;
        for(int i = 1; i <= N; ++i){
            ++cnt[b[i]];
        }
        for(auto& e : cnt){
            ps.emplace_back(e.second , e.first);
        }
        sort(ps.begin() , ps.end());
        reverse(ps.begin() , ps.end());
        for(int i = 1; i <= N + 1; ++i){
            if(cnt[i] == 0){
                unseen = i;
                break;
            }
        }
        int nfill = X;
        map<int , int> need;
        for(auto& e : ps){
            int color = e.second;
            int num = e.first;
            int canput = (nfill >= num) ? num : nfill;
            need[color] = canput;
            if(canput == 0)break;
            e.first -= canput;
            nfill -= canput;
        }
        if(ID)for(auto& e : need){
            cout << e.first << " " << e.second << endl;
        }
        int nderange = Y - X;
        for(int i = ps.size(); i >= 0; --i){
            
        }
    }
}
