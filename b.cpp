#include <bits/stdc++.h>

#define ll              long long
#define vi              vector<int >
#define vll              vector<ll >
#define vii              vector<vector<int > >
#define pii             pair<int , int >
#define R(i , n, a) for(int i = n; i >= a; i--)
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "

#define int ll
using namespace std;
const int MOD = 1e9 + 7;

void solve(){
    int n; cin >> n;

    vi a(n);
    for(int &i : a) cin >> i;

    int jump = a[0] - 1, curr = a[0];

    for(int i = 1; i < n; i++){
        if(a[i] > a[i - 1]) jump += a[i] - a[i - 1];
    }

    cout << jump << endl;
    
}


signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }

}