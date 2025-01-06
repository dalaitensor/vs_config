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

int exp(int a, int b){
    if(b == 0) return 1;

    int res = exp(a, b/2);
    if(b & 1)
        return (((res * res) % MOD) * a) % MOD;
    else 
        return (res * res) % MOD;
}

void solve(){
    int n;

    cin >> n;
    // int divs = sqrt(n);
    int answer = 0;
      
    for(int i = 1, j; i <= n; i = j){
        int q = n / i;
        j = n/q + 1;
        int sumj = ((((j % MOD) *( (j-1)%MOD)) % MOD) * exp(2, MOD-2)) %MOD;
        int sumi = ((((i % MOD) *( (i-1)%MOD)) % MOD) * exp(2, MOD-2)) %MOD;
        int diff = (sumj - sumi + MOD) % MOD;

        answer += (q%MOD) * diff;
        answer %= MOD;
    }

    cout << answer;

    // 12 
    // 1  2 3 4 5 6 7 8 9 10 11 12 13
    // 12 6 4 3 2 2 1 1 1 1  1  1  1
    // 1  1 1 1 2   7
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

