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

  int q; cin >> q;
  while (q--) {
      int n, t; cin >> n >> t;
      vector<pair<int, pi>> arr(n); // <confidence level, time it takes to learn, index>
      for (int i = 0; i < n; i++) {
          cin >> arr[i].s.f >> arr[i].f;
          arr[i].s.s = i;
      }

      sort(arr.begin(), arr.end()); // sort based on minimum confidence level

      map<int, set<int>> mp; // <k, set of indices>
      int l = 0, r = n-1; // left, right
      while (l < r) {
          int k = (r + l + 1) / 2; // maximize k confident problems
          cout << l << " " << r << " " << k << "\n"; // debug
          bool isPos = false; // verify if k is possible

          // prefix, always keep k elements
          priority_queue<pair<int, pi>> pq, pq2; // <time, # of topics>
          int time = 0, pre[n];
          for (int i = 0; i < n; i++) { // i = total # topics
              if (i < k) {
                  pq.push({arr[i].s.f, {arr[i].f, arr[i].s.s}});
                  time += arr[i].s.f;
              }
              else if (pq.top().f > arr[i].s.f && arr[i].f <= i+1) { // current takes less time, swap out
                  time -= pq.top().f;
                  pq.pop();
                  pq.push({arr[i].s.f, {arr[i].f, arr[i].s.s}});
                  time += arr[i].s.f;
              }
              pre[i] = time;
          }
          for (int i = 0; i < n; i++) cout << pre[i] << " ";
          cout << "\n";

          // suffix, always keep top m-k elements
            int suf[n]; time = 0;
            for (int i = n-1; i >= 0; i--) { // i = total # topics
                if (pq2.size() < i-k+1) {
                    pq2.push({arr[i].s.f, {arr[i].f, arr[i].s.s}});
                    time += arr[i].s.f;
                }
                else if (pq2.top().f > arr[i].s.f) { // current takes less time, swap out
                    time -= pq2.top().f;
                    pq2.pop();
                    pq2.push({arr[i].s.f, {arr[i].f, arr[i].s.s}});
                    time += arr[i].s.f;
                }
                while (pq2.size() > i-k+1) {
                    time -= pq2.top().f;
                    pq2.pop();
                }
                suf[i] = time;
            }
          for (int i = 0; i < n; i++) cout << suf[i] << " ";
          cout << "\n";

          for (int i = k-1; i < n && k != 0; i++) {
                if (pre[i] + suf[i] <= t) {
                    isPos = true; break;
                }
            }

            if (isPos) l = k;
            else r = k-1;

            set<int> se;
          while (!pq.empty()) {
              se.insert(pq.top().s.s+1);
              pq.pop();
          }
          while (!pq2.empty()) {
              se.insert(pq2.top().s.s+1);
              pq2.pop();
          }
          mp.insert({k, se});
      }
        cout << l << "\n" << mp.size() << "\n";
      for (int i : mp.find(l)->s) cout << i << " ";
  }
}
/*
want to maximize k confident problems -> binary search on k
 iterate over m = # total topics
m ≥ k

prefix: always keep k elements
 - calculate the smallest amount of time for k of first m problems
 suffix: always keep top m-k elements
 - # of elements in pq decreases as we extend suffix
 - smallest time for m-k from the suffix

 iterate over all m and if pref + suff < t, then k is valid

 2
4 100
20 1
40 4
60 3
30 3
1 5
10 1

 1
4 100
20 1
40 4
60 3
30 3

*/
