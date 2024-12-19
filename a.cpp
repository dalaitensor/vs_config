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


 
    void solve() {
        cin >> n;
        vi arr(n);

        for(int &i : arr){
            cin >> i;
        }


        int cnt = 0, res = INT_MAX;
        for(int i = 0; i < n; i++){
            if(arr[i] != arr[0]){
                res = min(cnt, res);
                cnt = 0;
            } else {
                cnt++;
            }
        }

        res = min(res, cnt);

        if(res == n) cout << -1 << endl;
        else cout << res << endl;


        
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
    cin >> t;
    while(t--) {
        Sol s;
        s.solve();
    }

    return 0;
}