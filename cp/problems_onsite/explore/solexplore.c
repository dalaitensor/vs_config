#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int long long

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
#define abs(a) a < 0 ? -a : a
#define MAXN (int)1e9 + 5

char str[1000005];
int a[100005], b[100005];

void solve() {
    int n, m, t;
    scanf("%lld %lld %lld", &n, &m, &t);

    for(int i = 1; i <= n - 1; i++) scanf("%lld", a + i);

    while(m--){
        int x, y;
        scanf("%lld%lld", &x, &y);

        b[x] = y;
    }


    
    for(int i = 1; i <= n - 1; i++){
        t += b[i];
        t -= a[i];
        if(t <= 0){
            printf("No");
            return;
        }
        

        // printf("%lld\n", b[i]);
        // printf("%lld\n", t);
    }

    printf("Yes");








    
}
 
signed main() {
    int t;
    t=1;
    // scanf("%lld", &t);
    while (t--) {
        solve();
    }
}