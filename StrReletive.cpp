//
// Created by xcmworkharder on 2020-10-13 上午8:58.
//
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int atoi(const char *str) {
        if (*str == '\0') {
            return 0;
        }
        while (*str == ' ') {
            str++;
        }
        int flag = 1;
        if (*str == '-') {
            flag = -1;
            str++;
        }
        long long ret = 0;
        while (isdigit(*str)) {
            ret = 10 * ret + (*str) - '0';
            str++;
            if (flag * ret > INT_MAX) {
                return INT_MAX;
            }
            if (flag * ret < INT_MIN) {
                return INT_MIN;
            }
        }
        return flag * ret;
    }
};

int main() {

    string numStr = "-13223423aa432432434";
    cout << Solution().atoi(numStr.c_str()) << endl;
    return 0;
}

