#include <bits/stdc++.h>

#define ll              long long
#define vi              vector<int >
#define vll             vector<ll >
#define pii             pair<int , int >
#define R(i , n, a) for(int i = n; i >= a; i--)
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "
const int MOD = int(1e9) + 7;

using namespace std;



class Sol {
private:
    int n;

    
 
public:

    void helper(int x, bool up , int par, string s){
        if(x == 1){
            s += par + '0';
            cout << s << endl;
            return;
        } 
        s += par + '0';
        int a =  up ? 0 : 1;
        helper(x - 1, true, a , s);
        helper(x - 1, false, 1 - a , s);
    }


    void solve() {
        cin >> n;

        string res;
        helper(n, true, 0, res);
        helper(n, false, 1, res);


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