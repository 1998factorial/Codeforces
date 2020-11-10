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
const int maxn=10050;
int a[maxn],n;

int main(){
	scanf("%d",&n);
	REP(i,0,2*n)scanf("%d",&a[i]);
	sort(a,a+2*n);
	int sum=0;
	REP(i,0,n)sum+=a[i];
	int sum2=0;
	REP(i,n,2*n)sum2+=a[i];
	if(sum!=sum2){
		REP(i,0,2*n)cout<<a[i]<<" ";
		cout<<endl;
	}
	else{
		cout<<-1<<endl;
	}
	return 0;
}
