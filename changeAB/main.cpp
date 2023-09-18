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

    int n; cin >> n;
    int A[n], B[n], C[n];
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    int s = 0;
    for (int i = 0; i < n; i++) {
        C[i] = A[i] - B[i];
        s += C[i];
    }
    if (s != 0) {
        cout << -1;
        return 0;
    }

    int dp[5000000], sum[5000000]; ms(dp, 0); ms(sum, 0);
    for (int mask = 0; mask < (1 << n); mask++) { // iterate over masks
        for (int i = 0; i < n; i++) { // iterate through bits
            if (!(mask & (1 << i))) { // if the bit is off
                int next = mask ^ (1 << i);
                sum[next] = sum[mask] + C[i]; // find sum

                if (sum[next] == 0) dp[next] = max(dp[next], dp[mask] + 1); // good subset, one more
                else dp[next] = max(dp[next], dp[mask]); // not good subset
            }
        }
    }
    cout << n - dp[(1 << n) - 1];
}
/*
impossible if sum of C != 0
  upper bound on the answer is N − 1, because we can fix exactly one element with each operation, except for the last operation which fixes the final two elements
  partition into disjoint subsets
  min operations for each subset S_i = S_i - 1 operations
   dp[mask] = max sequence of zero-sum subsets contained within mask
 transitions from subsets to one bit differing
*/
