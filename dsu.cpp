#include <bits/stdc++.h>

#define ll              long long
#define vi              vector<int >
#define vil             vector<ll >
#define pb              push_back
#define fi              first
#define sc              second
#define pii             pair<int , int >
#define pb              push_back
#define L(i , a , n) for(int i = a; i < n; i++)
#define R(i , n, a) for(int i = n; i >= a; i--)

using namespace std;

typedef struct{
    int size;
    int minim;
    int maxim;
} el;

class Sol {
private:
    // vector<int> rank;

    vector<int> par;
    vector<el> vals;

    int n, m;

public:

    int find(int x){
        return par[x] = (par[x] == x ? x : find(par[x]));
    }

    void un(int a, int b){
        a = find(a); b = find(b);

        if(a == b) return ;

        if(vals[a].size > vals[b].size){
            swap(a, b);
        }

        par[b] = a;

        vals[a].size += vals[b].size;
        vals[a].minim = min(vals[a].minim, vals[b].minim);
        vals[a].maxim = max(vals[a].maxim, vals[b].maxim);
        
    }

    void solve() {
        cin >> n >> m;
        ++n;
        par.resize(n);
        vals.resize(n);
        // rank.resize(n);

        L(i, 0, n){
            par[i] = i;
            vals[i].size = 1;
            vals[i].minim = i;
            vals[i].maxim = i;
        }


        while(m--){
            string ins; int u , v;
            cin >> ins >> u;

            if(ins == "get"){
                u = find(u);
                
                cout << vals[u].minim << " " << vals[u].maxim << " " << vals[u].size << endl;
            } else {
                cin >> v;
                un(u, v);

                // L(i, 0, n){
                // cout << par[i] << " ";
                // }
                // cout << endl;
                // L(i, 0, n){
                //     cout << vals[i].size << " ";
                // }
                // cout << endl;
            }

            
        }
    }
};

int main() {

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    // int t;
    // cin >> t;
    // while(t--) {
        Sol s;
        s.solve();
    // }

    return 0;
}