#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <stack>
using namespace std;
#define pi pair<int, int>;
#define f first;
#define s second;
const int MX = 1e6+1;
int BIT[MX] = {};
void update(int x, int delta) { // increment index x by delta
    for(++x; x <= MX; x += x&-x)
        BIT[x] += delta; // update for all parents
}
int query(int x) { // find prefix sum at index x
    int sum = 0;
    for(++x; x > 0; x -= x&-x)
        sum += BIT[x];
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q; cin >> q;
    int arr[MX];
    for (int i = 0; i < MX; i++) arr[i] = -1;
    set<int> pos[MX];
    stack<pair<char, int>> queries; // <op, update>
    int cur = 0;

    for (int i = 0; i < q; i++) {
        char c; cin >> c;

        if (c == '+') {
            int x; cin >> x;
            cur++;
            int old = arr[cur];
            // out with the old
            if (old != -1) {
                if (pos[old].size()) {
                    update(*pos[old].begin(), -1);
                    pos[old].erase(cur);
                }
                if (pos[old].size()) {
                    update(*pos[old].begin(), 1);
                }
            }
            // in with the new
            arr[cur] = x;
            if (arr[cur] != -1) {
                if (pos[x].size()) {
                    update(*pos[x].begin(), -1);
                }
                pos[x].insert(cur);
                if (pos[x].size()) {
                    update(*pos[x].begin(), 1);
                }
            }
            queries.push({c, old}); // add to queries
        }
        else if (c == '-') {
            int a; cin >> a;
            cur -= a;
            queries.push({c, a}); // add to queries
        }
        else if (c == '?') cout << query(cur) << endl;
        else { // rollback
            char op = queries.top().f; int val = queries.top().s; queries.pop();
            if (op == '+') {
                int last = arr[cur];
                if (last != -1) {
                    if (pos[last].size()) {
                        update(*pos[last].begin(), -1);
                        pos[last].erase(cur);
                    }
                    if (pos[last].size()) {
                        update(*pos[last].begin(), 1);
                    }
                }
                arr[cur] = val;
                if (arr[cur] != -1) {
                    if (pos[val].size()) {
                        update(*pos[val].begin(), -1);
                    }
                    pos[val].insert(cur);
                    if (pos[val].size()) {
                        update(*pos[val].begin(), 1);
                    }
                }
                cur--;
            }
            else cur += val; // subtract
        }

        // for (int i = 0; i <= cur; i++) cout << BIT[i] << " "; cout << endl;
//        for (int i : arr) cout << i << " ";
//        cout << endl << cur << endl;

    }
}
/*
to count # of distinct numbers: since we're removing from the right, we can store the first occurrence of each element
 sort by <first occurrence, element>
 don't delete, instead keep pointer of last element in array (if last index is 5 and then we delete 3, the last index is now 2
 keep set of positions for each value (set<int> indices[])
 1 if first occurrence, else 0. fenwick tree prefix sum array to keep track of # of distinct elements after we update everytime
*/
