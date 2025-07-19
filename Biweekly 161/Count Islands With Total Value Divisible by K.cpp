class Solution {
public:
    int countIslands(vector<vector<int>>& g, int k) {
        int m = g.size(), n = g[0].size(), c = 0;
        vector<vector<bool>> v(m, vector<bool>(n));
        int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j] > 0 && !v[i][j]) {
                    long long s = 0;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    v[i][j] = 1;
                    
                    while (!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        s += g[x][y];
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d], ny = y + dy[d];
                            if (nx >= 0 && ny >= 0 && nx < m && ny < n && g[nx][ny] > 0 && !v[nx][ny]) {
                                v[nx][ny] = 1;
                                q.push({nx, ny});
                            }
                        }
                    }
                    
                    if (s % k == 0) c++;
                }
            }
        }
        
        return c;
    }
};