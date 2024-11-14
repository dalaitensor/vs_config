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
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "

using namespace std;

class Sol {
private:
    vector<int> arr;
    ll n;

public:
    void solve() {
        ll b, c;
        cin >> n >> b>> c;

        

        if(b == 0) {
            if(n <= c){
                cout << n << '\n';
            } else if(c >= n - 2){
                cout << n - 1 << '\n';
            } else {
                cout << -1 << '\n';
            }
        } else {
            if(c >= n){
                cout << n << endl;
            } else {
                cout << n - max(0ll, 1 + (n - c - 1) / b) << "\n";
            }
        }

    }
};

int main() {

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        Sol s;
        s.solve();
    }

    return 0;
}