#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 1011
 
int p[MAX_SIZE];
int a[MAX_SIZE];
set<int> st1;
set<int> st2;
int main() {
    int n, T, i;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        st1.clear();
        st2.clear();
        bool valid=false;
        for(i = 1; i <= n; ++i) {
            scanf("%d", &p[i]);
            st2.insert(p[i]);
            a[p[i]] =i;
        }
        st1.insert(p[1]);
        st2.erase(p[1]);
        for(i = 2; i < n; ++i){
            st2.erase(p[i]);
            if(*st1.begin() < p[i] && p[i] > *st2.begin()){
                valid=true;
                break;
            }
            st1.insert(p[i]);
        }
        printf("%s\n", valid?"YES":"NO");
        if (valid) {
            printf("%d %d %d\n", a[*st1.begin()], i, a[*st2.begin()]);
        }
    }
}

