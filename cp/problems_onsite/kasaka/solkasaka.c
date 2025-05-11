#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int long long
 
#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
#define abs(a) a < 0 ? -a : a
#define MAXN (int)1e9 + 5

char str[1000005];

void solve() {
    scanf("%s", str);

    int n = strlen(str);

    int front = 0;
    while (front < n && str[front] == 'a') front++;

    int back = 0;
    while (back < n && str[n-1-back] == 'a') back++;

    if (front > back) {
        printf("No");
        return ;
    }

    int j = n-1-back;

    for (int i = front; i < n-1-back; i++, j--) {
        if (str[i] != str[j]) {
            printf("No");
            return ;
        }
    }

    printf("Yes");



    
}
 
signed main() {
    int t;
    t=1;
    // scanf("%d", &t);
    while (t--) {
        solve();
    }
}