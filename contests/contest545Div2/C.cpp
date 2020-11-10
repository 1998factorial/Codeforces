#include <bits/stdc++.h>
#define ID if(0)
using namespace std;

int N , M;
int a[1005][1005];
vector<int> col[1005] , row[1005];

int solve(int i , int j){
    // find number less than a[i][j] on row i
    int l = 0 , r = row[i].size() - 1 , x1 = 0 , x2 = 0 , y1 = 0 , y2 = 0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(row[i][mid] < a[i][j]){
            x1 = mid + 1;
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    // find number less than a[i][j] on col j
    l = 0 , r = col[j].size() - 1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(col[j][mid] < a[i][j]){
            y1 = mid + 1;
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    // find number greater than a[i][j] on row i
    l = 0 , r = row[i].size() - 1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(row[i][mid] > a[i][j]){
            x2 = row[i].size() - 1 - mid + 1;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    // find number greater than a[i][j] on row j
    l = 0 , r = col[j].size() - 1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(col[j][mid] > a[i][j]){
            y2 = col[j].size() - 1 - mid + 1;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return 1 + max(x1 , y1) + max(x2 , y2); 
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            scanf("%d" , &a[i][j]);
        }
    }   
    for(int i = 1; i <= N; ++i){
        set<int> vis;
        for(int j = 1; j <= M; ++j){
            vis.insert(a[i][j]);
        }
        for(int j : vis){
            row[i].push_back(j);
        }
    }
    for(int i = 1; i <= M; ++i){
        set<int> vis;
        for(int j = 1; j <= N; ++j){
            vis.insert(a[j][i]);
        }
        for(int j : vis){
            col[i].push_back(j);
        }
    }
    ID for(int i = 1; i <= N; ++i){
        printf("at row %d\n" , i);
        for(int j : row[i]){
            printf("%d " , j);
        }
        printf("\n");
    }
    ID for(int i = 1; i <= M; ++i){
        printf("at col %d\n" , i);
        for(int j : col[i]){
            printf("%d " , j);
        }
        printf("\n");
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            printf("%d " , solve(i , j));
        }
        printf("\n");
    }
}