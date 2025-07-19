class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        vector<vector<pair<int,int>>> adj(n);
        vector<int> indeg(n, 0);
        vector<int> allCosts;
        allCosts.reserve(edges.size());
        for (auto &e : edges) {
            allCosts.push_back(e[2]);
        }
        if (allCosts.empty()) return -1;
        int lo = *min_element(allCosts.begin(), allCosts.end());
        int hi = *max_element(allCosts.begin(), allCosts.end());
        int ans = -1;
        vector<long long> dp(n);
        vector<int> indeg2(n);
        auto can = [&](int minC) {
            fill(indeg2.begin(), indeg2.end(), 0);
            for (int i = 0; i < n; i++) adj[i].clear();
            for (auto &e : edges) {
                int u = e[0], v = e[1], c = e[2];
                if (c >= minC && online[u] && online[v]) {
                    adj[u].emplace_back(v, c);
                    indeg2[v]++;
                }
            }
            const long long INF = LLONG_MAX/4;
            for (int i = 0; i < n; i++) dp[i] = INF;
            dp[0] = 0;
            queue<int> q;
            for (int i = 0; i < n; i++) {
                if (indeg2[i] == 0 && online[i]) {
                    q.push(i);
                }
            }
            while (!q.empty()) {
                int u = q.front(); q.pop();
                long long du = dp[u];
                if (du == INF) {
                    for (auto &pr : adj[u]) {
                        int v = pr.first;
                        if (--indeg2[v] == 0) q.push(v);
                    }
                    continue;
                }
                for (auto &pr : adj[u]) {
                    int v = pr.first, c = pr.second;
                    if (du + c <= k && du + c < dp[v]) {
                        dp[v] = du + c;
                    }
                    if (--indeg2[v] == 0) {
                        q.push(v);
                    }
                }
            }
            return dp[n-1] <= k;
        };
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (can(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }

};