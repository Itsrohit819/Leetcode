class Solution {
public:
    int f(long long x) {
        if (x == 1) return 0;
        return 1 + f(__builtin_popcountll(x));
    }
    
    struct S {
        int n;
        vector<vector<int>> t;
    
        S(vector<int>& d) {
            n = d.size();
            t.resize(4 * n, vector<int>(6));
            b(d, 0, n - 1, 0);
        }
    
        void b(vector<int>& d, int l, int r, int i) {
            if (l == r) {
                t[i][d[l]] = 1;
                return;
            }
            int m = (l + r) / 2;
            b(d, l, m, 2 * i + 1);
            b(d, m + 1, r, 2 * i + 2);
            mrg(i);
        }
    
        void mrg(int i) {
            for (int k = 0; k < 6; k++)
                t[i][k] = t[2 * i + 1][k] + t[2 * i + 2][k];
        }
    
        void u(int p, int v, int l, int r, int i) {
            if (l == r) {
                fill(t[i].begin(), t[i].end(), 0);
                t[i][v] = 1;
                return;
            }
            int m = (l + r) / 2;
            if (p <= m) u(p, v, l, m, 2 * i + 1);
            else u(p, v, m + 1, r, 2 * i + 2);
            mrg(i);
        }
    
        vector<int> q(int ql, int qr, int l, int r, int i) {
            if (ql <= l && r <= qr) return t[i];
            int m = (l + r) / 2;
            vector<int> res(6);
            if (ql <= m) {
                auto a = q(ql, qr, l, m, 2 * i + 1);
                for (int k = 0; k < 6; k++) res[k] += a[k];
            }
            if (qr > m) {
                auto b = q(ql, qr, m + 1, r, 2 * i + 2);
                for (int k = 0; k < 6; k++) res[k] += b[k];
            }
            return res;
        }
    };

    vector<int> popcountDepth(vector<long long>& a, vector<vector<long long>>& q) {
        int n = a.size();
        vector<int> d(n);
        for (int i = 0; i < n; i++) d[i] = f(a[i]);
        vector<long long> trenolaxid = a;
        S s(d);
        vector<int> res;
        for (auto& x : q) {
            if (x[0] == 1) {
                auto v = s.q(x[1], x[2], 0, n - 1, 0);
                res.push_back(v[x[3]]);
            } else {
                int i = x[1];
                a[i] = x[2];
                s.u(i, f(x[2]), 0, n - 1, 0);
            }
        }
        return res;
    }
};