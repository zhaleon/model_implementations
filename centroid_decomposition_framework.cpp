#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <assert.h>
#include <string>
#include <cstring>
#include <unordered_map>
#include <bitset>
#include <climits>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <deque>
#include <cmath>
#include <set>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<int> > vii;
typedef vector<int> vi;
typedef vector<pair<int, int> > vpi;

#define INF 1000000000
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define rep(i,a,b) for (int i = a; i < b; i++)

void setIO(string name) {
	freopen((name+".txt").c_str(), "r", stdin); 
	freopen((name+".out").c_str(), "w", stdout);
}

int T;
ll N, K, A, B, C, e, Case = 1;

vi adj[1000001];
int component[1000001];
int subtreeSizes[1000001];
bool v[1000001];
bool active[1000001];

int sizes[1000001], checked = 0; //dsu???

int subtreeSizes2[1000001], checked2 = 0;
bool v2[1000001];

string s;

ll cnt = 0, color = 0;
void flood(int cur) {
	cnt++;
	component[cur] = color;
	for (auto edge : adj[cur]) if (!component[edge] && s[edge-1] == '*') flood(edge);
}

ll treeDP(int cur, int root) {
	//cout << "ROOT: " << root << ' ' << cur << ' ' << adj[cur].size() << endl;
	v2[cur] = 1;
	ll res = 0;
	if (adj[cur].size() == 1 && cur != root) {
		checked2++;
		return subtreeSizes2[cur] = 1ll;
	}
	for (auto edge : adj[cur]) if (!v2[edge]) res += treeDP(edge, root);
	checked2++;
	return subtreeSizes2[cur] = res + 1;
}

typedef struct node {
	int cur, dist, tree;
	node(){};
	node(int c, int d, int t) : cur(c), dist(d), tree(t) {};
} node;

ll bfs(int root, bool hasCovid, ll treeSize, ll largest) {
	ll res = 0;
	
	queue<node> bfs; //actual node, distance, subtree it belongs to
	bfs.push(node(root, 0, 0));
	
	unordered_map<int, bool> seen;
	unordered_map<int, bool> firstTime;
	unordered_map<int, pair<int, ll>> sums; //subtree -> amount of components and sum of distances
	int tot = 0;
	seen[root] = true;

	while(!bfs.empty()) {
		auto cur = bfs.front(); bfs.pop();
		//if (Case == 3) cout << "WHAT:\n" << component[cur.cur] << ' ' << component[root] << ' ' << sizes[component[cur.cur]] << ' ' << largest << endl ;
		if (component[cur.cur] != component[root] && !firstTime[component[cur.cur]] && sizes[component[cur.cur]] == largest) {
			firstTime[component[cur.cur]] = true;
			if (hasCovid) res += cur.dist;
			tot++;
			sums[cur.tree].F++;
			sums[cur.tree].S += cur.dist;
			if (Case == 1) cerr << "WHAT: " << cur.dist << ' ' << tot << endl;
		}
	
		for (auto edge : adj[cur.cur]) {
			if (active[edge] && !seen[edge]) {
				seen[edge] = true;
				if (cur.tree == 0) bfs.push(node(edge, cur.dist+1, edge));
				else if (component[cur.cur] == component[edge]) bfs.push(node(edge, cur.dist, cur.tree));
				else bfs.push(node(edge, cur.dist+1, cur.tree));
			}
		}
	}
	if (!hasCovid) treeSize--;
	//for (auto group : sums) cout << group.S.F << ' '; cout << endl;
	for (auto group : sums) res += (tot - group.S.F) * group.S.S;
	return res;
}

int subtrees(int cur, int start) {
	int sum = 0;
	v[cur] = 1;
	
	if (adj[cur].size() == 1 && cur != start) {
		checked++;
		return subtreeSizes[cur] = 1;
	}
	
	for (auto edge : adj[cur]) if (!v[edge] && active[edge]) sum += subtrees(edge, start);
	checked++;
	return subtreeSizes[cur] = sum+1;
}

int find_centroid(int root, int subtreeSize) {
	if (subtreeSize == 2) return root;
	memset(subtreeSizes, 0, sizeof(subtreeSizes));
	memset(v, 0, sizeof(v));
	subtrees(root, root);
	int cur = root;
	int biggestSubtree, nxt = 0, curLargest = 0, centroid = 0;
	unordered_map<int, bool> m;
	int BROKEN = 0;
	do {
		curLargest = 0;
		int biggest = subtreeSize-subtreeSizes[cur];
		m[cur] = 1;
		for (auto edge : adj[cur]) {
			if (m[edge] || !active[edge]) continue;
			biggest = max(biggest, subtreeSizes[edge]);
			if (subtreeSizes[edge] > curLargest) {
				nxt = edge;
				curLargest = subtreeSizes[edge];
			}
		}
		biggestSubtree = biggest;
		centroid = cur;
		cur = nxt;
		cerr << "TEST " << biggestSubtree << ' ' << subtreeSize << ' ' << cur << ' ' << nxt << ' ' << centroid << endl;
		BROKEN += 1;
		if (BROKEN > 10) break;
	} while(biggestSubtree > subtreeSize/2+1);// && BROKEN < 100);
	cerr << "CENTROID: " << centroid << ' ' << root << ' ' << subtreeSize << ' ' << subtreeSizes[2] << endl;
	return centroid;
}

int main() {
	setIO("test");
	//setIO("quarantine_validation_input");
    ios::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	
	while (T--) {
		memset(v, 0, sizeof(v)); //reset all the bullshit
		memset(component, 0, sizeof(component));
		rep(i,0,1000001) adj[i].clear();
		rep(i,0,1000001) active[i] = 1;
		memset(sizes, 0, sizeof(sizes)); checked = 0; checked2 = 0;
		vector<ll> rooms;
		map<ll, int> m; //component size -> number of components
		
		cin >> N >> K >> s;
		
		rep(i,2,K+2) {
			cin >> e;
			adj[i].PB(e);
			adj[e].PB(i);
			rooms.PB(e);
		}
		
		cin >> A >> B >> C;
		if (K < N-1) { //build tree
			rep(i,K+2,N+1) {
				e = (rooms[rooms.size()-2]*A + rooms[rooms.size()-1]*B + C) % (i-1) + 1;
				rooms.PB(e);
				adj[i].PB(e);
				adj[e].PB(i);
			}
		}
		
		color = 0; //get components
		int largest = 0, idx = 1;
		rep(i,1,N+1) {
			if (!component[i] && s[i-1] == '*') {
				color++; cnt = 0;
				flood(i);
				//if (Case == 3) cout << "WTF: " << sizes[color] << ' ' << cnt << ' ' << color << endl;
				sizes[color] = cnt;
				if (cnt > largest) largest = cnt, idx = i;
				m[cnt]++;
			}
		}
		
		int numComponents = color;
		rep(i,1,N+1) if (!component[i]) {
			color++;
			component[i] = color;
		}
		
		ll pairs, secondLargest = 0; //get number of pairs that can be visited
		bool simple = 0; //one single dfs is fine one largest -> all second largest
		
		if (m.size() == 1) {
			ll temp = m.begin()->F;
			if (m.begin()->S == 1) pairs = temp*(temp-1)/2;
			else pairs = temp*(2*temp-1);
			secondLargest = largest;
		} else {
			if (m.empty()) {
				pairs = 0;
			} else {
				auto it = --m.end();
				if (it->S > 1) {
					secondLargest = largest;
					pairs = it->F * (2*(it->F)-1);
				} else {
					simple = 1;
					auto it2 = prev(it);
					secondLargest = it2->F;
					int temp = it->F + it2->F;
					pairs = temp*(temp-1)/2;
				}
			}
		}
		
		if (numComponents == 1) {
			ll ans = 0;
			//cout << "TEST: " << largest << ' ' << idx << ' ' << ans << endl;
			memset(v2, 0, sizeof(v2));
			treeDP(idx, idx);
			
			//for (int i = 1; i <= 5; i++) cout << subtreeSizes2[i] << ' '; cout << endl;
			
			queue<int> bfs;
			bfs.push(idx);
			unordered_map<int, bool> visited;
			while(!bfs.empty()) {
				int cur = bfs.front(); bfs.pop();
				
				if (cur != idx) {
					if (component[cur] == 1) {
						ans += largest-1;
					} else {
						ans += subtreeSizes2[cur]*(N-subtreeSizes2[cur]);
					}
				}
				visited[cur] = 1;
				
				for (auto edge : adj[cur]) {
					if (!visited[edge]) {
						visited[edge] = 1;
						bfs.push(edge);
					}
				}
			}
			
			memset(v2, 0, sizeof(v2));
			checked2 = 0;
			memset(subtreeSizes2, 0, sizeof(subtreeSizes2));
			
			cout << "Case #" << Case << ": " << pairs << ' ' << ans << '\n';
			Case++;
			continue;
		} else if (!numComponents) {
			ll ans = 0;
			cerr << "Case: " << Case << endl;
			memset(v2, 0, sizeof(v2));
			treeDP(idx, idx);
			
			//if(Case == 2)
			//for (int i = 1; i <= 3; i++) cout << subtreeSizes2[i] << ' '; cout << endl;
			cerr << subtreeSizes2[2] << endl;
			queue<int> bfs;
			bfs.push(idx);
			unordered_map<int, bool> visited;
			while(!bfs.empty()) {
				int cur = bfs.front(); bfs.pop();
				
				if (cur != idx) {
					ans += subtreeSizes2[cur]*(N-subtreeSizes2[cur]);
					assert(ans > 0);
				}
				visited[cur] = 1;
				
				for (auto edge : adj[cur]) {
					if (!visited[edge]) {
						visited[edge] = 1;
						bfs.push(edge);
					}
				}
			}
			
			memset(v2, 0, sizeof(v2));
			checked2 = 0;
			memset(subtreeSizes2, 0, sizeof(subtreeSizes2));
			
			cout << "Case #" << Case << ": " << pairs << ' ' << ans << '\n';
			Case++;
			continue;
		}
		
		if (simple) {
		
			ll ans = 0;
			queue<node> bfs; //actual node, distance, subtree it belongs to
			bfs.push(node(idx, 0, 0));
			
			unordered_map<int, bool> seen;
			unordered_map<int, bool> firstTime;
			seen[idx] = true;

			while(!bfs.empty()) {
				auto cur = bfs.front(); bfs.pop();
				//cout << cur.cur << ' ' << idx << ' ' << firstTime[component[cur.cur]] << ' ' << sizes[cur.cur] << endl;
				if (component[cur.cur] != component[idx] && !firstTime[component[cur.cur]] && sizes[component[cur.cur]] == secondLargest) {
					firstTime[component[cur.cur]] = true;
					//cout << "WHAT " << cur.dist << ' ' << cur.cur << endl;
					ans += cur.dist;
				}
			
				for (auto edge : adj[cur.cur]) {
					if (active[edge] && !seen[edge]) {
						seen[edge] = true;
						if (cur.tree != 0) bfs.push(node(edge, cur.dist+1, edge));
						else if (component[cur.cur] == component[edge]) bfs.push(node(edge, cur.dist, cur.tree));
						else bfs.push(node(edge, cur.dist+1, cur.tree));
					}
				}
			}
			//cout << ans << endl;
			cout << "Case #" << Case << ": " << pairs << ' ' << ans*largest*secondLargest << '\n';
			Case++;
			continue;
		}

		ll ans = 0;

		queue<pii> q; //queue for subtrees;
		q.push(MP(1,N));
		int broken = 0;
		while (!q.empty()) {
			broken++;
			//if (broken > 30) break;
			pii cur = q.front(); q.pop();
			assert(active[cur.F]);
			if (cur.S <= 1) {
				active[cur.F] = 0;
				continue;
			}
			
			if (checked == N) {
				checked = 0;
				memset(subtreeSizes, 0, sizeof(subtreeSizes));
			}
			//cerr << "TEST: " << Case << ' ' << ' ' << cur.S << endl;
			
			int centroid = find_centroid(cur.F, cur.S);
			
			ans += bfs(centroid, s[cur.F-1] == '*', cur.S, largest);

			cerr << "TEST: " << Case << ' ' << centroid << ' ' << cur.S << endl;
			
			memset(v2, 0, sizeof(v2));
			if (checked2 == N) {
				checked2 = 0;
				memset(subtreeSizes2, 0, sizeof(subtreeSizes2));
			}
			
			treeDP(centroid, centroid);
			
			//cout << subtreeSizes2[2] << endl;
			active[centroid] = false;
			for (auto edge : adj[centroid]) {
				if (active[edge]) q.push(MP(edge, subtreeSizes2[edge]));
			}
		}
		//cout << "Case #" << Case << ": " << ans << endl;
		//cerr << ans << endl;
		cout << "Case #" << Case << ": " << pairs << ' ' << ans*largest*secondLargest << '\n';
		Case++;
//		for(int i = 1; i <= 10; i++) {
//			cout << s[i-1] << ' ' << i << ": ";
//			for (auto edge : adj[i]) cout << edge << ' '; cout << endl;
//		}
		
	}

    return 0;
}