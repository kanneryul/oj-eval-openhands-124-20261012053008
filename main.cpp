#include <iostream>
#include <vector>
#include <algorithm>

// Segment tree for range maximum query with lazy propagation
class SegmentTree {
private:
    std::vector<int> tree;
    std::vector<int> lazy;
    int n;

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
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
        tree[node] = std::max(tree[node * 2], tree[node * 2 + 1]);
    }

    int query_range(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return 0;
        
        push(node, start, end);
        if (start >= l && end <= r) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        int left_val = query_range(node * 2, start, mid, l, r);
        int right_val = query_range(node * 2 + 1, mid + 1, end, l, r);
        return std::max(left_val, right_val);
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void update(int l, int r, int val) {
        update_range(1, 0, n - 1, l, r, val);
    }

    int query(int l, int r) {
        return query_range(1, 0, n - 1, l, r);
    }
};

int main() {
    int x, k, p;
    std::cin >> x >> k >> p;
    
    SegmentTree seg_tree(x);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        std::cin >> u >> v >> n;
        
        // Convert to 0-based indexing
        u--; v--;
        
        // Check if we can allocate n seats for this journey
        // For journey from u to v, we need to check segments [u, v-1]
        if (u >= v) {
            std::cout << "N\n";
            continue;
        }
        
        int max_seats = seg_tree.query(u, v - 1);
        
        if (max_seats + n <= k) {
            // Allocate seats
            seg_tree.update(u, v - 1, n);
            std::cout << "T\n";
        } else {
            std::cout << "N\n";
        }
    }
    
    return 0;
}