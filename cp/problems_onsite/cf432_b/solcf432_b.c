#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int long long

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
#define abs(a) a < 0 ? -a : a
#define MAXN (int)1e9 + 5


void solve() {
    int ax, ay, bx, by , cx, cy;
    scanf("%lld%lld%lld%lld%lld%lld", &ax, &ay, &bx, &by , &cx, &cy);

    // printf("%lld %lld %lld %lld %lld %lld", ax, ay, bx, by , cx, cy);
    int dx1 = ax - bx, dy1 = ay - by;
    int dx2 = bx - cx, dy2 = by - cy;
    int dis1 = dx1*dx1 + dy1*dy1;
    int dis2 = dx2*dx2 + dy2*dy2;

    int cross = (bx - ax)*(cy - ay)
                    - (by - ay)*(cx - ax);

    // printf("%lld %lld", dis1, dis2);

    if (cross == 0 || dis1 != dis2) {
        printf("No\n");
    } else {
        printf("Yes\n");
    }
}
 
signed main() {
    int t;
    t=1;
    // scanf("%lld", &t);
    while (t--) {
        solve();
    }
}