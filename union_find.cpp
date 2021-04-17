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

int N, M;

int parent[100001];
int size[100001];

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

int merge(int a, int b) {
	a = find(a), b = find(b);

	if (a == b)
		return 0;

	if (size[a] < size[b]) 
		swap(a,b);

	size[a] += size[b];
	parent[b] = a;
	return size[a];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

	cin >> N >> M;

	int cc = N, big = 1;
    iota(parent+1, parent+1+N,1);
	fill(size+1, size+1+N, 1);

	rep(i,1,M) {
		int a, b;
		cin >> a >> b;

		int k = merge(a,b);
		
		if (k) {
			cc--;
			big = max(big, k);
		}

		cout << cc << ' ' << big << endl;
	}

    return 0;
}








