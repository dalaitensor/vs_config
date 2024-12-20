#include <bits/stdc++.h>

#define ll              long long
#define vi              vector<int >
#define vll             vector<ll >
#define pii             pair<int , int >
#define R(i , n, a) for(int i = n; i >= a; i--)
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "


using namespace std;

typedef struct{
   int x , k; 
} prime;

const int MOD = int(1e9) + 7;

class Sol {
private:
    int n;

    
 
public:
    ll power(ll base, ll exp, ll m){
        if(exp == 0) return 1;
        if(exp == 1) return base % m;
        ll temp = power(base, exp / 2, m);
        temp = (temp * temp) % m;

        if(exp & 1){
            temp = (temp * base) % m;
        }

        return temp;
    }


    void solve() {
        cin >> n;
        vector<prime> arr(n);

        ll number = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i].x >> arr[i].k;
            number += arr[i].k;
        } 

        debug(number) << endl;

        ll fact = 1;

        for(int i = 1; i <= number; i++){
            fact = (fact * i) % MOD;
        }

        debug(fact) << endl;

        ll sum = 0;
        ll prod = 1ll;

        for(int i = 0; i < n; i++) {
            sum += (arr[i].x * arr[i].k) % MOD;
            prod *= power(arr[i].x, arr[i].k, MOD);
        }

        cout << fact << " " << sum << " " << prod << endl;
         
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