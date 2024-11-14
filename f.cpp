#include <bits/stdc++.h>

#define pb push_back
#define L(i , a , n) for(int i = a; i < n; i++)
#define R(i , n, a) for(int i = n; i >= a; i--)

using namespace std;

class Sol {
private:
    vector<int> arr;
    long long l, r, i , k;

public:
    void solve() {
        cin >> l >> r >> i >> k;
        long long res = 0;

        if(l % 2 == 0 && r % 2 == 0){
            res ^= r;
        } else if(l % 2 != 0 && r % 2 == 0){
            res ^= l;
            res ^= r;
        } else if(l % 2 != 0 && r % 2 != 0){
            res ^= l;
        }

        cout << "first" << res << endl;

        if(((r - l + 1) / 2) % 2 != 0){
            res ^= 1;
        }

        cout << "second" << res << endl;

        long long d = r / (1 << i);

        if(d % 2){
            res ^= k;
        }

        cout << "third" << res << endl;



        long long idx = (d ) * (1 << i);

        for(; idx <= r; idx += (1 << i)){
            res ^= idx;
        }

        
        cout << res << endl;
    }
};

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t, n;
    cin >> t;
    while(t--) {
        Sol s;
        s.solve();
    }

    return 0;
}