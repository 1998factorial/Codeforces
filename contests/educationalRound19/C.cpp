#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 100111
 
stack<char> st;
multiset<char> pend;
vector<char> ret;
char s[MAX_SIZE];
int N;
 
int main() {    
    int i;
    scanf("%s", s);
    N = strlen(s);
    for (i = 0 ; i < N; ++i) {
        pend.insert(s[i]);
    }
    // invariant stack.top() > *pend.begin()
    for (i = 0 ; i < N; ++i) {
        pend.erase(pend.find(s[i]));
        st.push(s[i]);
        while (!st.empty() && !pend.empty()) {
            if (st.top() <= *pend.begin()) {
                ret.push_back(st.top());
                st.pop();
            } else {
                break;
            }
        }    
    }
 
    while (!st.empty()) {
        ret.push_back(st.top());
        st.pop();
    }
 
    for (auto v : ret) {
        cout << v;
    }
    cout << endl;
    return 0;
}