#include <stdio.h>
 
int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int a[505];
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
 
        int already_unsorted = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (a[i] > a[i + 1]) {
                already_unsorted = 1;
                break;
            }
        }
 
        if (already_unsorted) {
            printf("0\n");
            continue;
        }
 
        // Else, compute min operations
        int min_ops = 1e9;
        for (int i = 0; i < n - 1; ++i) {
            if (a[i] <= a[i + 1]) {
                int diff = a[i + 1] - a[i];
                int ops = diff / 2 + 1;
                if (ops < min_ops) min_ops = ops;
            }
        }
 
        printf("%d\n", min_ops);
    }
    return 0;
}