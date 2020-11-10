/*
    Constructive
    largest diameter comes from a chain like graph
    check if the graph can be connected first
    Then, we get all the leaf and internal nodes
    diameter = N - # leaf - 1 + min(2 , # leaf)
    then we just build up the internal chain and try to connect as many
    leaves toward the 2 end points of the chain as possible.
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;
int N;
int a[505];

int main(){
    scanf("%d" , &N);
    int sum = 0;
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        sum += a[i];
    }
    if(sum < 2 * N - 2){
        printf("NO\n");
        return 0;
    }
    vector<int> leaf;
    for(int i = 1; i <= N; ++i){
        if(a[i] < 2){
            a[i] = 0;
            leaf.push_back(i);
        }
    }
    int n = leaf.size();
    int d = N - n - 1 + min(2 , n);
    printf("YES %d\n%d\n" , d , N - 1);
    int pre = -1;
    if(leaf.size()){
        pre = leaf.back();
        leaf.pop_back();
    }
    for(int i = 1; i <= N; ++i){
        if(a[i] > 1){
            if(pre != -1){
                printf("%d %d\n" , i , pre);
                --a[pre]; --a[i];
            }
            pre = i;
        }
    }
    for(int i = N; i >= 1; --i){
        while(leaf.size() && a[i] > 0){
            --a[i];
            printf("%d %d\n" , leaf.back() , i);
            leaf.pop_back();
        }
    }
}
