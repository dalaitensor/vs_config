#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// #define int long long
 
#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
#define abs(a) a < 0 ? -a : a
#define MAXN (int)1e9 + 5
 
int freq[5005];
int pref[5005];
 
void solve() {
    int n; scanf("%d", &n);
 
    for(int i =0 ; i < n; i++){
        int a; scanf("%d", &a);
 
        freq[a]++;
    }
 
    pref[0] = freq[0];
 
    for(int i=1 ; i < 5001; i++){
        pref[i] = pref[i - 1] + freq[i];
    }
 
    int res = 1000005;
    for(int i = 1; i < 5001; i++){
        int local = pref[i - 1] + (pref[5000] - pref[min(5000, 2*i)]);
        res = min(res, local);
    }
 
    printf("%d", res);
}
 
signed main() {
    int t;
    t=1;
    // scanf("%lld", &t);
    while (t--) {
        solve();
    }
}