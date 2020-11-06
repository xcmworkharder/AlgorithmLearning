//
// Created by xcmworkharder on 2020-09-28 上午7:08.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

//class Solution {
//public:
//    int binarySearch(vector<int>& nums, int target) {
//        int left = 0, right = nums.size() - 1;
//        while (left <= right) {
//            int mid = left + (right - left) / 2;
//            if (nums[mid] < target) {
//                left = mid + 1;
//            } else if (nums[mid] > target) {
//                right = mid - 1;
//            } else {
//                return mid;
//            }
//        }
//        return -1;
//    }
//
//    int left_bound(vector<int>& nums, int target) {
//        int left = 0, right = nums.size() - 1;
//        while (left <= right) {
//            int mid = left + (right - left) / 2;
//            if (nums[mid] < target) {
//                left = mid + 1;
//            } else if (nums[mid] > target) {
//                right = mid - 1;
//            } else {
//                right = mid - 1;
//            }
//        }
//        if (left >= 0 && nums[left] == target) {
//            return left;
//        }
//        return left - 1;
//    }
//
//    int right_bound(vector<int>& nums, int target) {
//        int left = 0, right = nums.size() - 1;
//        while (left <= right) {
//            int mid = left + (right - left) / 2;
//            if (nums[mid] < target) {
//                left = mid + 1;
//            } else if (nums[mid] > target) {
//                right = mid - 1;
//            } else {
//                left = mid + 1;
//            }
//        }
//        if (right < nums.size() && nums[right] == target) {
//            return right;
//        }
//        return right + 1;
//    }
//
//    int leftBound(const vector<int>& nums, int target) {
//        int left = 0, right = nums.size() - 1;
//        while (left <= right) {
//            int mid = left + (right - left) / 2;
//            if (nums[mid] < target) {
//                left = mid + 1;
//            } else {
//                right = mid - 1;
//            }
//        }
//        if (right < nums.size() - 1 && nums[right + 1] == target) {
//            return right + 1;
//        }
//        return right;
//    }
//
//    int rightBound(const vector<int>& nums, int target) {
//        int left = 0, right = nums.size() - 1;
//        while (left <= right) {
//            int mid = left + (right - left) / 2;
//            if (nums[mid] > target) {
//                right = mid - 1;
//            } else {
//                left = mid + 1;
//            }
//        }
//        if (left > 0 && nums[left - 1] == target) {
//            return left - 1;
//        }
//        return left;
//    }
//};

class Solution {
private:
    int binarySearch(const vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > target) {
                right = mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
//     int right_bound(const vector<int>& nums, int target) {
//         int left = 0, right = nums.size() - 1;
//         while (left <= right) {
//             int mid = left + (right - left) / 2;
//             if (nums[mid] > target) {
//                 right = mid - 1;
//             } else {
//                 left = mid + 1;
//             }
//         }
//         if (left > 0 && nums[left - 1] == target) {
//             return left - 1;
//         }
//         return left;
//     }
//    int left_bound(const vector<int>& nums, int target) {
//        int left = 0, right = nums.size() - 1;
//        while (left < right) {
//            int mid = left + (right - left) / 2;
//            if (nums[mid] < target) {
//                left = mid + 1;
//            } else {
//                right = mid;
//            }
//        }
//        return left;
//    }

public:
    vector<int> lengthOfLIS(vector<int>& nums) {
        // 1. 动态规划解法 时间复杂度为O(n2)
        // int n = nums.size();
        // if (n <= 1) {
        //     return n;
        // }
        // vector<int> dp(n, 1);
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < i; j++) {
        //         if (nums[j] < nums[i]) {
        //             dp[i] = max(dp[i], dp[j] + 1);
        //         }
        //     }
        // }
        // // 返回最大的子序列
        // return *max_element(dp.begin(), dp.end());

        // 2. 利用二分查找进行分堆排序, 复杂度为O(nlogn)
        /**
        // [6, 3, 5, 10, 11, 2, 9, 14, 13, 7, 4, 8, 12]
        // 过程[6]->[3]->[3,5]->[3, 5, 10]->[3, 5, 10, 11]->[2, 5, 10, 11]
        // ->[2, 5, 9, 11]->[2, 5, 9, 11, 14]->[2, 5, 9, 11, 13]->[2, 5, 7, 11, 14]
        // ->[2, 4, 7, 11, 14]->[2, 4, 7, 8, 14]->[2, 4, 7, 8, 12]
        */
        vector<int> res;
        for (auto n : nums) {
            if (res.empty() || res.back() < n) {
                res.emplace_back(n);
            }
            int index = binarySearch(nums, n);
            res[index] = n;
        }
        return res;
    }
};

bool specialSort(vector<int>& a, vector<int>& b) {
    if (a[1] < b[1]) {
        return true;
    } else if (a[1] == b[1]) {
        return a[0] < b[0];
    } else {
        return false;
    }
}

int left_bound(vector<int>& arr, int target) {
    int lo = 0, hi = arr.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
        return lo;
    }
}

int main() {

    string S{"abcde"};
    vector<string> words = {"a", "bb", "acd", "ace"};
//    unordered_map<char, vector<int>> sMap;
//    for (int i = 0; i < str.size(); ++i) {
//        sMap[str[i]].push_back(i);
//    }
//    for (auto& map : sMap) {
//        cout << map.first << ": {";
//        for (auto v : map.second) {
//            cout << v << ",";
//        }
//        cout << "}" << endl;
//    }

    int res = 0, j;
    for (int i = 0; i < words.size(); i ++) {
        int position = -1;
        for (j = 0; j < words[i].size(); j ++) {
            position = S.find_first_of(words[i][j], position + 1); // 从下标position + 1开始遍历
            if (position == -1) break;  //若未找到弹出
        }
        if (j == words[i].length()) res ++; //表示str已全部被遍历了，则为其子串
    }
    cout << res << endl;

//    vector<int> arr{1, 3, 3, 5, 6};
//    cout << lower_bound(arr.begin(), arr.end(), 5) - arr.begin() << endl;

//    vector<vector<int>> arr{{1, 2}, {2, 3}, {3, 4}, {1, 3}};
//    sort(arr.begin(), arr.end(), specialSort);
//    for (auto ar : arr) {
//        for (auto a : ar) {
//            cout << a << " ";
//        }
//        cout << endl;
//    }

//    vector<int> arr{6, 3, 5, 10, 11, 2, 9, 14, 13, 7, 4, 8, 12};
//    vector<int> res = Solution().lengthOfLIS(arr);
//    for (auto r : res) {
//        cout << r << endl;
//    }

//    vector<int> arr{1, 3, 5, 7, 9};
//    cout << Solution().binarySearch(arr, 7) << endl;
//    cout << Solution().left_bound(arr, 8) << endl;
//    cout << Solution().right_bound(arr, 8) << endl;
//    cout << "--------------------" << endl;
//    cout << Solution().leftBound(arr, 5) << endl;
//    cout << Solution().rightBound(arr, 5) << endl;
    return 0;
}


