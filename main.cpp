#include <cstdio>
#include <vector>
#include <algorithm>

// Segment tree for range maximum query with lazy propagation
class SegmentTree {
private:
    std::vector<int> max_val;  // maximum value in the range
    std::vector<int> lazy;     // lazy propagation values
    int n;

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            max_val[node] += lazy[node];
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update_range(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);
        if (start > r || end < l) return;
        
        if (start >= l && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        
        int mid = (start + end) / 2;
        update_range(node * 2, start, mid, l, r, val);
        update_range(node * 2 + 1, mid + 1, end, l, r, val);
        max_val[node] = std::max(max_val[node * 2], max_val[node * 2 + 1]);
    }

    int query_range(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return 0;
        
        push(node, start, end);
        if (start >= l && end <= r) {
            return max_val[node];
        }
        
        int mid = (start + end) / 2;
        int left_val = query_range(node * 2, start, mid, l, r);
        int right_val = query_range(node * 2 + 1, mid + 1, end, l, r);
        return std::max(left_val, right_val);
    }

public:
    SegmentTree(int size) {
        n = size;
        max_val.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void update(int l, int r, int val) {
        if (l <= r) {
            update_range(1, 0, n - 1, l, r, val);
        }
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return query_range(1, 0, n - 1, l, r);
    }
};

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    SegmentTree seg_tree(x);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Convert to 0-based indexing
        u--; v--;
        
        // For journey from u to v, we need to check segments [u, v-1]
        if (u >= v) {
            printf("N\n");
            continue;
        }
        
        // Check if we can allocate n seats for this journey
        int max_seats = seg_tree.query(u, v - 1);
        
        if (max_seats + n <= k) {
            // Allocate seats
            seg_tree.update(u, v - 1, n);
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}