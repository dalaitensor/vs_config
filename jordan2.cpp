#include <bits/stdc++.h>
#include "fraction.hpp"

//#define int              long long
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
int n, m;

typedef struct {
    string x;
    int index;
    flo val;
} item;

typedef struct {
    int r,c;
} pos;

void print(vector<vector<item>>& arr){
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if(arr[i][j].x == "x") cout << "x\n";
            else arr[i][j].val.print();
        }   
        cout << endl;
    }
}


int get(vector<vector<item>> & arr, int row ){
    for (int j = 1; j <= m; j++) {
        if(arr[row][j].val.getNumerator() && arr[0][j].x[0] == 'x'){
            return j;
        }
    }

    return -1;
}


void printSol(vector<vector<item>>& arr){
    for (int i = 1; i <= n; i++) {
        cout << arr[i][0].x << arr[i][0].index << " = ";
        for (int j = 1; j <= m; j++) {
            cout << arr[i][j].val.getNumerator() << "/" << arr[i][j].val.getNumerator() << " + ";
        }
        cout << endl;
    }
}


void solve(){

    cin >> n >> m;

    vector<vector<item>> arr(n + 1, vector<item>(m + 1, {"c", 0, 0}));
    vector<vector<item>> arr1(n + 1, vector<item>(m + 1, {"c", 0, 0}));


    for (int i = 1; i <= m; i++) {
        arr[0][i].x = "x";
        arr[0][i].index = i;
        arr1[0][i].x = "x";
        arr1[0][i].index = i;
    }

    for(int i = 1; i <= n; i++){
        int el;
        // cout << "sul gishuun\nx1 ees xn hurtel daraallan oruulna uu: ";
        for (int j = 0; j <= m; j++) {
            cin >> el;
            flo a(el, 1);
            arr[i][j].val = a;

            cout << arr[0][j].x << " ";
            arr[i][j].val.print();
        }
        cout << endl;
    }

    bool f = true;

    for (int row = 1; row <= n; row++) {
        int col = get(f ? arr : arr1, row);

        debug2(row, col) << endl;
        if(col == -1){
            cout << "not posibble\n";
            return;
        }
        flo el = f ? arr[row][col].val : arr1[row][col].val;

        for(int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++){  
                if(i == row && j == col){
                    if(f) arr1[i][j].val = flo(1,1) / arr[i][j].val;
                    else arr[i][j].val  = flo(1,1) / arr1[i][j].val;
                } else if(i == row){
                    if(f) arr1[i][j].val =  arr[i][j].val / el;
                    else arr[i][j].val = arr1[i][j].val / el;
                } else if(j == col){
                    if(f) arr1[i][j].val = arr[i][j].val / (el * flo(-1, 1));
                    else arr[i][j].val = arr1[i][j].val / (el * flo(-1, 1));
                } else {
                    if(f) arr1[i][j].val = (el * arr[i][j].val - arr[row][j].val * arr[i][col].val) / el;
                    else arr[i][j].val = (el * arr1[i][j].val - arr1[row][j].val * arr1[i][col].val) / el;
                }
            }
        }

        for (int j = 1; j <= m; j++) {
            if(f) arr1[0][j] = arr[0][j];
            else arr[0][j] = arr1[0][j];
        }

        for (int i = 1; i <= n; i++) {
            if(f) arr1[i][0] = arr[i][0];
            else arr[i][0] = arr1[i][0];
        }

        if(f){
            arr1[row][0] = arr[0][col];
            arr1[0][col] = arr[row][0];
        } else {
            arr[row][0] = arr1[0][col];
            arr[0][col] = arr1[row][0];
        }
        print(f ? arr1 : arr);
        // print(f ? arr : arr1);

        f = !f;
    }

    printSol(f ? arr1 : arr);

}


signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }

}