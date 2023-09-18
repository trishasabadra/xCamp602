#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))
const int MX = 1e5+5, MOD = 1e9+7; // 1420696969

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
typedef pair<ll, ll> pl;
#define f first
#define s second

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        ll arr[n];
        vector<pair<pl, pl>> intervals; // <start, end> index of same, <cur bit, min dp for interval>
        ll mn[n]; // min dp for prev i elements
        for (int i = 0; i < n; i++) {
            cin >> arr[i];

            if (i == 0) {
                mn[i] = arr[i] - m;
                intervals.push_back({{i, i}, {arr[i], arr[i] - m}});
                continue;
            }

            // iterate through intervals instead of each index
            mn[i] = mn[i-1] + arr[i] - m;
            intervals.push_back({{i, i}, {arr[i], mn[i]}});
            for (int j = intervals.size()-1; j > 0; j--) {
                ll cost = intervals[j].s.f | intervals[j-1].s.f; // cur bit <-- (prev bit | cur bit)

                if (intervals[j-1].f.f == 0) mn[i] = min(mn[i], min(cost - m, intervals[j-1].s.s + cost - m));
                    // prev dp + cur cost - m (keep interval one), prev dp + min dp for interval - m (split interval into two)
                else mn[i] = min(mn[i], min(mn[intervals[j-1].f.f-1] + cost - m, intervals[j-1].s.s + cost - m));

                if (cost == intervals[j].s.f) { // combine intervals
                    intervals[j-1].f.s = intervals[j].f.s; // change end index
                    //intervals[j-1].s.s = min(intervals[j-1].s.s, cost-m); // update min dp for the interval
                    intervals[j-1].s.s = min(intervals[j-1].s.s, intervals[j].s.s); // update min dp for the interval
                    intervals.erase(intervals.begin() + j);
                }
                intervals[j-1].s.f = cost; // update cur bit
            }
            //cout << mn[i] << " ";
        }
        cout << mn[n-1] << "\n";
    }

}
/*

 for each interval (i, j), have to store min dp for all intervals (i, k) where k ≤ j

key: a cell does NOT contribute if s ≤ a ≤ b ≤ t where a is the first occurence and b is the last
*/
