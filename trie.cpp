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

template<const size_t A = 26>
struct trie {
    struct node {
        int freq;
        int pre_freq = 0;
        int nxt[A] = {0}, exists;
        node() : freq(0) {};
        node(int freq) : freq(freq) {};
    };
    
    vector<node> pt;
    trie() { pt.resize(1); };
     
    inline int ord(const char c) { return (int)(c - 'a'); }
   
    int find(const char *s, int l) {
        int p = 0;
        for (int i = 0; i < l; ++i) {
            int c = ord(s[i]);
            if (!pt[p].nxt[c]) return 0;
            p = pt[p].nxt[c];
        }
        return pt[p].freq;
    }

    int find2(const char *s, int l) {
        int p = 0;
        for (int i = 0; i < l; ++i) {
            int c = ord(s[i]);
            if (!pt[p].nxt[c]) return 0;
            p = pt[p].nxt[c];
        }
        return pt[p].pre_freq;
    }
        
    void insert(const char* s, int l) {
        for (int p = 0, i = 0; i < l; ++i) {
            int c = ord(s[i]);
            if (!pt[p].nxt[c]) {
                pt[p].nxt[c] = pt.size();
                pt.push_back(node());
            }
            p = pt[p].nxt[c];
            if (i == l-1) ++pt[p].freq;
            else ++pt[p].pre_freq;
        }
    }
    
    void erase(const char* s, int l) {
        for (int p = 0, i = 0; i < l; ++i) {
            int c = ord(s[i]);
            p = pt[p].nxt[c];
            if (i == l-1) --pt[p].freq;
            else --pt[p].pre_freq;

            assert(~pt[p].freq);
        }
    }
};

int N, Q;
trie<> bit[100001];
string temp[100001];

void upd(int pos, string &val) {
    int i = pos;
    while (pos < N+1) {
        bit[pos].erase(temp[i].c_str(), temp[i].length());
        bit[pos].insert(val.c_str(), val.length());
        pos += pos & -pos;
    }
    temp[i] = val;
}

int query(int i, string &val) {
    int res = 0;
    while (i) {
        res += bit[i].find(val.c_str(), val.length());
        i -= i & -i;
    }
    return res;
}

int query(int i, int j, string &val) {
    return query(j, val) - query(i-1, val);
}

int q2(int i, string &val) {
    int res = 0;
    while (i) {
        res += bit[i].find2(val.c_str(), val.length());
        i -= i & -i;
    }
    return res;
}

int q2(int i, int j, string &val) {
    return q2(j, val) - q2(i-1, val);    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    rep(i,1,N) {
        string s;
        cin >> s;
        upd(i, s);
    }

    cin >> Q;
    rep(i,1,Q) {
        int t; cin >> t;
        int a, b;
        string s;
        
        if (t == 1) {
            cin >> a >> s;
            upd(a,s);
        } else if (t == 2) {
            cin >> a >> b >> s;
            
            string cur = "";
            string ans = "N\n";
            rep(j,0,s.length()-1) {
                cur += s[j];
                //cout << cur;
                if (query(a,b,cur) > 0) ans = "Y\n";
            } //cout << endl;
            
            cout << ans;
        } else {
            cin >> a >> b >> s;
            if (q2(a,b,s) > 0) cout << "Y\n";
            else cout << "N\n";
        }
    }

    return 0;
}
