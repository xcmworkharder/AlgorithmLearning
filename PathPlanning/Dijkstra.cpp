//
// Created by xcmworkharder on 2020-11-05 下午8:04.
//
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvii = vector<vii>;

vector<int> parent;

// 导入数据文件并创建邻接矩阵
vvii loadAndMakeTree(const string& filename) {
    ifstream readData(filename);
    if (readData) {
        string buf;
        getline(readData, buf);
        istringstream oneLine(buf);
        int n;
        oneLine >> n;
        vvii G(n);
        while (getline(readData, buf)) {
            oneLine = istringstream(buf);
            int v1, v2, d;
            oneLine >> v1 >> v2 >> d;
            cout << v1 << " " << v2 << " " << d << endl;
            G[v1].push_back(ii(v2, d));
        }
        return G;
    }
    return vvii();
}

// 初始化节点的邻接矩阵
vvii makeTree(int n, int e) {
    vvii G(n);
    for (int i = 0; i < e; ++i) {
        int v1, v2, d;
        cin >> v1 >> v2 >> d;
        G[v1].push_back(ii(v2, d));
    }
    return G;
}

int dijkstra(const vvii& G, int s, int t) {
    int n = G.size();
    vi D(n, INT_MAX);
    priority_queue<ii, vector<ii>, greater<ii>> Q;
    D[s] = 0;
    Q.push(ii(0, s));
    parent[0] = 0;
    while (!Q.empty()) {
        ii p = Q.top();
        Q.pop();
        int d = p.first, v = p.second;
        if (v == t) {
            break;
        }
        // 如果队列中的元素值大于松弛的值，则直接剔除
        if (D[v] < d) {
            continue;
        }
        for (int i = 0; i < G[v].size(); ++i) {
            int v2 = G[v][i].first, d = G[v][i].second;
            if (D[v2] > D[v] + d) {
                parent[v2] = v;
                D[v2] = D[v] + d;
                Q.push(ii(D[v2], v2));
            }
        }
    }
    return D[t] == INT_MAX ? -1 : D[t];
}

int main() {

    //cout << dijkstra(makeTree(6, 7), 0, 5) << endl;
    vvii G = loadAndMakeTree("graph.txt");
    if (G.size() == 0) {
        cout << "there is no data" << endl;
        return 0;
    }
    cout << "readData successful!" << "dataSize: " << G.size() << endl;
    parent = vector<int>(G.size(), -1);
    cout << "shortest path is: " << dijkstra(G, 0, 5) << endl;
    // 获取最短路径
    vector<int> path;
    int target = 5;
    path.push_back(target);
    while (parent[target] != 0) {
        path.push_back(parent[target]);
        target = parent[target];
    }
    path.push_back(0);
    reverse(path.begin(), path.end());
    for (auto& p : path) {
        cout << p;
        if (p != path[path.size() - 1]) {
            cout << " -> ";
        }
    }
    cout << endl;
    return 0;
}
