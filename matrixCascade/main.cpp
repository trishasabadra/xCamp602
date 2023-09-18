/*
 Problem: Matrix Cascade
 */
#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))
const int MX = 1e5+5, MOD = 1e9+7;

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
#define f first
#define s second

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t; cin >> t;
  while (t--) {
      int n; cin >> n;
      int a[n][n];
      for (int i = 0; i < n; i++) {
          string s; cin >> s;
          for (int j = 0; j < n; j++) a[i][j] = s[j] == '1' ? 1 : 0;
      }

      int left[n], right[n+1]; ms(left, 0); ms(right, 0);
      int count = 0;
      for (int i = 0; i < n; i++) { // iterate through rows
          // update prefix sum for this row
          int cur = 0;
          for (int j = 0; j < n; j++) {
                cur += left[j] - right[j];
                a[i][j] += cur;
                a[i][j] %= 2; // either 0 or 1
          }

          // update range
          int newL[n], newR[n+1]; ms(newL, 0); ms(newR, 0);
          newL[0] = left[0];
          for (int j = 1; j < n; j++) {
              newL[j-1] += left[j];
              newR[j+1] += right[j];
          }
          for (int j = 0; j < n; j++) left[j] = newL[j], right[j] = newR[j];

          // add new ranges
          for (int j = 0; j < n; j++) {
              if (a[i][j] == 1) { // toggle
                  count++;
                  left[max(0, j - 1)]++;
                  right[min(n, j + 2)]--;
              }
          }
      }
      cout << count << "\n";
  }

}
/*
prefix sum on each row
 update left (+1) and right (-1) of each range
 when moving to next row, update left index goes to left and right goes to right as long as it is not < 0 or > n
*/
