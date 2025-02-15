#include <bits/stdc++.h>

#define int              long long
#define vi              vector<int >
#define vii              vector<vector<int > >
#define pii             pair<int , int >
#define R(i , n, a) for(int i = n; i >= a; i--)
#define all(x) begin(x), end(x)
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "

using namespace std;
const int MOD = 1e9 + 7;

vii adj = {
    {0, 0 , 0 , 0},
    {9, 2 ,3 ,5},
    {10, 1, 4 ,6},
    {11, 1, 4, 7},
    {12, 2, 3, 8},
    {13, 1, 6, 7},
    {14, 2, 5, 8},
    {15, 3, 5, 8},
    {16, 4, 6, 7},
    {1, 10, 11, 13},
    {2, 9, 12, 14},
    {3, 9, 12 ,15},
    {4, 10, 11, 16},
    {5, 9, 14, 15},
    {6, 10, 13, 16},
    {7, 11, 13, 16},
    {8, 12, 14, 15},  
};

void solve(int cs){
    cout << "case #" << cs << ": ";

    vi arr(17);

    for (int i = 1; i <= 16; i++) {
        cin >> arr[i];
    }

    vector<int> s;

    int op = 3;

    for(int i = 1; i <= 8; i++){
        if(arr[i]){
            if(!arr[i + 8]){
                if(!op){
                    cout << "more\n";
                    return;
                }
                op--;
                arr[i] = 0;
                arr[i + 8] = 1;
            } else {
                s.push_back(i);
            }
        }
    }

    if(s.size() > 1){
        cout << "more\n";
        return;
    } 

    if(s.size() == 0){
        cout << 3 - op << endl;
        return;
    }

    queue<pii> q;

    q.push({s[0], op});

    while(!q.empty()){
        pii node = q.front(); q.pop();

        if(node.second == -1){
            break;
        }

        if(node.first > 8 && arr[node.first] == 0){
            cout << 3 - node.second << endl;
            return;
        }

        for(int nei : adj[node.first]){
            q.push({nei, node.second - 1});
        }
    }

    cout << "more\n";

}


signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    for(int i =1; i <= t; i++) solve(i);
}