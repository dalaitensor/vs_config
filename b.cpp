#include <bits/stdc++.h>

#define ll              long long
#define vi              vector<int >
#define vll              vector<ll >
#define vii              vector<vector<int > >
#define pii             pair<int , int >
#define R(i , n, a) for(int i = n; i >= a; i--)
#define all(x) begin(x), end(x)
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "
#define int ll

using namespace std;
const int MOD = 1e9 + 7;

typedef struct {
    int seg, pref, suf, sum;
} node;


class St{
private:
    vector<int> st;

public:
    St(int n){
        st.resize(4 * n, 0);
    }

    void print() {
        for (int val : st) {
            cout << val << " ";
        }
        cout << endl;
    }

    void merge(int pos, int val){
        st[pos] = val;
    }

    int op(int a, int b){
        return a + b;
    }

    void build(vector<int> &arr, int lx, int rx, int pos){
        if(lx == rx){
            merge(pos, arr[lx]);
            return;
        }

        int mid = lx + (rx - lx) / 2;

        build(arr, lx, mid, 2 * pos + 1);
        build(arr, mid + 1, rx, 2 * pos + 2);

        st[pos] = op(st[2 * pos + 1], st[2 * pos + 2]);
    }

    void update(int index, int val,  int lx, int rx, int pos){
        if(lx == rx){
            merge(pos, 1 - st[pos]);
            return;
        }

        int mid = lx + (rx - lx) / 2;

        if(mid >= index) update(index, val, lx, mid, 2 * pos + 1);
        else update(index, val, mid + 1, rx, 2 * pos + 2);

        st[pos] = op(st[2 * pos + 1], st[2 * pos + 2]);
    }

    int query(int k, int lx, int rx, int pos){
        if(lx == rx){
            return lx;
        }

        int mid = lx + (rx - lx) / 2;

        int s = st[2 * pos + 1];

        if(k < s)
            return query(k, lx, mid, 2 * pos + 1);
        else
            return query(k - s, mid + 1, rx, 2 * pos + 2);
    }

};

void solve(){
    int n, m;
    cin >> n >> m;

    vi arr(n);
    for(int &i:arr) cin >> i;

    St tree(n);

    tree.build(arr, 0, n - 1, 0);
    // tree.print();

    while(m--){
        int dir, x; cin >>dir >> x;

        if(dir == 1){
            tree.update(x, 0, 0, n - 1, 0);
            // tree.print();
        } else {
            cout << tree.query(x, 0, n - 1, 0) << endl;
        }
    }
    

}


signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }

}