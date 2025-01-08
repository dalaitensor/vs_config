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
    int val, count;
} node;

class St{
private:
    vector<node> st;

public: 
    St(int n){
        st.resize(4 * n, {INT64_MAX, 1});
    }

    void print() {
        for (auto val : st) {
            cout << val.val << " ";
        }
        cout << endl;
    }

    void merge(int pos, int val){
        st[pos] = {val, 1};
    }

    node op(node a, node b){
        if(a.val == b.val) return {a.val, a.count + b.count};
        else {
            if(a.val < b.val) return a;
            else return b;
        }
    }

    void build(vi& arr, int lx, int rx, int pos){
        if(lx == rx){
            merge(pos, arr[lx]);
            return;
        }

        int mid = lx + (rx - lx) / 2;

        build(arr, lx, mid, 2 * pos + 1);
        build(arr, mid + 1, rx, 2 * pos + 2);

        st[pos] = op(st[2 * pos + 1], st[2 * pos + 2]);
    }

    void update(int val, int index, int lx, int rx, int pos){
        if(lx == rx){
            merge(pos, val);
            return;
        }

        int mid = lx + (rx - lx) / 2;

        if(mid >= index) update(val, index, lx ,mid, 2 * pos + 1);
        else update(val, index, mid + 1, rx, 2 * pos + 2);

        st[pos] = op(st[2 * pos + 1], st[2 * pos + 2]);
    }

    node query(int l, int r, int lx, int rx, int pos){
        if(l <= lx && rx <= r){
            return st[pos];
        }
        if(rx < l || r < lx) return {INT64_MAX, 1};

        int mid = lx + (rx - lx) / 2;

        node left = query(l, r, lx, mid, 2 * pos + 1);
        node right = query(l, r, mid + 1, rx, 2 * pos + 2);

        return op(left, right);
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
        int dir, x, y; cin >> dir >> x >> y;
        if(dir == 1){
            tree.update(y, x, 0, n - 1, 0);
        } else {
            node res =  tree.query(x, y - 1, 0, n - 1, 0);
            cout << res.val << " " << res.count << endl;
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