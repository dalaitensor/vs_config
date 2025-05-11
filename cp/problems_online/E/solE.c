#include <stdio.h>
#include <string.h>
 
#define MAX 100010
 
int a[MAX];
long long f[MAX], bitf[MAX];
 
void solve() {
    int n, i, j, k, l, T;
    long long ans;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++) scanf("%d", &a[i]);
 
        memset(f, 0, sizeof(f));
        for (j = 1; j <= n; j++) {
            for (l = j + 1; l <= n; l++) {
                if (a[j] > a[l]) f[j]++;
            }
        }
 
        ans = 0;
        for (k = 1; k <= n; k++) {
            for (j = 1; j < k; j++) {
                if (a[j] > a[k]) f[j]--;
            }
 
            bitf[0] = 0;
            for (i = 1; i <= k; i++) {
                bitf[i] = bitf[i - 1] + f[i];
            }
 
            for (i = 1; i < k; i++) {
                if (a[i] < a[k]) ans += bitf[k - 1] - bitf[i];
            }
        }
        printf("%lld\n", ans);
    }
}
 
int main() {
    solve();
    return 0;
}