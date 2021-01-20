#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
#define double long double
using namespace std;
 
ll x[MAX_SIZE], y[MAX_SIZE];
int N;
 
struct node {
    double a, b, c;
    bool operator < (node other) const {
        return c < other.c;
    }
};
 
double getmiddle(double a, double b) {
    return -0.5 * b / a; 
}
 
int main() {
    int i;
    scanf("%d", &N);
    double ans = 0;
    for (i = 1; i <= N; ++i) {
        scanf("%I64d%I64d", &x[i], &y[i]);
        ans = ans + 1.0 * x[i] * x[i];
        ans = ans + 1.0 * y[i] * y[i];
    }
    
    priority_queue<node> q;
 
    for (i = 1; i <= N; ++i) {
        if (q.empty()) {
            q.push(node{1, -2.0 * x[i], getmiddle(1, -2.0 * x[i])});
        } else {
            node nd = node{1, -2.0 * x[i], getmiddle(1, -2.0 * x[i])};
            while (!q.empty() && q.top().c > nd.c) {
                auto pr = q.top();
                q.pop();
                nd = node{nd.a + pr.a, nd.b + pr.b, getmiddle(nd.a + pr.a, nd.b + pr.b)};
            }
            q.push(nd);
        }
    }
 
    while (!q.empty()) {
        auto nd = q.top();
        ans = ans - 0.25 * nd.b * nd.b / nd.a;
        q.pop();
    }
 
    for (i = 1; i <= N; ++i) {
        if (q.empty()) {
            q.push(node{1, -2.0 * y[i], getmiddle(1, -2.0 * y[i])});
        } else {
            node nd = node{1, -2.0 * y[i], getmiddle(1, -2.0 * y[i])};
            while (!q.empty() && q.top().c > nd.c) {
                auto pr = q.top();
                q.pop();
                nd = node{nd.a + pr.a, nd.b + pr.b, getmiddle(nd.a + pr.a, nd.b + pr.b)};
            }
            q.push(nd);
        }
    }
 
    while (!q.empty()) {
        auto nd = q.top();
        ans = ans - 0.25 * nd.b * nd.b / nd.a;
        q.pop();
    }
 
    printf("%.9Lf\n", ans);
    return 0;
}