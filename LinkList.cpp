//
// Created by xcmworkharder on 2020-10-13 上午8:41.
//
#include <iostream>

using namespace std;

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int _val) : val(_val), next(nullptr) {

    }
};

class Solution {
public:
    ListNode* reverse(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while (cur) {
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }

    void reverseAndPrint(ListNode* head) {
        if (!head) {
            return;
        }
        reverseAndPrint(head->next);
        cout << head->val << "->";
    }

    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while (cur) {
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        while (head) {
            cout << head->val << " " << pre->val << endl;
            if (head->val != pre->val) {
                return false;
            }
            pre = pre->next;
            head = head->next;
        }
        return true;
    }
};

int main() {

    ListNode* first = new ListNode(1);
    ListNode* second = new ListNode(2);
    ListNode* third = new ListNode(1);
    //ListNode* fourth = new ListNode(3);

    first->next = second;
    second->next = third;
    third->next = nullptr;
    //third->next = fourth;
    //fourth->next = nullptr;
    Solution().reverseAndPrint(first);

//    ListNode* newHead = Solution().reverse(first);
//    cout << newHead->val << "->" << newHead->next->val << endl;
//    cout << newHead->next->next->val << "->" << (newHead->next->next->next == nullptr ? 0 : 1) << endl;
    return 0;
}
