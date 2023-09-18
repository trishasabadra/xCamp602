/*
Problem: Editorial for Two
URL: https://codeforces.com/problemset/problem/1837/F
*/
#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))
const int MX = 3e5+5, MOD = 1e9+7;

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
typedef pair<ll, ll> pl;
#define f first
#define s second

int a[MX], n, k;
bool check(ll L) {
    // prefix
    priority_queue<ll> pq; // <cur num, cur sum>
    pq.push(0);
    ll mnPref[n+1], mnSuff[n+1], sum = 0;
    mnPref[0] = 0;
    for (int i = 0; i < n; i++) {
        ll num = pq.top();
        if (sum + a[i] <= L) { // can add a[i]
            pq.push(a[i]);
            sum += a[i]; // add to sum
            mnPref[i+1] = mnPref[i];
        }
        else if (num > a[i]) { // remove top, add a[i] instead
            pq.pop();
            pq.push(a[i]);
            sum = sum - num + a[i];
            mnPref[i+1] = mnPref[i]+1;
        }
        else mnPref[i+1] = mnPref[i]+1; // discard a[i]
    }

    // suffix
    while (!pq.empty()) pq.pop();
    pq.push(0);
    mnSuff[n] = 0; sum = 0; // sum is now suffix sum
    for (int i = n-1; i >= 0; i--) {
        ll num = pq.top();
        if (sum + a[i] <= L) { // can add a[i]
            pq.push(a[i]);
            sum += a[i]; // add to sum
            mnSuff[i] = mnSuff[i+1];
        }
        else if (num > a[i]) { // remove top, add a[i] instead
            pq.pop();
            pq.push(a[i]);
            sum = sum - num + a[i];
            mnSuff[i] = mnSuff[i+1]+1;
        }
        else mnSuff[i] = mnSuff[i+1]+1; // discard a[i]
    }

    for (int i = 1; i <= n; i++) {
        if (mnPref[i] + mnSuff[i] <= n-k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 0; i < n; ++i) cin >> a[i];

         ll l = 0, r = 1e15;
        //ll l = 0, r = 15;
        while (l + 1 < r) {
            ll mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid;
        }
        cout << r << endl;
    }
}
/*
 binary search on answer L.
 Sweep from left and right to get prefix and suffix.
mn_pref[i] = from the first i elements, min # elements to remove to keep sum ≤ L (do same for mn_suff for last i elements
Use priority queue to store elements from greatest to least, to compare the new element with the largest element.
At the end, scan through and take suffix and prefix at that point

 2.
 to count # of distinct numbers: since we're removing from the right, we can store the first occurrence of each element
 sort by <first occurrence, element>
 don't delete, instead keep pointer of last element in array (if last index is 5 and then we delete 3, the last index is now 2
 keep set of positions for each value (set<int> indices[])
 1 if first occurrence, else 0. fenwick tree prefix sum array to keep track of # of distinct elements after we update everytime

 3.
 trick: d(u, v) = d(root, u) + d(root, v) - 2 * d(root, lca(u, v))
v = 2*x + y
 x = v/2, y = remainder

 4.
 maximize max and minimize min
 so this basically takes advantage of the fact that the best path will automatically choose to subtract the maximum edge and add the minimum edge
}

*/
