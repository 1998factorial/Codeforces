#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int a[maxn] , b[maxn];
int N;
int ans[maxn] , ians[maxn];
vector<int> add[maxn] , del[maxn];

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d" , &a[i] , &b[i]);
        add[a[i]].push_back(i);
        del[b[i]].push_back(i);
    }
    priority_queue<ii , vector<ii> , greater<ii>> q;
    vector<pair<int , int>> possible_swaps;
    for(int i = 1; i <= N; ++i){
        for(int j : add[i]){
            q.push(make_pair(b[j] , j));
        }
        if(q.size() == 1){
            auto it = q.top();
            q.pop();
            ans[i] = it.second;
        }
        else if(q.size() > 1){
            auto it = q.top();
            q.pop();
            ans[i] = it.second;
            possible_swaps.emplace_back(it.second , q.top().second);
        }
    }
    for(int i = 1; i <= N; ++i){
        ians[ans[i]] = i;
    }
    for(auto& e : possible_swaps){
        int x = e.first , y = e.second;
        if(a[x] <= ians[y] && ians[y] <= b[x] && a[y] <= ians[x] && ians[x] <= b[y]){
            printf("NO\n");
            for(int i = 1; i <= N; ++i){
                printf("%d " , ians[i]);
            }
            printf("\n");
            swap(ians[x] , ians[y]);
            for(int i = 1; i <= N; ++i){
                printf("%d " , ians[i]);
            }
            printf("\n");
            return 0;
        }
    }
    printf("YES\n");
    for(int i = 1; i <= N; ++i){
        printf("%d " , ians[i]);
    }
    printf("\n");
}
