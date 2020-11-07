//
// Created by xcmworkharder on 2020-11-05 下午8:04.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int F, H;
    Node(int f, int h) : F(f), H(h) {

    }
    bool operator == (const Node& b) {
        return F == b.F && H == b.H;
    }
};

int main(int argc, char** argv) {

    vector<Node> arr{Node(5, 3), Node(2, 4), Node(3, 2), Node(3,2)};
    cout << (find_if(arr.begin(), arr.end(), [](const Node& a) {return a.F == 3 && a.H == 2;}) != arr.end()) << endl;
    //cout << (*min_element(arr.begin(), arr.end(), 
    //                     [](const Node& a, const Node& b) {
    //                            return a.F < b.F; }
    //                            )).F << endl;
    //
    //cout << arr.size() << endl;
    //arr.erase(remove(arr.begin(), arr.end(), Node(3, 2)), arr.end());
    //cout << arr.size() << endl;

    return 0;
}
