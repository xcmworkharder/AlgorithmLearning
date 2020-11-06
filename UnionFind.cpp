//
// Created by xcmworkharder on 2020-10-13 上午9:37.
//
#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
private:
    int m_count;
    vector<int> m_parent;
    vector<int> m_size; // 记录树的重量

public:
    UnionFind(int n) : m_count(n) {
        m_parent.reserve(n);
        m_size.reserve(n);
        for (int i = 0; i < n; ++i) {
            m_parent.push_back(i);
            m_size.push_back(1);
        }
    }

    void Union(int p, int q) {
        int rootP = Find(p);
        int rootQ = Find(q);
        if (rootP == rootQ) {
            return;
        }
        // 小树接到大树上，树比较均衡
        if (m_size[rootP] > m_size[rootQ]) {
            m_parent[rootQ] = rootP;
            m_size[rootP] += m_size[rootQ];
        } else {
            m_parent[rootP] = rootQ;
            m_size[rootQ] += m_size[rootP];
        }
        m_count--;
    }

    int Find(int x) {
        while (m_parent[x] != x) {
            // 进行路径压缩
            m_parent[x] = m_parent[m_parent[x]];
            x = m_parent[x];
        }
        return x;
    }

    int count() const {
        return m_count;
    }

    bool connected(int p, int q) {
        return Find(p) == Find(q);
    }
};


int main() {

    return 0;
}

