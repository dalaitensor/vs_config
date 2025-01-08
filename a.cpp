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

void solve(){
    int n;
    cin >> n;
    vi arr(n);


    for(int &i : arr) cin >> i;

    map<int, int> mp;

    int s = 0, res = 0;
    for(int i = 0; i < n; i++){
        if(mp.find(arr[i]) != mp.end() && mp[arr[i]] >= s){
            s = mp[arr[i]] + 1;
        }
        mp[arr[i]] = i;
        res = max(res, i - s + 1);
    }

    cout << res;

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