#include <cmath>
class Point{
    public:
        Point(int x_ = 0,int y_ = 0)
        : x(x_), y(y_) {
        }
        Point(Point const &pnt)
        : x(pnt.x),y(pnt.y) {
        }
        Point& operator=(const  Point& other){
            if(&other == this){
                return *this;
            }
            x = other.x;
            y = other.y;
            return *this;
        }
        
        int getX()const{
            return x;
        }
        int getY()const{
            return y;
        }
        
    private:
        int x,y;
};
int dist(Point a, Point b){
  return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY()));
}
class PolygonalChain{
    public:
        PolygonalChain(int sz_, Point *pnt_)
        :sz(sz_)
        {
            pnt = new Point[sz_];
            for(int i = 0;i < sz_;i++){
                pnt[i] = pnt_[i];
            }
            closed = 0;
        }
        PolygonalChain(PolygonalChain const &other)
        {
        	sz = other.sz;
            pnt = new Point[sz];
            for(int i = 0;i < sz;i++){
              pnt[i] = other.pnt[i];
			}
        }
        PolygonalChain& operator=(const PolygonalChain& other){
            if(&other == this){
                return *this;
            }
            sz = other.sz;
			delete[] pnt;
            pnt = new Point[sz];
            for(int i = 0;i < sz;i++){
              pnt[i] = other.pnt[i];
			}
            return *this;
        }
        int getN()const{
            return sz;
        }
        Point getPoint(int ind)const{
            return pnt[ind];
        }
        int perimeter()const{
            int res = 0;
            for(int i = 1;i < getN();i++){
                res += dist(pnt[i],pnt[i - 1]);
            }
            if(getClosed()) {
                res += dist(pnt[0],pnt[getN() - 1]);
            }
            return res;
        }
        
        void setClosed(bool val) {
            closed = val;
        }
        bool getClosed() const {
            return closed;
        }
        
        ~PolygonalChain(){
			delete[] pnt;
			pnt = 0;
    	}
    	
    protected:
        int sz;
        Point *pnt;
        bool closed;
};
class ClosedPolygonalChain: public PolygonalChain{
    public:
        ClosedPolygonalChain(int sz, Point *pnt):  PolygonalChain(sz, pnt){
            setClosed(1);
        }
    ~ClosedPolygonalChain(){
    }
};
class Polygon: public ClosedPolygonalChain{
    public:
        Polygon(int sz, Point *pnt) : ClosedPolygonalChain(sz, pnt) {
        }
        double area()const{
            double S_Polygon = 0;
            for(int i = 1;i < this->getN() - 1;i++){
                S_Polygon += s_triangle(this->getPoint(0),this->getPoint(i),this->getPoint(i + 1));
            }
            return S_Polygon;
        }
        ~Polygon(){
    	}
    private:
        double s_triangle(Point a,Point b, Point c)const{
        	return abs((a.getX() - b.getX()) * (c.getY() - b.getY()) - (a.getY() - b.getY()) * (c.getX() - b.getX())) / 2;
        }
};
class Triangle: public Polygon{
    public:
        Triangle(int sz, Point *pnt) : Polygon(sz, pnt) {
        }
        bool hasRightAngle()const{
            Point a = pnt[0];
            Point b = pnt[1];
            Point c = pnt[2];
            int ab = dist(a,b) * dist(a,b);
            int bc = dist(b,c) * dist(b,c);
            int ca = dist(c,a) * dist(c,a);
            if(ab + bc ==  ca){
                return true;
            }
            if(bc +  ca == ab){
                return true;
            }
            if(ca +  ab ==  bc) {
              return true;
            }
            return false;
        }
        ~Triangle(){
    	}
        
};
class Trapezoid: public Polygon{
    public:
        Trapezoid(int sz, Point *pnt): Polygon(sz, pnt) {
        }
        int height()const{
            int S = area();
            Point a = pnt[1];
            Point b = pnt[2];
            Point c = pnt[0];
            Point d = pnt[3];
            int foundation1 = dist(a,b);
            int foundation2 = dist(c,d);
            return 2 * S / (foundation1 + foundation2);
        }
        ~Trapezoid(){
    	}
};
class RegularPolygon: public Polygon{
    public:
        RegularPolygon(int sz,Point* pnt): Polygon(sz,pnt){
        }
        int perimeter()const{
			return getN() * dist(pnt[0], pnt[1]);
		}
		int area()const{
		  return (getN() * dist(pnt[0], pnt[1]) * dist(pnt[0], pnt[1]))  / (4. * tan(3.14 / getN()));
		}
        ~RegularPolygon(){
    	}
};
