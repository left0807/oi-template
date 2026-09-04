#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct HeavyLightDecomposition {
    int n;
    vector<vector<int>> adj;
    vector<int> sz, dep, fa, son, top, dfn, rnk;
    int cur_cnt;

    HeavyLightDecomposition(int _n) : n(_n), adj(_n + 1), sz(_n + 1), dep(_n + 1), 
                                      fa(_n + 1), son(_n + 1, 0), top(_n + 1), 
                                      dfn(_n + 1), rnk(_n + 1), cur_cnt(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // First DFS: computes subtree sizes, depths, parents, and heavy children
    void dfs1(int u, int p, int d) {
        dep[u] = d;
        fa[u] = p;
        sz[u] = 1;
        int max_sz = -1;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs1(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > max_sz) {
                max_sz = sz[v];
                son[u] = v;
            }
        }
    }

    // Second DFS: computes chain tops, DFS order (dfn), and inverse mapping (rnk)
    void dfs2(int u, int t) {
        top[u] = t;
        dfn[u] = ++cur_cnt;
        rnk[cur_cnt] = u;
        if (!son[u]) return;
        dfs2(son[u], t); // Heavy child gets the same chain head
        for (int v : adj[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v); // Light child starts a new chain
        }
    }

    void init(int root = 1) {
        dfs1(root, 0, 1);
        dfs2(root, root);
    }

    // Standard LCA query
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    // Example function to process paths for range operations (e.g., Segment Tree)
    // Passes intervals [L, R] in the flattened DFS array for each chain segment between u and v
    template <typename Op>
    void process_path(int u, int v, Op op) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            op(dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        op(dfn[u], dfn[v]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    HeavyLightDecomposition hld(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }

    hld.init(1); // Rooted at 1

    // Example path query callback template:
    // hld.process_path(u, v, [&](int l, int r) {
    //     // Query/Update segment tree on range [l, r]
    // });

    return 0;
}