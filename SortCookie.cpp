//
// Created by xcmworkharder on 2020-09-24 上午11:44.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        sort(A, A.size());
        return res;
    }

private:
    vector<int> res;
    void sort(vector<int>& arr, int n) {
        if (n == 1) {
            return;
        }

        // 找到最大索引
        int max = 0, index = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] > max) {
                max = arr[i];
                index = i;
            }
        }

        // 第一次翻转，将最大饼放到最上面
        reverse(arr.begin(), arr.begin() + index + 1);
        res.emplace_back(index + 1);

        // 第二次翻转，将最大饼放到最下面
        reverse(arr.begin(), arr.begin() + n);
        res.emplace_back(n);

        // 调用递归函数
        sort(arr, n - 1);
    }
};

int main() {

    vector<int> arr{3, 2, 4, 1};
    vector<int> res = Solution().pancakeSort(arr);
    for (auto r : res) {
        cout << r << endl;
    }
    return 0;
}


