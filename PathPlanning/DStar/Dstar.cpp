#include "Dstar.h"
#include <stdio.h>

// 启动OpenGL
#define USE_OPEN_GL

#ifdef USE_OPEN_GL
#ifdef MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#endif


Dstar::Dstar() { 
    maxSteps = 80000;  // node expansions before we give up
    C1       = 1;      // cost of an unseen cell
}

float Dstar::keyHashCode(state u) {
  return (float)(u.k.first + 1193 * u.k.second);
}

bool Dstar::isValid(state u) {
    ds_oh::iterator cur = openHash.find(u);
    if (cur == openHash.end()) 
	return false;
    if (!close(keyHashCode(u), cur->second)) 
	return false;
    return true; 
}

list<state> Dstar::getPath() {
  return path;
}

bool Dstar::occupied(state u) { 
    ds_ch::iterator cur = cellHash.find(u);
  
    if (cur == cellHash.end()) 
	return false;
    return (cur->second.cost < 0);
}

void Dstar::init(int sX, int sY, int gX, int gY) {
    cellHash.clear();
    path.clear();
    openHash.clear();
    while(!openList.empty()) 
	openList.pop();

    k_m = 0;
  
    s_start.x = sX;
    s_start.y = sY;
    s_goal.x  = gX;
    s_goal.y  = gY;

    cellInfo tmp;
    tmp.g = tmp.rhs =  0;
    tmp.cost = C1;

    cellHash[s_goal] = tmp;

    tmp.g = tmp.rhs = heuristic(s_start,s_goal);
    tmp.cost = C1;
    cellHash[s_start] = tmp;
    s_start = calculateKey(s_start);

    s_last = s_start;
}

void Dstar::makeNewCell(state u) {
    if (cellHash.find(u) != cellHash.end()) return;

    cellInfo tmp;
    tmp.g       = tmp.rhs = heuristic(u,s_goal);
    tmp.cost    = C1;
    cellHash[u] = tmp; 
}

double Dstar::getG(state u) {

    if (cellHash.find(u) == cellHash.end()) 
      return heuristic(u,s_goal);
    return cellHash[u].g;
}

double Dstar::getRHS(state u) {
    if (u == s_goal) 
	return 0;  

    if (cellHash.find(u) == cellHash.end()) 
      return heuristic(u,s_goal);
    return cellHash[u].rhs;
}

void Dstar::setG(state u, double g) {
    makeNewCell(u);  
    cellHash[u].g = g; 
}

double Dstar::setRHS(state u, double rhs) {
    makeNewCell(u);
    cellHash[u].rhs = rhs;
}

double Dstar::eightCondist(state a, state b) {
    double temp;
    double min = abs(a.x - b.x);
    double max = abs(a.y - b.y);
    if (min > max) {
      double temp = min;
      min = max;
      max = temp;
    }
    return ((M_SQRT2-1.0) * min + max);
}

int Dstar::computeShortestPath() {
  
    list<state> s;
    list<state>::iterator i;

    if (openList.empty())
	return 1;

    int k=0;
    while ((!openList.empty()) && 
          (openList.top() < (s_start = calculateKey(s_start))) || 
          (getRHS(s_start) != getG(s_start))) {

    if (k++ > maxSteps) {
        fprintf(stderr, "At maxsteps\n");
        return -1;
    }


    state u;

    bool test = (getRHS(s_start) != getG(s_start));
    
    // lazy remove
    while (1) { 
        if (openList.empty()) 
	    return 1;
        u = openList.top();
        openList.pop();
      
        if (!isValid(u)) 
	    continue;
        if (!(u < s_start) && (!test))
	    return 2;
        break;
    }
    
    ds_oh::iterator cur = openHash.find(u);
    openHash.erase(cur);

    state k_old = u;

    if (k_old < calculateKey(u)) { // u is out of date
        insert(u);
    } else if (getG(u) > getRHS(u)) { // needs update (got better)
        setG(u,getRHS(u));
        getPred(u,s);
        for (i = s.begin(); i != s.end(); i++) {
            updateVertex(*i);
        }
    } else {   // g <= rhs, state has got worse
        setG(u,INFINITY);
        getPred(u,s);
        for (i = s.begin(); i != s.end(); i++) {
          updateVertex(*i);
        }
        updateVertex(u);
      }
    }
    return 0;
}

bool Dstar::close(double x, double y) { 
    if (isinf(x) && isinf(y))
        return true;
    return (fabs(x - y) < 0.00001); 
}

void Dstar::updateVertex(state u) {
    list<state> s;
    list<state>::iterator i;
 
    if (u != s_goal) {
      getSucc(u,s);
      double tmp = INFINITY;
      double tmp2;

      for (i = s.begin();i != s.end(); i++) {
          tmp2 = getG(*i) + cost(u, *i);
          if (tmp2 < tmp)
	      tmp = tmp2;
      }
      if (!close(getRHS(u), tmp))
	  setRHS(u,tmp);
    }

    if (!close(getG(u), getRHS(u))) 
	insert(u);
}

void Dstar::insert(state u) {
    ds_oh::iterator cur;
    float csum;

    u    = calculateKey(u);
    cur  = openHash.find(u);
    csum = keyHashCode(u);
  
    openHash[u] = csum;
    openList.push(u);
} 

void Dstar::remove(state u) { 
    ds_oh::iterator cur = openHash.find(u);
    if (cur == openHash.end())
	return;
    openHash.erase(cur);
}

double Dstar::trueDist(state a, state b) {
    float x = a.x - b.x;
    float y = a.y - b.y;
    return sqrt(x * x + y * y); 
}

double Dstar::heuristic(state a, state b) {
    return eightCondist(a,b)*C1;
}

state Dstar::calculateKey(state u) {  
    double g = getG(u);
    double rhs = getRHS(u);
    //double val = fmin(g,rhs);
    if (g > rhs) {
        u.k.first  = rhs + 4 * heuristic(u, s_start) + k_m;
        u.k.second = rhs;	
    } else {
	u.k.first  = g + heuristic(u,s_start) + k_m;
	u.k.second = g;
    }
    return u;
}

double Dstar::cost(state a, state b) {
    int xd = abs(a.x - b.x);
    int yd = abs(a.y - b.y);
    double scale = 1;

    if (xd + yd > 1) 
	scale = M_SQRT2;

    if (cellHash.count(a) == 0) 
	return scale * C1;
    return scale*cellHash[a].cost;
}

void Dstar::updateCell(int x, int y, double val) {
    state u;
  
    u.x = x;
    u.y = y;

    if ((u == s_start) || (u == s_goal)) 
	return;

    makeNewCell(u); 
    cellHash[u].cost = val;

    updateVertex(u);
}

void Dstar::getSucc(state u, list<state>& s) { 
    s.clear();
    u.k.first  = -1;
    u.k.second = -1;

    if (occupied(u))
	return;

    u.x += 1;
    s.push_front(u);
    u.y += 1;
    s.push_front(u);
    u.x -= 1;
    s.push_front(u);
    u.x -= 1;
    s.push_front(u);
    u.y -= 1;
    s.push_front(u);
    u.y -= 1;
    s.push_front(u);
    u.x += 1;
    s.push_front(u);
    u.x += 1;
    s.push_front(u);
}

void Dstar::getPred(state u, list<state>& s) {
  
    s.clear();
    u.k.first  = -1;
    u.k.second = -1;

    u.x += 1;
    if (!occupied(u)) s.push_front(u);
    u.y += 1;
    if (!occupied(u)) s.push_front(u);
    u.x -= 1;
    if (!occupied(u)) s.push_front(u);
    u.x -= 1;
    if (!occupied(u)) s.push_front(u);
    u.y -= 1;
    if (!occupied(u)) s.push_front(u);
    u.y -= 1;
    if (!occupied(u)) s.push_front(u);
    u.x += 1;
    if (!occupied(u)) s.push_front(u);
    u.x += 1;
    if (!occupied(u)) s.push_front(u);
  
}

void Dstar::updateStart(int x, int y) {

    s_start.x = x;
    s_start.y = y;
    
    k_m += heuristic(s_last, s_start);

    s_start = calculateKey(s_start);
    s_last  = s_start;
  
}

void Dstar::updateGoal(int x, int y) {
    list< pair<ipoint2, double> > toAdd;
    pair<ipoint2, double> tp;
    
    ds_ch::iterator i;
    list< pair<ipoint2, double> >::iterator kk;
    
    for (i = cellHash.begin(); i != cellHash.end(); i++) {
	if (!close(i->second.cost, C1)) {
	    tp.first.x = i->first.x;
	    tp.first.y = i->first.y;
	    tp.second = i->second.cost;
	    toAdd.push_back(tp);
	}
    }

    cellHash.clear();
    openHash.clear();

    while(!openList.empty())
	openList.pop();
    
    k_m = 0;
    
    s_goal.x  = x;
    s_goal.y  = y;

    cellInfo tmp;
    tmp.g = tmp.rhs =  0;
    tmp.cost = C1;

    cellHash[s_goal] = tmp;

    tmp.g = tmp.rhs = heuristic(s_start, s_goal);
    tmp.cost = C1;
    cellHash[s_start] = tmp;
    s_start = calculateKey(s_start);

    s_last = s_start;    

    for (kk = toAdd.begin(); kk != toAdd.end(); kk++) {
	updateCell(kk->first.x, kk->first.y, kk->second);
    }
}

bool Dstar::replan() {

    path.clear();

    int res = computeShortestPath();
    //printf("res: %d ols: %d ohs: %d tk: [%f %f] sk: [%f %f] sgr: (%f,%f)\n",res,openList.size(),openHash.size(),openList.top().k.first,openList.top().k.second, s_start.k.first, s_start.k.second,getRHS(s_start),getG(s_start));
    if (res < 0) {
	fprintf(stderr, "NO PATH TO GOAL\n");
	return false;
    }
    list<state> n;
    list<state>::iterator i;

    state cur = s_start; 

    if (isinf(getG(s_start))) {
	fprintf(stderr, "NO PATH TO GOAL\n");
	return false;
    }
    
    while(cur != s_goal) {
	path.push_back(cur);
	getSucc(cur, n);

	if (n.empty()) {
	fprintf(stderr, "NO PATH TO GOAL\n");
	return false;
	}

	double cmin = INFINITY;
	double tmin;
	state smin;
	
	for (i=n.begin(); i!=n.end(); i++) {
    
	//if (occupied(*i)) continue;
	double val  = cost(cur,*i);
	double val2 = trueDist(*i,s_goal) + trueDist(s_start,*i); // (Euclidean) cost to goal + cost to pred
	val += getG(*i);

	if (close(val,cmin)) {
	    if (tmin > val2) {
	    tmin = val2;
	    cmin = val;
	    smin = *i;
	    }
	} else if (val < cmin) {
	    tmin = val2;
	    cmin = val;
	    smin = *i;
	}
    }
    n.clear();
    cur = smin;
    }
    path.push_back(s_goal);
    return true;
}

#ifdef USE_OPEN_GL

void Dstar::draw() {
    ds_ch::iterator iter;
    ds_oh::iterator iter1;
    state t;

    list<state>::iterator iter2;
    
    glBegin(GL_QUADS);
    for(iter=cellHash.begin(); iter != cellHash.end(); iter++) {
	if (iter->second.cost == 1) glColor3f(0,1,0);
	else if (iter->second.cost < 0 ) glColor3f(1,0,0);
	else glColor3f(0,0,1);
	drawCell(iter->first,0.45);
    }

    glColor3f(1,1,0);
    drawCell(s_start,0.45);
    glColor3f(1,0,1);
    drawCell(s_goal,0.45);

    for(iter1=openHash.begin(); iter1 != openHash.end(); iter1++) {
	glColor3f(0.4,0,0.8);
	drawCell(iter1->first, 0.2);
    }
    
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.6, 0.1, 0.4);

    for(iter2=path.begin(); iter2 != path.end(); iter2++) {
	glVertex3f(iter2->x, iter2->y, 0.2);
    }
    glEnd();
}

void Dstar::drawCell(state s, float size) {
    float x = s.x;
    float y = s.y;
    
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size);
    glVertex2f(x - size, y + size);
}

#else
void Dstar::draw() {}
void Dstar::drawCell(state s, float z) {}
#endif
