#include <bits/stdc++.h>
using namespace std;
#define MAXN 5005
#define ID if (0)
#define sz(x) ((int)(x).size())
#define ii pair<int, int>
#define x first
#define y second
int n;
int secret_evn[MAXN];
int secret_odd[MAXN];
// return true if e[i] < o[j]
int qcount = 0;
bool islt(int i, int j) {
    ID {
        qcount++;
        return secret_evn[i] < secret_odd[j];
    } else {
        cout << "? " << i << ' ' << j << endl;
        cout.flush();
        char c;
        cin >> c;
        return c == '<';
    }
}
void answer(vector<int> values) {
    ID {
        assert(values.size() == n);
        for (int i = 0; i < values.size(); i++) {
            if (i%2==0) assert(values[i] == secret_odd[(i/2)+1]);
            else assert(values[i] == secret_evn[(i/2)+1]);
        }
    } else {
        cout << '!';
        for (int x : values) cout << ' ' << x;
        cout << endl;
        cout.flush();
    }
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int partition_odd(int pivot, vector<int>& odd, int s, int e) {
    vector<int> lt; // less than pivot
    vector<int> gt;
    for (int i = s; i <= e; i++) {
        if (islt(pivot,odd[i])) gt.push_back(odd[i]);
        else lt.push_back(odd[i]);
    }
    for (int i = 0; i < lt.size(); i++) odd[i+s] = lt[i];
    for (int i = 0; i < gt.size(); i++) odd[i+s+lt.size()] = gt[i];
    return max(2,(s+sz(lt))*2);
}
// partition evens based on pivot, returns the (odd) value of the pivot
int partition_evn(int pivot, vector<int>& evn, int s, int e) {
    vector<int> lt; // less than pivot
    vector<int> gt;
    for (int i = s; i <= e; i++) {
        if (islt(evn[i],pivot)) lt.push_back(evn[i]);
        else gt.push_back(evn[i]);
    }
    for (int i = 0; i < lt.size(); i++) evn[i+s] = lt[i];
    for (int i = 0; i < gt.size(); i++) evn[i+s+lt.size()] = gt[i];
    return (s+sz(lt))*2+1;
}
int main() {
    cin >> n;
    ID {
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 0) secret_evn[i/2] = i;
            else secret_odd[(i+1)/2] = i;
        }
        shuffle(secret_odd+1,secret_odd+1+(n/2)+(n%2==1),rng);
        shuffle(secret_evn+1,secret_evn+1+(n/2),rng);
    }
    if (n == 1) {
        answer({1});
    }
    vector<int> evn;
    vector<int> odd;
    for (int i = 1; i <= n; i++) {
        if (i%2==0) evn.push_back(i/2);
        else odd.push_back((i+1)/2);
    }
    set<ii> s;
    for (int i = 1; i <= sz(evn); i++) {
        if (sz(s) <= 1) {
            int value = partition_odd(i, odd, 0, sz(odd)-1);
            s.insert({value,i});
        } else {
            vector<ii> v;
            for (ii x : s) v.push_back(x);
            int lo = 0;
            int hi = sz(v)-1;
            int best = -1;
            while (hi >= lo) {
                int mid = (hi+lo)/2;
                // assert(v[mid].x/2 < sz(odd));
                if ((v[mid].x/2) >= sz(odd) || islt(i,odd[v[mid].x/2])) {
                    hi = mid-1;
                } else {
                    best = mid;
                    lo = mid+1;
                }
            }
            int start = 0;
            int end = sz(odd)-1;
            if (best == -1) {
                end = (v[1].x/2)-1;
            } else if (best+2 >= sz(v)) {
                start = (v[best].x/2);
            } else {
                start = (v[best].x/2);
                end = (v[best+2].x/2)-1;
            }
            if (start <= end) {
                int value = partition_odd(i, odd, start, end);
                s.insert({value,i});
            } else {
                int value = start*2;
                s.insert({value,i});
                cout << i << ' ' << secret_evn[i] << ' ' << value << ' ' << best << ' ' << v[best].x << endl;
                assert(secret_evn[i] == value);
            }
            // cout << start << ' ' << end << endl;
            // assert(secret_evn[i] == value);
        }
    }
    // now odd should be completely sorted
    ID {
        cout << "query count: " << qcount << endl;
        cout << "sorted odd:";
        for (int x : odd) cout << ' ' << secret_odd[x];
        cout << endl;
    }
    vector<ii> ans_evn;
    for (ii x : s) ans_evn.push_back(x);
    sort(ans_evn.begin(), ans_evn.end(), [&](ii a, ii b) {return a.y < b.y;});
    cout << '!';
    for (ii x : ans_evn) cout << ' ' << x.x;
    vector<int> ans_odd(sz(odd),0);
    for (int i = 0; i < sz(odd); i++) {
        ans_odd[odd[i]-1] = i*2+1;
    }
    for (int x : ans_odd) cout << ' ' << x;
    cout << endl;
    cout.flush();
    ID {
        cout << "actual values:" << endl;
        cout << '!';
        for (int i = 1; i <= sz(evn); i++) cout << ' ' << secret_evn[i];
        for (int i = 1; i <= sz(odd); i++) cout << ' ' << secret_odd[i];
        cout << endl;
    }
}