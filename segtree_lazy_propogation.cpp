#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<int>> vii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vpi;

#define INF 1000000000
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define rep(i,a,b) for (int i = a; i < b; i++)

void setIO(string name) {
	freopen((name+".in").c_str(), "r", stdin); 
	freopen((name+".out").c_str(), "w", stdout);
}

int N, Q;
int arr[200001];

struct data {
	ll sum, upd, len;
	int add;
};

data segtree[800001];

data make_data(ll val, ll len = 1) {
	data res;
	res.len = len;
	res.sum = val;
	res.add = res.upd = 0;
	return res;
}

data combine(data a, data b) {
	data res;
	res.sum = a.sum + b.sum;
	res.len = a.len + b.len;
	res.upd = 0;
	res.add = 1;
	return res;
}

void build(int v = 1, int L = 1, int R = N) {
	if (L > R) return;
	if (L == R)
		segtree[v] = make_data(arr[L]);
	else {	
		int M = (L + R)/2;
		build(2*v, L, M);
		build(2*v+1, M+1, R);

		segtree[v] = combine(segtree[2*v], segtree[2*v+1]);
	}
}

void push(int v) {
	if (!segtree[v].upd || v > 400001) 
		return;
	
	if (segtree[v].add == 1) {
		segtree[2*v].upd += segtree[v].upd;
		segtree[2*v+1].upd += segtree[v].upd;
		segtree[2*v].sum += segtree[v].upd * segtree[2*v].len;
		segtree[2*v+1].sum += segtree[v].upd * segtree[2*v+1].len;
		if (segtree[2*v].add == 0)
			segtree[2*v].add = 1;
		if (segtree[2*v+1].add == 0)
			segtree[2*v+1].add = 1;

	} else if (segtree[v].add == 2) {
		segtree[2*v].upd = segtree[2*v+1].upd = segtree[v].upd;
		segtree[2*v].sum = segtree[2*v].len * segtree[v].upd;
		segtree[2*v+1].sum = segtree[2*v+1].len * segtree[v].upd;
		segtree[2*v].add = segtree[2*v+1].add = 2;
	}

	segtree[v].add = 0;
	segtree[v].upd = 0;
}

ll query(int v, int tl, int tr, int l, int r) {
	if (l == tl && r == tr)  
		return segtree[v].sum;
			
	push(v);
	int tm = (tl+tr)/2;	
	
	if (r <= tm)
		return query(2*v, tl, tm, l, r);
	if (l > tm)
		return query(2*v+1, tm+1, tr, l, r);

	return query(v*2, tl, tm, l, tm) + query(v*2+1, tm+1, tr, tm+1, r);
}

void range_set(int v, int tl, int tr, int l, int r, int val) {
	if (l > r) return;
	
	push(v);

	if (l == tl && r == tr) {
		segtree[v].upd = val; 
		segtree[v].add = 2;
		segtree[v].sum = val*segtree[v].len;
	} else {
		int tm = (tl + tr)/2;
		range_set(2*v, tl, tm, l, min(r,tm), val);
		range_set(2*v+1, tm+1,tr, max(l,tm+1), r, val);
		segtree[v].sum = segtree[2*v].sum + segtree[2*v+1].sum;
	}
}

void range_add(int v, int tl, int tr, int l, int r, int val) {
	if (l > r) return;
	
	push(v);

	if (l == tl && r == tr) {
		//cout << "WHAT: " << v << ' ' << segtree[v].sum << ' ' << val << endl;
		segtree[v].upd = val;
		segtree[v].add = 1;
		segtree[v].sum += segtree[v].len * val;
	} else {
		int tm = (tl + tr)/2;
		range_add(2*v, tl, tm, l, min(r,tm), val);
		range_add(2*v+1, tm+1,tr, max(l,tm+1), r, val);
		segtree[v].sum = segtree[2*v].sum + segtree[2*v+1].sum;
	}
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

	cin >> N >> Q;
	rep(i,1,N+1) cin >> arr[i];
   
	build();
	/* cout << endl << segtree[1].sum << ' ' << segtree[1].len << endl << endl; */
	/* rep(i,1,25) cout << i << ' ' << segtree[i].sum << endl; */
	
	/* range_add(1,1,N,2,6,5); */
	/* cout << "upd: " << segtree[9].upd << ' ' << segtree[9].sum << endl; */
	/* cout << "upd: " << segtree[6].upd << ' ' << segtree[6].sum << endl; */
	/* cout << "upd: " << segtree[12].upd << ' ' << segtree[12].sum << endl; */
	/* range_add(1,1,N,4,4,4); */
	/* //range_add(1,1,N,3,4,1); */	
	
	/* cout << endl << query(1,1,N,1,6) << endl; */
	/* cout << "upd: " << segtree[3].upd << ' ' << segtree[3].sum << endl; */
	/* cout << "upd: " << segtree[6].upd << ' ' << segtree[6].sum << endl; */
	/* cout << query(1,1,N,1,5) << endl; */
	/* return 0; */
	
	vi ans;

	rep(i,0,Q) {
		int t, a, b, x; 
		cin >> t;
		if (t == 1) {
			cin >> a >> b >> x;
			range_add(1,1,N,a,b,x);
		} else if (t == 2) {
 			cin >> a >> b >> x;
			range_set(1,1,N,a,b,x);
		} else {
			cin >> a >> b;
			cout << query(1,1,N,a,b) << endl;
			ans.PB(query(1,1,N,a,b));
		}
	}

	//for (auto e : ans) cout << "ans " << e << endl;

    return 0;
}








