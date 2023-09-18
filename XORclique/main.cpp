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
        int count[31]; ms(count, 0);
        for (int i = 0; i < n; i++) {
            int a; cin >> a;

            for (int j = 30; j >= 0; j--) {
                if (a & (1 << j)) {
                    count[j]++;
                    break;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < 31; i++) {
            ans = max(ans, count[i]);
        }
        cout << ans << '\n';
    }
}
/*

*/
