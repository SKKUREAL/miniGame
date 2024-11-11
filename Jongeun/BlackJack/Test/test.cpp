#include <vector>
#include <queue>
using namespace std;


struct SegmentTree {
    int n;
    vector<pair<int, int>> tree;  // Each node stores (score, -index) for tie-breaking

    // Build the Segment Tree
    SegmentTree(const vector<int>& score) {
        n = score.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, score);
    }

    void build(int node, int l, int r, const vector<int>& score) {
        if (l == r) {
            tree[node] = make_pair(score[l], -l);
        } else {
            int m = (l + r) / 2;
            build(2 * node, l, m, score);
            build(2 * node + 1, m + 1, r, score);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    // Query the maximum in a given range
    pair<int, int> query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) {
            return make_pair(-1, -1);  // Return minimum if out of range
        }
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int m = (l + r) / 2;
        return max(query(2 * node, l, m, ql, qr),
                   query(2 * node + 1, m + 1, r, ql, qr));
    }

    // Update the score at a specific index
    void update(int node, int l, int r, int idx) {
        if (l == r) {
            tree[node] = make_pair(-1, -1);  // Mark as removed
        } else {
            int m = (l + r) / 2;
            if (idx <= m) {
                update(2 * node, l, m, idx);
            } else {
                update(2 * node + 1, m + 1, r, idx);
            }
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }
};

long sumVips(vector<int> score, int guilder_count, int k) {
  int n = score.size();
    long long sum = 0;  // Use long long to prevent overflow
    int l = 0, r = n - 1;

    // Max-heap (score, -index)
    priority_queue<pair<int, int>> pq;
    vector<bool> in_pq(n, false);    // Tracks if an index is already in the heap
    vector<bool> selected(n, false); // Tracks if an index has been selected

    // Initialize the candidates from both ends
    for (int i = l; i <= min(l + k - 1, r); ++i) {
        pq.push({score[i], -i});
        in_pq[i] = true;
    }
    for (int i = max(r - k + 1, l); i <= r; ++i) {
        if (!in_pq[i]) {
            pq.push({score[i], -i});
            in_pq[i] = true;
        }
    }

    int count = 0;
    while (count < guilder_count && !pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int idx = -top.second;

        if (selected[idx]) {
            continue;
        }

        sum += top.first;  // Add the score to the sum
        selected[idx] = true;
        count++;

        // Update pointers and push new candidates if necessary
        if (idx == l) {
            l++;
            if (l <= r) {
                int new_idx = l + k - 1;
                if (new_idx <= r && !in_pq[new_idx]) {
                    pq.push({score[new_idx], -new_idx});
                    in_pq[new_idx] = true;
                }
            }
        } else if (idx == r) {
            r--;
            if (l <= r) {
                int new_idx = r - k + 1;
                if (new_idx >= l && !in_pq[new_idx]) {
                    pq.push({score[new_idx], -new_idx});
                    in_pq[new_idx] = true;
                }
            }
        }
    }

    return sum;
}
