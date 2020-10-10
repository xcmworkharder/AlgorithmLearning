//
// Created by xcmworkharder on 2020-10-03 下午7:52.
//
#include <iostream>
#include <vector>

using namespace std;

// 暴力查找子串
int searchSubstr(string pat, string txt) {
    int m = pat.size();
    int n = txt.size();

    for (int i = 0; i < n - m; ++i) {
        int j;
        for(j = 0; j < m; ++j) {
            if (pat[j] != txt[i + j]) {
                break;
            }
        }
        if (j == m) {
            return i;
        }
    }
    return -1;
}

class KMP {
private:
    vector<vector<int>> dp; // dp[i][char] = next 当pat中第i个字符遇到字符char是转移到哪个pat中哪个字符
    string pat;

public:
    KMP(string _pat) : pat{_pat} {

        int M  = pat.size();
        dp = vector<vector<int>>(M, vector<int>(256, 0));
        // 遇到pat的第一个字符时从0状态转到1状态
        dp[0][pat[0]] = 1;
        // 定义影子状态X, 初始为0
        int X = 0;
        // 当前状态j从1开始
        for (int j = 1; j < M; j++) {
            for (int c = 0; c < 256; c++) {
                dp[j][c] = dp[X][c];
            }
            dp[j][pat[j]] = j + 1;
            X = dp[X][pat[j]];
        }
    }

    int search(string txt) {
        int N = txt.size();
        int M = pat.size();
        int j = 0;
        for (int i = 0; i < N; ++i) {
            j = dp[j][txt[i]];
            if (j == M) {
                return i - M + 1;
            }
        }
        return -1;
    }
};

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {

    }
};

void getMin(TreeNode*& root) {
    while (root->left) {
        root = root->left;
    }
    cout << root->val << endl;
}

int main() {

    cout << char('a' | ' ') << endl;
    cout << char('A' | ' ') << endl;

    cout << char('b' & '_') << endl;
    cout << char('B' & '_') << endl;

    cout << char('d' ^ ' ') << endl;
    cout << char('D' ^ ' ') << endl;

    cout << bool((-1) ^ (2)) << endl;

//    TreeNode* root = new TreeNode(1);
//    TreeNode* left = new TreeNode(2);
//    TreeNode* right = new TreeNode(3);
//    root->left = left;
//    root->right = right;
//
//    cout << root->val << endl;
//    getMin(root);
//    cout << root->val << endl;

    // 使用KMP算法
//    KMP kmp("abab");
//    cout << kmp.search("ddababcde") << endl;
    // 暴力查找子串方法
    //cout << searchSubstr("abc", "sddfabcde") << endl;

    return 0;
}



