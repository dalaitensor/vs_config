#include <bits/stdc++.h>

#define ll              long long
#define vi              vector<int >
#define vil             vector<ll >
#define pb              push_back
#define pii             pair<int , int >
#define R(i , n, a) for(int i = n; i >= a; i--)
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "

using namespace std;

class Sol {
private:
    int n;

public:
    void solve() {
        // cin >> n;
        printf("%d asdcsa", n);
        // vi pref(n+1), dp(n + 1);

        // for (int i = 1; i <= n; i++) {
        //     dp[i] = 1 + pref[i - 1];
        //     pref[i] = dp[i] + pref[i - 1];
        // }

        // cout << dp[n];
    }
};

int main() {

#ifndef ONLINE_JUDGE
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    // cin >> t;
    while(t--) {
        Sol s;
        s.solve();
    }

    return 0;
}