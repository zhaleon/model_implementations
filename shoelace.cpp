#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pair<int, int> > vpi;

#define INF 1000000000
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define rep(i,a,b) for (int i = a; i <= b; i++)

int N;
double x[10000];
double y[10000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    double area = 0;
    
    cin >> N;
    rep(i,1,N) cin >> x[i] >> y[i];
    
    rep(i,1,N) {
        
        area += x[i] * y[i % N + 1] - y[i] * x[i % N + 1];
        
    }
    
    cout << area/2 << endl;

    return 0;
}