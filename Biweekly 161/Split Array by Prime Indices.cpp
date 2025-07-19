class Solution {
public:
    bool p(int x) {
        if (x < 2) return false;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    }

    long long splitArray(vector<int>& nums) {
        long long a = 0, b = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (p(i)) a += nums[i];
            else b += nums[i];
        }
        return abs(a - b);
    }
};