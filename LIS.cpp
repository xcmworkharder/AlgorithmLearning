//
// Created by xcmworkharder on 2020-10-13 上午8:41.
//
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> keepDP, keepPos;
public:
    /**
     * retrun the longest increasing subsequence
     * @param arr int整型vector the array
     * @return int整型vector
     */
    vector<int> LIS(vector<int>& arr) {
        // write code here
        int n = arr.size();
        if (n <= 1) {
            return arr;
        }
        vector<int> dp(n, 0);     // 记录数组中递增元素
        vector<int> pos(n, 0);    // pos[i] = j 记录nums[i]在dp中的位置
        int len = 0; // 递增元素的索引
        dp[len] = arr[0];
        for (int i = 1; i < n; ++i) {
            if (arr[i] > dp[len]) {
                dp[++len] = arr[i];
                pos[i] = len;
            } else {
                int low = 0, high = len;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    if (dp[mid] < arr[i]) {
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }
                if (low != -1) {
                    dp[low] = arr[i];
                    pos[i] = low;
                } else {
                    dp[0] = arr[i];
                    pos[i] = 0;
                }
            }
        }

        keepDP = dp;
        keepPos = pos;

        vector<int> res(len + 1, INT_MAX);
        for (int i = n - 1; i >= 0; i--) {
            if (pos[i] == len) {
                res[len] = min(res[len], arr[i]);
                len--;
            }
        }

        return res;
    }
};

int main() {

    vector<int> arr{1, 4, 2, 3, 2, 5, 6, 8, 7, 9};

    Solution solution;
    vector<int> res = solution.LIS(arr);

    for (auto r : res) {
        cout << r << " ";
    }
    cout << endl;

    for (auto d : solution.keepDP) {
        cout << d << " ";
    }
    cout << endl;

    for (auto p : solution.keepPos) {
        cout << p << " ";
    }
    cout << endl;

    return 0;
}

