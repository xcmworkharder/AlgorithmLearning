#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <climits>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
 
class CPoint {
public:
    CPoint(int x, int y) 
        : X(x), Y(y), G(0), H(0), F(0), m_parentPoint(nullptr) { }
    ~CPoint() { 
    }
    
    int X, Y, G, H, F;
    CPoint* m_parentPoint;
    void calF() {
        F = G + H; // 如果H = 0， 退化为dijkstra算法
    }
};

class AStar {
private:
    vector<vector<int>> m_array;
    static const int STEP = 10;
    static const int OBLIQUE = 14;
    
    list<CPoint*> m_openList;
    list<CPoint*> m_closeList;
    
public:
    AStar(vector<vector<int>>& array) {
	m_array = array;
    }
    
    ~AStar() {}
    
    list<CPoint*> getCloseList() const {
        return m_closeList;
    }
    
    list<CPoint*> getOpenList() const {
        return m_openList;
    }
    
    int calcG(CPoint* start, CPoint* point) {
	int G = (abs(point->X - start->X) + abs(point->Y - start->Y)) == 2 ? STEP : OBLIQUE;
	int parentG = point->m_parentPoint != nullptr ? point->m_parentPoint->G : 0;
	return G + parentG;
    }
    
    int calcH(CPoint* end, CPoint* point) {
	int step = abs(point->X - end->X) + abs(point->Y - end->Y);	// 曼哈顿距离
	return STEP * step;
    }
    
    CPoint* getMinFPoint() {
        if (!m_openList.empty()) {
	    auto resPoint = m_openList.front();
	    for (auto& point : m_openList) {
	        if (point->F < resPoint->F) {
		    resPoint = point;
		}
	    }
	    return resPoint;
	}
	return nullptr;
    }
    
    // 搜索路径
    CPoint* findPath(CPoint* start, CPoint* end, bool isIgnoreCorner) {
	m_openList.push_back(start);
	while (!m_openList.empty()) {
	    auto curPoint = getMinFPoint();
	    m_openList.remove(curPoint);
	    m_closeList.push_back(curPoint);
	    
	    auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
	    for (auto& target : surroundPoints) {
		if (!isInList(m_openList, target)) {
		    target->m_parentPoint = curPoint;
		    target->G = calcG(curPoint, target);
		    target->H = calcH(target, end);
		    target->calF();
		    m_openList.push_back(target);
		} else {
		    int tmpG = calcG(curPoint, target);
		    if (tmpG < target->G) {
			target->m_parentPoint = curPoint;
			target->G = tmpG;
			target->calF();
		    }
		}
		// 判断目标点是否存入判断列表
		CPoint* resPoint = isInList(m_openList, end);
		if (resPoint) {
		    return resPoint;
		}
	    }
	}
	return nullptr;
    }
    
    list<CPoint*> getPath(CPoint* start, CPoint* end, bool isIgnoreCorner) {
	CPoint* resPoint = findPath(start, end, isIgnoreCorner);
	list<CPoint*> pathList;
	while (resPoint) {
	    pathList.push_front(resPoint);
	    resPoint = resPoint->m_parentPoint;
	}
	
	m_openList.clear();
	m_closeList.clear();
	
	return pathList;
    }
    
    // 使用指针的空与否来判断
    CPoint* isInList(list<CPoint*>& list, const CPoint* point) const {
	for (auto& p : list) {
	    if (p->X == point->X && p->Y == point->Y) {
		return p;
	    }
	}
	return nullptr;
    }
    
    bool canReach(const CPoint* point, const CPoint* target, bool isIgnoreCorner) {
	// 如果目标点与当前点重合，超出地图，是障碍物，或者在关闭列表中，则false:表示无法到达
	if (target->X < 0 || target->X > m_array.size() - 1 
	    || target->Y < 0 || target->Y > m_array[0].size() - 1
	    || m_array[target->X][target->Y] == 1 
	    || target->X == point->X && target->Y == point->Y 
	    || isInList(m_closeList, target)) {
	    return false;
	} else {
	    if (abs(point->X - target->X) + abs(point->Y - target->Y) == 1) {
		return true;
	    } else {
		// 如果目标位置与当前位置的横向和纵向都可通过，则对角可通过          
		if (m_array[point->X][target->Y] == 0 && m_array[target->X][point->Y] == 0) {
		    return true;
		} else { // 否则，就会有一处挨着墙体，如果忽略墙体影响，则返回真，如果考虑墙体则返回假
		    return isIgnoreCorner;
		}
	    }
	}
	return true;
    }
    
    vector<CPoint*> getSurroundPoints(const CPoint* point, bool isIgnoreCorner) {
	vector<CPoint*> surroundPoints;
	for (int x = point->X - 1; x <= point->X + 1; x++) {
	    for (int y = point->Y - 1; y <= point->Y + 1; y++) {
		CPoint* target = new CPoint(x, y);
		if (canReach(point, target, isIgnoreCorner)) {
		    surroundPoints.push_back(target);
		}
	    }
	}
	return surroundPoints;
    }
};

int main() {
    int start_point_x = 1;
    int start_point_y = 1;
    int goal_point_x = 2;
    int goal_point_y = 10;
    vector<vector<int>> array{ //  0  1  2  3  4  5  6  7  8  9 10  11    
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},// 0 
        { 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},// 1
	{ 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},// 2
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},// 3
	{ 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},// 4
	{ 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},// 5
	{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},// 6
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} // 7
    };
	
    AStar aStar = AStar(array);
    if (array[start_point_x][start_point_y] || array[goal_point_x][goal_point_y]) {
        cout << "start point or goal point set error!!!" << endl;
        return 0;
    }
    CPoint* start = new CPoint(start_point_x, start_point_y);
    CPoint* end = new CPoint(goal_point_x, goal_point_y);
    CPoint* point = aStar.findPath(start, end, true);
 
    Rect rect;
    Point left_up, right_bottom; // opencv中的Point
    
    Mat img(600, 600, CV_8UC3, Scalar(255, 255, 255));
    namedWindow("A* Test");
    
    while (point != nullptr) {
        left_up.x = point->Y * 50;  //存储数组的列(point->Y)对应矩形的x轴，一个格大小50像素
        left_up.y = point->X * 50;  
        right_bottom.x = left_up.x + 50;  
        right_bottom.y = left_up.y + 50;
        rectangle(img, left_up, right_bottom, Scalar(0, 255, 255), CV_FILLED, 8, 0); //path yellow(full)
        cout << "(" << point->X << "," << point->Y << ");" << endl;
        point = point->m_parentPoint;     
    }
 
    for(int i = 0;i < 8;i++) {
        for(int j = 0;j < 12;j++) {   
            left_up.x = j * 50; //存储数组的列(j)对应矩形的x轴
            left_up.y = i * 50;  
            right_bottom.x = left_up.x + 50;  
            right_bottom.y = left_up.y + 50;
            if(array[i][j]) {
                rectangle(img, left_up, right_bottom, Scalar(0,0,255), CV_FILLED, 8, 0);//obstacles red
            } else {
                if(i == start_point_x && j == start_point_y)
                    rectangle(img, left_up, right_bottom, Scalar(255,0,0), CV_FILLED, 8, 0);//start point blue(full)
                else if(i == goal_point_x && j == goal_point_y)
                    rectangle(img, left_up, right_bottom, Scalar(0,0,0), CV_FILLED, 8, 0);//goal point black(full)
                else
                    rectangle(img, left_up, right_bottom, Scalar(0,255,0), 2, 8, 0);//free white content,green edge
            }    
        }
    }
    
    
    // 打印opened 和 closed的列表,可以看出使用dijkstra和a*的算法复杂的区别
    cout << aStar.getCloseList().size() << endl;
    for (auto& c : aStar.getCloseList()) {
        left_up.x = c->Y * 50;  //存储数组的列(point->Y)对应矩形的x轴，一个格大小50像素
        left_up.y = c->X * 50;  
        right_bottom.x = left_up.x + 50;  
        right_bottom.y = left_up.y + 50;
        rectangle(img, left_up, right_bottom, Scalar(0, 255, 0), CV_FILLED, 8, 0); // green
    }
    cout << aStar.getOpenList().size() << endl;
    for (auto& c : aStar.getOpenList()) {
        left_up.x = c->Y * 50;  //存储数组的列(point->Y)对应矩形的x轴，一个格大小50像素
        left_up.y = c->X * 50;  
        right_bottom.x = left_up.x + 50;  
        right_bottom.y = left_up.y + 50;
        rectangle(img, left_up, right_bottom, Scalar(0, 255, 0), CV_FILLED, 8, 0); // green
    }

    imshow("A* Test", img);   //窗口中显示图像 
    waitKey(0);
    return 0;
}
