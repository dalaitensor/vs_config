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
    vector<pii> arr;
    int n;

public:

    void solve() {
        int n, a ,b ;
        cin >> n >> a >> b;
        string s;
        cin >> s;

        int x = 0, y = 0, idx = 0;

        L(i, 0 ,10000){
            char op = s[idx++];
            if(op == 'N') y++;
            else if(op == 'E') x++;
            else if(op == 'S') y--;
            else if(op == 'W') x--;

            if(idx == n){
                idx = 0;
            }
            if(x == a && y == b){
                cout << "YES\n";
                return;
            } 
        }
        cout << "NO\n";

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