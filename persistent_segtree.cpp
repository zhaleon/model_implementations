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
#define rep(i,a,b) for (int i = a; i <= b; i++)

void setIO(string name) {
	freopen((name+".in").c_str(), "r", stdin); 
	freopen((name+".out").c_str(), "w", stdout);
}

int N, Q;
int arr[200001];

struct node {
	node *l, *r;
	ll sum;

	node(ll k) : l(nullptr), r(nullptr), sum(k) {};
	node(node *a, node *b) : l(a), r(b), sum(0) {
		if (a) sum += a->sum;
		if (b) sum += b->sum;
	};
};

int cur = 0;
node* arrs[200002];

node* build(int tl = 1, int tr = N) {
	if (tl == tr)
		return new node(arr[tl]);
	int tm = (tl + tr)/2;
	return new node(build(tl, tm), build(tm+1, tr));
}

ll sum(node *v, int tl, int tr, int l, int r) {
	if (l > r) 
		return 0;

	if (tl == l && tr == r) 
		return v->sum;

	int tm = (tl + tr)/2;
	return sum(v->l, tl, tm, l, min(r, tm)) + sum(v->r, tm+1, tr, max(l,tm+1), r);
}

node* update(node *v, int tl, int tr, int pos, int val) {
	if (tl == tr)
		return new node(val);

	int tm = (tl + tr)/2;

	if (pos <= tm)
		return new node(update(v->l, tl, tm, pos, val), v->r);
	else
		return new node(v->l, update(v->r, tm+1, tr, pos, val));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

	cin >> N >> Q;
	rep(i,1,N) cin >> arr[i];
    	
	arrs[++cur] = build();	
	
	rep(i,1,Q) {
		int t; 
		cin >> t;
		
		if (t == 1) {
			int k, a, x;
			cin >> k >> a >> x;
			node* j = update(arrs[k], 1, N, a, x);
			arrs[k] = j;
		} else if (t == 2) {
			int k, a, b;
			cin >> k >> a >> b;
			cout << sum(arrs[k], 1, N, a, b) << endl;
		} else {
			int x;
			cin >> x;
			arrs[++cur] = arrs[x];
		}
	}
    
    return 0;
}








