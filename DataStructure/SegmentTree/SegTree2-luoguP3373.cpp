#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 5;
struct SegTree{
	int sum,add,mul,l,r; // lazy tag
}tr[N<<2];
int n,m,mod,a[N];
void MOD(int &x){x = (x%mod+mod)%mod;}
void pushup(int p){
	tr[p].sum = tr[p<<1].sum + tr[p<<1|1].sum;
	MOD(tr[p].sum);
}
void pushdown(int p){
	tr[p<<1].sum = tr[p<<1].sum * tr[p].mul + (
		tr[p<<1].r - tr[p<<1].l + 1
	) * tr[p].add;
	tr[p<<1].mul *= tr[p].mul;
	tr[p<<1].add = tr[p].mul * tr[p<<1].add + tr[p].add;
	MOD(tr[p<<1].sum);
	MOD(tr[p<<1].mul);
	MOD(tr[p<<1].add);
	
	tr[p<<1|1].sum = tr[p<<1|1].sum * tr[p].mul + (
		tr[p<<1|1].r - tr[p<<1|1].l + 1
	) * tr[p].add;
	tr[p<<1|1].mul *= tr[p].mul;
	tr[p<<1|1].add = tr[p].mul * tr[p<<1|1].add + tr[p].add;
	MOD(tr[p<<1|1].sum);
	MOD(tr[p<<1|1].mul);
	MOD(tr[p<<1|1].add);
	
	tr[p].mul = 1;
	tr[p].add = 0;
	
}
void build(int p,int l,int r){
	tr[p].l = l,tr[p].r = r,tr[p].add = 0,tr[p].mul = 1;
	if(l == r){
		tr[p].sum = a[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}
void modify(int p,int l,int r,int add,int mul){
	if(l<=tr[p].l && r>=tr[p].r){
		tr[p].sum = tr[p].sum * mul + (
			tr[p].r - tr[p].l + 1
		) * add;
		tr[p].mul *= mul;
		tr[p].add = tr[p].add * mul + add;
		MOD(tr[p].sum);
		MOD(tr[p].mul);
		MOD(tr[p].add);
		return ;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)modify(p<<1,l,r,add,mul);
	if(r > mid)modify(p<<1|1,l,r,add,mul);
	pushup(p);
}
int query(int p,int l,int r){
	int sum = 0;
	if(l<=tr[p].l && r>=tr[p].r)return  tr[p].sum;
	int mid = (tr[p].l + tr[p].r) >> 1;
	pushdown(p);
	if(l <= mid)sum += query(p<<1,l,r);
	if(r > mid)sum += query(p<<1|1,l,r);
	MOD(sum);
	return sum;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>mod;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int op,x,y,k;
		cin>>op>>x>>y;
		if(op == 1){
			cin>>k;
			modify(1,x,y,0,k);
		}
		if(op == 2){
			cin>>k;
			modify(1,x,y,k,1);
		}
		if(op == 3){
			int sum = query(1,x,y);
			MOD(sum);
			cout<<sum<<"\n";
		}
	}
	return 1-1;
}
