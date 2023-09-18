#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))
const int MOD = 1e9+7;

using namespace std;
typedef long long ll;

void setIO(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    setIO("palpath");

    int n; cin >> n;
    string grid[n];
    for (int i = 0; i < n; i++) cin >> grid[i];

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) cout << grid[i][j] << " ";
//        cout << "\n";
//    }

    ll prev[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) prev[i][j] = 0;
        prev[i][i] = 1;
    }

    for (int a = 1; a < n; a++) { // diagonal
        ll dp[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) dp[i][j] = 0;

        for (int r1 = 0; r1 < n; r1++) { // row
            int c1 = n - 1 - r1 - a;
            if (c1 < 0) continue;

            for (int r2 = 0; r2 < n; r2++) {
                int c2 = n - 1 - r2 + a;
                if (c2 < c1 || c2 >= n || grid[r1][c1] != grid[r2][c2]) continue;

                dp[r1][r2] = prev[r1][r2];
                if (r1 < n-1) dp[r1][r2] += prev[r1+1][r2];
                if (r2 > 0) dp[r1][r2] += prev[r1][r2-1];
                if (r1 < n-1 && r2 > 0) dp[r1][r2] += prev[r1 + 1][r2 - 1];
                dp[r1][r2] %= MOD;
            }
        }
        // copy dp to prev
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) prev[i][j] = dp[i][j];
    }
    cout << prev[0][n-1];
}
/*
middle diagonal is middle of palindrome
 start from middle diagonal and go up and down

 are we starting at the diagonal, or starting at 1, 1?
 not each row has a column that works
 its just the distance from the current to the row
 calculate j, if j >= n, doesn't work

 // iterate by diagonal, bottom to top
*/
