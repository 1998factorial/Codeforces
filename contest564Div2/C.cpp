#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <complex>
//#include <unordered_set>
#define REP(i,a,b) for(int i=a;i<b;i++)
#define RREP(i,a,b) for(int i=a;i>=b;i--)
#define FILL(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
const int maxn=2e5+10;
int n,a[maxn],b[maxn],p[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<n+1;i++)scanf("%d",&a[i]),p[a[i]]=0;
	for(int i=1;i<n+1;i++)scanf("%d",&b[i]),p[b[i]]=i;
	if(p[1]){
		int i=2;
		for(i;p[i]==p[1]+i-1;++i);
			
	}
	return 0;
}