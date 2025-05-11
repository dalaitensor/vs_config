#include <stdio.h>
#include <math.h>
 
void solve() {
    int n;
    scanf("%d", &n);
    printf("%d\n", n + (int)ceil((float)n / 6));
}
 
int main() { 
    int t = 1;
    while (t--) {
        solve();
    }
 
    return 0;
}