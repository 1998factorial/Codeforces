/*
    Constructive
    we want the number of characters that appear odd number of times to be at most 1
    so if we have at least 2 such char, we need to make 2 of them even each time.
    We also want lexicographically smallest, so it make sense to exchange the largest odd char
    and smallest odd char each iteration.
    At the end, we aware of the difference of the case when 0 char is odd, and 1 char is odd.
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
char ans[maxn];
int N;
int cnt[26];

int main(){
    string s;
    cin >> s;
    N = s.size();
    for(int i = 0; i < N; ++i){
        ++cnt[s[i] - 'a'];
    }
    deque<int> q;
    for(int i = 0; i < 26; ++i){
        if(cnt[i] & 1)q.push_back(i);
    }
    while(q.size() > 1){
        ++cnt[q.front()];
        --cnt[q.back()];
        q.pop_front();
        q.pop_back();
    }
    int l = 1 , r = N;
    if(q.size() == 0){
        for(int i = 0; i < 26; ++i){
            for(int j = 1; j <= cnt[i]; ++j){
                if(j & 1)ans[l++] = 'a' + i;
                else ans[r--] = 'a' + i;
            }
        }
    }
    else{
        int x = q.front();
        for(int i = 0; i < 26; ++i){
            int up = cnt[i] / 2 * 2;
            for(int j = 1; j <= up; ++j){
                if(j & 1)ans[l++] = 'a' + i;
                else ans[r--] = 'a' + i;
            }
        }
        ans[l] = 'a' + x;
    }
    for(int i = 1; i <= N; ++i){
        printf("%c" , ans[i]);
    }
    printf("\n");
}
