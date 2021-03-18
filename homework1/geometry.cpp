#include "geometry.h"
#include <cmath>

using namespace std;
Point :: Point(int x_, int y_)
: x(x_), y(y_) {
}

Point :: Point(const Point& pnt)
: x(pnt.x), y(pnt.y) {
}

Point& Point :: operator=(const Point& other) {
    if (&other == this){
        return *this;
    }
	
    x = other.x;	
    y = other.y;
	
    return *this;
}

int Point :: getX()const {
    return x;
}

int Point :: getY()const {
    return y;
}


//fixed copy-paste
double dist2(const Point& a, const Point& b) {
    return ((a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY()));
}

//fixed int??????
double dist(const Point& a, const Point& b) {
    return sqrt(dist2(a, b));
}

PolygonalChain :: PolygonalChain(int sz_, Point *pnt_)
:sz(sz_) {
    pnt = new Point[sz_];
    
    for (int i = 0; i < sz_; i++){
        pnt[i] = pnt_[i];
    }
    
    closed = 0;
}

PolygonalChain :: PolygonalChain(const PolygonalChain& other) {
    sz = other.sz;
	
    pnt = new Point[sz];
    
    for (int i = 0; i < sz; i++){
        pnt[i] = other.pnt[i];
    }
}

PolygonalChain& PolygonalChain :: operator=(const PolygonalChain& other) {
    if (&other == this) {
        return *this;
    }
    
    sz = other.sz;
    delete[] pnt;
    pnt = new Point[sz];
    
    for (int i = 0; i < sz; i++) {
        pnt[i] = other.pnt[i];
    }
	
    return *this;
}

int  PolygonalChain :: getN() const {
    return sz;
}

Point PolygonalChain :: getPoint(int ind) const {
    return pnt[ind];
}

double PolygonalChain :: perimeter() const {
    double res = 0;
	for (int i = 1; i < getN(); i++) {
        res += dist(pnt[i], pnt[i - 1]);
    }
    if (getClosed()) {
        res += dist(pnt[0], pnt[getN() - 1]);
    }
    
    return res;
}

void PolygonalChain :: setClosed(bool val) {
    closed = val;
}

bool PolygonalChain :: getClosed() const {
    return closed;
}

PolygonalChain :: ~PolygonalChain() {
    delete[] pnt;
}

ClosedPolygonalChain::ClosedPolygonalChain(int sz, Point *pnt):  PolygonalChain(sz, pnt) {
    setClosed(1);
}

ClosedPolygonalChain :: ~ClosedPolygonalChain() {
}

Polygon :: Polygon(int sz, Point *pnt) : ClosedPolygonalChain(sz, pnt) {
}
//fixed S P A C E S
double Polygon :: area() const {
    //fixed var with capital letter
    double s_polygon = 0;
    for (int i = 1; i < this->getN() - 1; i++) {
    	s_polygon += s_triangle(this->getPoint(0), this->getPoint(i), this->getPoint(i + 1));
    }
    
    return s_polygon;
}

Polygon :: ~Polygon() {
}

double Polygon :: s_triangle(Point a,Point b, Point c) const {
    return fabs((a.getX() - b.getX()) * (c.getY() - b.getY()) - (a.getY() - b.getY()) * (c.getX() - b.getX())) / 2.;
}

Triangle :: Triangle(int sz, Point *pnt) : Polygon(sz, pnt) {
}

bool Triangle :: hasRightAngle() const {
    Point a = pnt[0];
    Point b = pnt[1];
    Point c = pnt[2];
    
    int ab = dist2(a,b);
    int bc = dist2(b,c);
    int ca = dist2(c,a);
    
    if (ab + bc ==  ca) {
        return true;
    }
    if (bc +  ca == ab) {
        return true;
    }
    if (ca +  ab ==  bc) {
      return true;
    }
    
    return false;
}

Triangle :: ~Triangle() {
}

Trapezoid :: Trapezoid(int sz, Point *pnt): Polygon(sz, pnt) {
}

int Trapezoid :: height() const {
    //fixed too capital
    double trapezoid_area = area();
    
    Point a = pnt[1];
    Point b = pnt[2];
    Point c = pnt[0];
    Point d = pnt[3];
    
    double foundation1 = dist(a, b);
    double foundation2 = dist(c, d);
    
    return 2. * trapezoid_area / (foundation1 + foundation2);
}

Trapezoid :: ~Trapezoid() {
}

RegularPolygon :: RegularPolygon(int sz, Point* pnt): Polygon(sz, pnt) {
}

//fixed doubles??? i think
double RegularPolygon :: perimeter() const {
    return getN() * dist(pnt[0], pnt[1]);
}

double RegularPolygon :: area() const {
    //fixed const should static private; 3.14 is strange (u cound think pi = 3)
    return (getN() * dist(pnt[0], pnt[1]) * dist(pnt[0], pnt[1]))  / (4. * tan(M_PI / getN()));
}

RegularPolygon :: ~RegularPolygon() {
}
