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


using namespace std;

class Sol {
private:
    vector<vector<int>> arr;
    int n;

public:
    void solve() {
        cin >> n;

        arr.resize(n, vector<int> (3));

        vector<int> start(n);
        vector<int> end(n);

        int max_end = INT_MIN;

        L(i, 0, n){
            cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
            max_end = max(arr[i][2], max_end);
        }

        sort(arr.begin(), arr.end());

        map<int, int> dp;

        int global = arr[0][1], glob_end = arr[0][0] +  arr[0][2];

        L(i, 0 ,n){
            int sta = arr[i][0], end = arr[i][2], fun = arr[i][1];
            // debug(sta);
            int l = i + 1, r = n - 1;
            while(l <= r){
                int mid = (l + r) / 2;
                if(arr[mid][0] < sta + end){
                    l = mid + 1;
                } else if(arr[mid][0] >= sta + end){
                    r = mid - 1;
                }
            }
            

            // debug(sta + end);
            // debug(fun);

            debug(dp[sta]);

            
            if(sta > glob_end){
                dp[sta] = max(dp[sta], global);
            }

            debug(dp[sta]);


            if(l < n){
                dp[arr[l][0]] = max(dp[arr[l][0]], dp[sta] + fun);

                if(glob_end <= sta + end && global < dp[arr[l][0]]){
                    glob_end = sta + end;
                    global = dp[arr[l][0]];
                }

                // debug(arr[l][0]);
                debug(dp[arr[l][0]]) << endl;
            } else {
                dp[max_end] = max(dp[max_end], dp[sta] + fun);
                debug(dp[max_end]) << endl;
            }

            if(glob_end <= sta && global < dp[sta]){
                glob_end = sta;
                global = dp[sta];
            }

        }

        cout << dp[max_end];

    
    }
};

signed main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    // cin >> t;
    t= 1;
    while(t--) {
        Sol s;
        s.solve();
    }

}