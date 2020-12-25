#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int N , P , K;
array<int , 3> eve[maxn];
ll B[maxn];

// sort by b[i] <= b[i + 1] , if b[i] = b[i + 1] then a[i] >= a[i + 1]
// once we know the first task the teacher will obey, we know which tasks
// he will not obey, and we just need to find the larges K - 1 a[j] in 
// [i + 1 , N]

int main(){
    scanf("%d %d %d" , &N , &P , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d" , &eve[i][0] , &eve[i][1]);
        eve[i][2] = i;
    }
    sort(eve + 1 , eve + 1 + N , [&](array<int , 3>& lhs , array<int , 3>& rhs){
        if(lhs[1] != rhs[1])return lhs[1] < rhs[1]; // sort by b first
        return lhs[0] > rhs[0];
    });
    for(int i = 1; i <= N; ++i){
        B[i] = B[i - 1] + eve[i][1];
    }
    int best = -1 , D = P - K;
    ll maxa = 0 , maxb = 0 , asum = 0 , bsum = 0;
    multiset<int> vis;
    for(int i = N; i >= 1; --i){
        if(vis.size() >= K - 1 && i - D - 1 >= 0){
            if(maxa < asum + eve[i][0]){
                maxa = asum + eve[i][0];
                best = i;
            }
            if(maxa == asum + eve[i][0] && maxb < B[i - 1] - B[i - D - 1]){
                maxb = B[i - 1] - B[i - D - 1];
                best = i;
            }   
        }
        asum += eve[i][0];
        vis.insert(eve[i][0]);
        if(vis.size() > K - 1){
            auto it = vis.begin();
            asum -= *it;
            vis.erase(vis.find(*it));
        }
    }
    ID printf("maxa = %lld , maxb = %lld , best = %d\n" , maxa , maxb , best);
    vector<int> ans;
    for(int i = best - D; i <= best; ++i){
        ans.push_back(eve[i][2]);
    }
    // find the largest K - 1 a[j] in eve[best + 1 .. N]
    multiset<array<int , 2>> largest;
    for(int i = best + 1; i <= N; ++i){
        largest.insert({eve[i][0] , eve[i][2]});
        if(largest.size() > K - 1){
            auto it = largest.begin();
            largest.erase(largest.find(*it));
        }
    }
    for(auto& e : largest)ans.push_back(e[1]);
    for(int i : ans)printf("%d " , i);
    printf("\n");
}
