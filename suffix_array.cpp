#include <bits/stdc++.h>

#define pb push_back
#define L(i , a , n) for(int i = a; i < n; i++)
#define R(i , n, a) for(int i = n; i >= a; i--)

using namespace std;

class Sol {
private:

    int n;

public:

    void solve() {

        string s;
        cin >> s;
        s += "$";
        n = s.length();

        vector<int> p(n), c(n);
        {   
            vector<pair<char, int> > a(n);

            L(i,  0, n){
                a[i] = {s[i], i};
            }

            sort(a.begin(), a.end());

            L(i , 0 , n) p[i] = a[i].second;

            c[p[0]] = 0;

            L(i , 1, n){
                if(a[i].first == a[i - 1].first){
                    c[p[i]] = c[p[i - 1]];
                } else {
                    c[p[i]] = c[p[i - 1]] + 1;
                }
            }
        }

        int k = 0;
        while((1 << k) < n){
            vector<pair<pair<int, int> ,int> > a(n);
            L(i , 0 , n){
                a[i] = {{c[i],  c[(i + (1 << k)) % n]}, i};
            }

            sort(a.begin(), a.end());

            L(i , 0 , n) p[i] = a[i].second;

            c[p[0]] = 0;

            L(i , 1, n){
                if(a[i].first == a[i - 1].first){
                    c[p[i]] = c[p[i - 1]];
                } else {
                    c[p[i]] = c[p[i - 1]] + 1;
                }
            }

            k++;

        }

        L(i , 0 , n){
            cout << p[i] << " " << s.substr(p[i], n - p[i]) << endl;
        }
    }
};

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;

    Sol s;
    s.solve();



    return 0;
}