class Solution {
public:
    const int MOD = 1e9 + 7;

    long long mod_pow(long long a, long long b) {
        long long res = 1;
        while (b > 0) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }
    
    long long mod_inv(long long a) {
        return mod_pow(a, MOD - 2);
    }
    int countTrapezoids(vector<vector<int>>& points) {
        unordered_map<int, int> freq;

        for (auto& p : points)
            freq[p[1]]++;
    
        long long sum = 0, square_sum = 0;
    
        for (auto& [y, cnt] : freq) {
            if (cnt < 2) continue;
            long long seg = 1LL * cnt * (cnt - 1) / 2;
            sum = (sum + seg) % MOD;
            square_sum = (square_sum + seg * seg % MOD) % MOD;
        }
    
        long long ans = (sum * sum % MOD - square_sum + MOD) % MOD;
        ans = ans * mod_inv(2) % MOD;
    
        return (int)ans;
        }
};