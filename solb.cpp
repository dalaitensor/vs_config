#include <bits/stdc++.h>

#define int              long long
#define vi              vector<int >
#define vii              vector<vector<int > >
#define pii             pair<int , int >
#define R(i , n, a) for(int i = n; i >= a; i--)
#define all(x) begin(x), end(x)
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "

using namespace std;
const int MOD = 1e9 + 7;

void solve(){
    int n, m , q; cin >> n >> m >> q;
    n++;

    vector<vector<pii>> g(n);
    vii route(n, vi(n, INT64_MAX));
    for(int i = 0; i < m; i++){
        int u, v, w; cin >> u>> v >>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    

    for(int i = 1; i < n; i++){
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, i});
        route[i][i] = 0;
        while(not pq.empty()){
            int u = pq.top().second; pq.pop();
            if(route[i][u] == INT64_MAX) route[i][u] = 0;

            for(auto [v, w] : g[u]){
                if(route[i][v] > route[i][u] + w){
                    pq.push({route[i][v] = route[i][u] + w, v});
                }
            }
        }
    }

    while(q--){
        int u, v; cin >> u >> v;
        cout << (route[u][v] == INT64_MAX ? -1 :  route[u][v]) << endl;
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