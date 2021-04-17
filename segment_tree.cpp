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

int N, M;
ll arr[200001];

struct data {
	ll suff, pref, ans, sum;
	data() {};
};

data segtree[800001];

data make_data (int val) {
	data res;
	res.sum = val;
	res.pref = res.suff = res.ans = max (0, val);
	return res;
}

data combine (data l, data r) {
	data res;
	res.sum = l.sum + r.sum;
	res.pref = max (l.pref, l.sum + r.pref);
	res.suff = max (r.suff, r.sum + l.suff);
	res.ans = max (max (l.ans, r.ans), l.suff + r.pref);
	return res;
}

void build (int v = 1, int tl = 1, int tr = N) {
	if (tl == tr)
		segtree[v] = make_data (arr[tl]);
	else {
		int tm = (tl + tr) / 2;
		build (v*2, tl, tm);
		build (v*2+1, tm+1, tr);
		segtree[v] = combine(segtree[v*2], segtree[v*2+1]);
	}
}
 
void update (int v, int tl, int tr, int pos, int new_val) {
	if (tl == tr)
		segtree[v] = make_data (new_val);
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update (v*2, tl, tm, pos, new_val);
		else
			update (v*2+1, tm+1, tr, pos, new_val);
		segtree[v] = combine (segtree[v*2], segtree[v*2+1]);
	}
}

data query (int v, int tl, int tr, int l, int r) {
	if (l == tl && tr == r)
		return segtree[v];
	int tm = (tl + tr) / 2;
	if (r <= tm)
		return query (v*2, tl, tm, l, r);
	if (l > tm)
		return query (v*2+1, tm+1, tr, l, r);
	return combine (
		query (v*2, tl, tm, l, tm),
		query (v*2+1, tm+1, tr, tm+1, r)
	);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

   	cin >> N >> M; 
	rep(i,1,N+1) cin >> arr[i];

	build();
	rep(i,0,M) {
		int a, b;
		cin >> a >> b;
		
		update(1, 1, N, a, b);
		cout << query(1, 1, N, 1, N).ans << endl;
	}
	return 0;
}








