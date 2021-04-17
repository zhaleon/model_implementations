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

ll arr[200001];
ll bit[200001];

void upd(int pos, int delta) {
	while (pos < N+1) {
		bit[pos] += delta;
		pos += pos & -pos;
	}
}

ll sum(int i) {
	ll res = 0;
	while (i) {
		res += bit[i];
		i -= i & -i;
	}
	return res;
}

ll sum(int i, int j) {
	return sum(j) - sum(i-1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

	cin >> N >> Q;
	rep(i,1,N+1) {
		int a; cin >> a;
		arr[i] = a;
		upd(i, a);
	}

	rep(i,0,Q) {
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 1) {
		 	upd(b, -arr[b]);  	
			upd(b, c);
			arr[b] = c;
		} else { 
			cout << sum(b, c) << endl;
		}
	}
    
    return 0;
}








