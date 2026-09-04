#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct LazySegmentTree {
    int n;
    vector<T> tree, lazy;
    vector<bool> has_lazy;

    LazySegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        has_lazy.assign(4 * n, false);
    }

    void build(const vector<T>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node + 1, start, mid);
        build(arr, 2 * node + 2, mid + 1, end);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // MERGE
    }

    void push(int node, int start, int end) {
        if (has_lazy[node]) {
            // 1. Apply lazy value to the current node (Range Sum logic)
            tree[node] += lazy[node] * (end - start + 1);

            // 2. Propagate to children if not a leaf
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                has_lazy[2 * node + 1] = true;
                
                lazy[2 * node + 2] += lazy[node];
                has_lazy[2 * node + 2] = true;
            }

            // 3. Clear the lazy state
            lazy[node] = 0;
            has_lazy[node] = false;
        }
    }

    void update(int node, int start, int end, int l, int r, T val) {
        push(node, start, end);
        if (start > r || end < l) return; // Out of bounds
        if (start >= l && end <= r) {     // Fully in bounds
            lazy[node] += val;
            has_lazy[node] = true;
            push(node, start, end);
            return;
        }
        int mid = start + (end - start) / 2;
        update(2 * node + 1, start, mid, l, r, val);
        update(2 * node + 2, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // MERGE
    }

    T query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (start > r || end < l) return 0; // NULL VALUE
        if (start >= l && end <= r) return tree[node];
        
        int mid = start + (end - start) / 2;
        T left_ans = query(2 * node + 1, start, mid, l, r);
        T right_ans = query(2 * node + 2, mid + 1, end, l, r);
        return left_ans + right_ans; // MERGE
    }
    
    // Wrapper functions for easier usage
    void build(const vector<T>& arr) { build(arr, 0, 0, n - 1); }
    void update(int l, int r, T val) { update(0, 0, n - 1, l, r, val); }
    T query(int l, int r) { return query(0, 0, n - 1, l, r); }
};


/*
Customization Guide

To adapt this template for different problem types, modify the marked sections:

    Change to Range Minimum/Maximum: Replace the + operator with min() or max() wherever // MERGE is written. Update the NULL VALUE in the query function to infinity (for minimum) or negative infinity (for maximum).

    Change to Range Assignment: In the push and update functions, instead of adding to the existing lazy value (lazy[child] += lazy[node]), overwrite it (lazy[child] = lazy[node]).

    Change Node State: If the problem requires maintaining multiple states (e.g., maximum sum subarray), replace vector<T> tree with a custom struct and update the merge logic accordingly.
*/