#include <stdio.h>
#include <stdlib.h>
 
#define MAXN 100005
 
int a[MAXN], b[MAXN], arr[MAXN];

void solve() {
    int n, k;
    scanf("%d %d", &n, &k);
 
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
 
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
 
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = (b[i] == 0) ? 0 : (a[i] / b[i]);
        if (arr[i] > k) arr[i] = k;
        k -= arr[i];
    }
 
    if (k > 0) {
        for (int i = 0; i < n; i++) {
            printf("0 ");
        }
        printf("\n");
        return;
    }
 
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
 
int main() {
    int t = 1;
    while (t--) {
        solve();
    }
 
    return 0;
}