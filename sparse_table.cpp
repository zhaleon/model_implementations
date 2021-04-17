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
int table[200001][18]; //most inputs aren't larger than (1 << 17)

void init() {
    rep(i,1,N+1) table[i][0] = arr[i];
    
    rep(i,1,18) {
        int k = (1 << (i-1));
        rep(j,1,N+1-k) table[j][i] = min(table[j][i-1], table[j+k][i-1]);
    }
}

int query(int l, int r) {
    int p = 31-__builtin_clz(r-l);
    return min(table[l][p], table[r+1-(1 << p)][p]);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

	cin >> N >> Q;
	rep(i,1,N+1) cin >> arr[i];
	init();

	rep(i,0,Q) {
		int a, b;
		cin >> a >> b;
		cout << query(a,b) << endl;
	}	

    return 0;
}







