#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
int a[maxn] , N;

int main(){
    vector<int> ans;
    map<int , int> cnt;
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(int i = 1; i <= N; ++i){
        if(a[i] > 0){
            ++cnt[a[i]];
        }
        else if(a[i] < 0){
            if(cnt[-a[i]] <= 0){
                printf("No\n");
                return 0;
            }
            else{
                --cnt[-a[i]];
            }
        }
        else{
            // find the next neg that we do not have
            int tg = 1;
            map<int , int> tmp;
            for(auto& e : cnt){
                tmp[e.first] = e.second;
            }
            for(int j = i + 1; j <= N; ++j){
                if(a[j] < 0){   
                    if(tmp[-a[j]] <= 0){
                        tg = -a[j];
                        break;
                    }
                    else{
                        --tmp[-a[j]];
                    }
                }
                else if(a[j] > 0){
                    ++tmp[a[j]];
                }
            }
            ++cnt[tg];
            ans.push_back(tg);
        }
    }
    printf("Yes\n");
    for(int i : ans){
        printf("%d " , i);
    }
    printf("\n");
}