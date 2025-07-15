class Solution {
public:
    void go(int u, vector<vector<pair<int, int>>>& g, vector<bool>& vis,
            int lim) {
        vis[u] = 1;
        for (auto [v, w] : g[u]) {
            if (!vis[v] && w <= lim)
                go(v, g, vis, lim);
        }
    }

    int minCost(int n, vector<vector<int>>& e, int k) {
        vector<vector<pair<int, int>>> g(n);
        int mx = 0;
        for (auto& x : e) {
            g[x[0]].push_back({x[1], x[2]});
            g[x[1]].push_back({x[0], x[2]});
            mx = max(mx, x[2]);
        }

        int l = 0, r = mx, ans = mx;
        while (l <= r) {
            int m = (l + r) / 2, c = 0;
            vector<bool> vis(n);
            for (int i = 0; i < n; ++i) {
                if (!vis[i]) {
                    ++c;
                    go(i, g, vis, m);
                }
            }
            if (c <= k)
                ans = m, r = m - 1;
            else
                l = m + 1;
        }
        return ans;
    }
};
