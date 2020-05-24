#include <bits/stdc++.h>
#define MAX_SIZE 2097312
#define MID ((l + r) >> 1)
#define LEFT (id << 1)
#define RIGHT (id << 1 | 1)
using namespace std;

int N , Q;
int tree[MAX_SIZE];
int a[MAX_SIZE >> 1];

void build(int l , int r , int id){
	if(l > r)return;
	if(l == r){
		tree[id] = a[l];
	}
	else{
		build(l , MID , LEFT);
		build(MID + 1 , r , RIGHT);
		tree[id] = tree[LEFT] + tree[RIGHT];
	}
}

void add(int l , int r , int pos , int id){
	if(l > r)return;
	if(l == r && l == pos){
		++tree[id];
		return;
	}
	if(pos <= MID){
		add(l , MID , pos , LEFT);
	}
	else{
		add(MID + 1 , r , pos , RIGHT);
	}
	tree[id] = tree[LEFT] + tree[RIGHT];
}

void del(int l , int r , int k , int id){
	if(l > r)return;
	if(l == r){
		--tree[id];
		return;
	}
	if(tree[LEFT] >= k){
		del(l , MID , k , LEFT);
	}
	else{
		del(MID + 1 , r , k - tree[LEFT] , RIGHT);
	}
	tree[id] = tree[LEFT] + tree[RIGHT];
}

int get(int l , int r , int id){
	if(l > r) return 0;
	if(l == r) {
		return l;
	}
	if(tree[LEFT] > 0) {
		return get(l, MID, LEFT);
	}
	return get(MID + 1, r, RIGHT);
}

int main(){
	scanf("%d %d" , &N , &Q);
	for(int i = 1; i <= N; ++i){
		int x; scanf("%d" , &x);
		++a[x];
	}
	build(1 , N , 1);
	for(int i = 1; i <= Q; ++i){
		int x;scanf("%d" , &x);
		if(x > 0){
			add(1 , N , x , 1);
		}
		else{
			del(1 , N , -x , 1);
		}
	}
	if(tree[1] <= 0){
		puts("0\n");
	}
	else{
		printf("%d\n" , get(1 , N , 1));
	}
}
