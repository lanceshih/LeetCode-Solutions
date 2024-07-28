// Time:  O(n * sqrt(n)) = O(n^(3/2))
// Space: O(n)

// two pointers, sliding window
class Solution {
public:
    int numberOfSubstrings(string s) {
        int result = 0;
        vector<int> idxs = {-1};
        for (int i = 0; i < size(s); ++i) {
            if (s[i] == '0') {
                idxs.emplace_back(i);
            }
        }
        idxs.emplace_back(size(s));
        for (int i = 0, curr = 1; i < size(s); ++i) {
            if (idxs[curr] == i) {
                ++curr;
            }
            for (int c = 0; c * c <= min(static_cast<int>(size(s)), (curr - 1) * (curr - 1)); ++c) {
                if (((i - idxs[(curr - c) - 1]) - c) - c * c + 1 >= 1) {
                    result += min((c ? idxs[curr - c] : i) - idxs[(curr - c) - 1], ((i - idxs[(curr - c) - 1]) - c) - c * c + 1);
                }
            }
        }
        return result;
    }
};

// Time:  O(n * sqrt(n)) = O(n^(3/2))
// Space: O(n)
// two pointers, sliding window
class Solution2 {
public:
    int numberOfSubstrings(string s) {
        int result = 0;
        vector<int> idxs = {-1};
        for (int i = 0; i < size(s); ++i) {
            if (s[i] == '0') {
                idxs.emplace_back(i);
            }
        }
        idxs.emplace_back(size(s));
        for (int c = 0; c * c <= size(s); ++c) {
            for (int i = 0, left = 1, right = 1; i < size(s); ++i) {
                if (idxs[right] == i) {
                    ++right;
                }
                if (right - left == c + 1) {
                    ++left;
                }
                if (!(right - left == c && ((i - idxs[left - 1]) - c) >= c * c)) {
                    continue;
                }
                result += min((c ? idxs[left] : i) - idxs[left - 1], ((i - idxs[left - 1]) - c) - c * c + 1);
            }
        }
        return result;
    }
};

// Time:  O(n * sqrt(n)) = O(n^(3/2))
// Space: O(1)
// two pointers, sliding window
class Solution3 {
public:
    int numberOfSubstrings(string s) {
        int result = 0;
        for (int c = 0; c * c <= size(s); ++c) {
            vector<int> cnt(2);
            for (int right = 0, left = 0, curr = 0; right < size(s); ++right) {
                ++cnt[s[right] == '1'];
                while (cnt[0] == c + 1) {
                    --cnt[s[left++] == '1'];
                }
                if (!(cnt[0] == c && cnt[1] >= c * c)) {
                    continue;
                }
                for (curr = max(curr, min(left, right)); curr < right; ++curr) {
                    if (s[curr] == '0') {
                        break;
                    }
                }
                result += min(curr - left + 1, cnt[1] - c * c + 1);              
            }
        }
        return result;
    }
};
