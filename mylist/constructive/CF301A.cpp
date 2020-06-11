/*
    Constructive
    it is easy to see that at the end, either all negative numbers can be changed to positive,
    or we will left one negative number unchanged.
    We can see that when N is odd, we are guranteed that all numbers can be changed.
    And we can see that only when N is even and the number of non positivee 
*/
#include <bits/stdc++.h>
using namespace std;

int N;
int a[500];

int main(){
    cin >> N;
    vector<int> neg , pos;
    for(int i = 1; i <= N * 2 - 1; ++i){
        cin >> a[i];
        if(a[i] <= 0){
            neg.push_back(-a[i]);
        }
        else if(a[i] > 0){
            pos.push_back(a[i]);
        }
    }
    sort(neg.begin() , neg.end());
    sort(pos.begin() , pos.end());
    int sum = 0;
    int K = neg.size();
    K = K % N;
    if(K % 2 == 1 && N % 2 == 0){
        int v = 1001;
        if(pos.size())v = min(v , pos[0]);
        if(neg.size())v = min(v , neg[0]);
        sum -= 2 * v;
    }
    for(int i : pos)sum += i;
    for(int i : neg)sum += i;
    cout << sum << endl;
}
