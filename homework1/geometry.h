#include <cmath>
//h->cpp
class Point{
    public:
        Point()
        : x(0), y(0){
        }
        //default arguments
        Point(int x_,int y_)
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
        //space
        int getX()const{
            return x;
        }
        int getY()const{
            return y;
        }
    //space
    private:
        int x,y;
};
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
            //dif sizes kill ur program
            sz = other.sz;
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
            int x,y,x1,y1;
            for(int i = 1;i < this->getN();i++){
                //why do u need method when u have pnt
                //dist between Points many times
                x = this->getPoint(i).getX();
                x1 = this->getPoint(i - 1).getX();
                y = this->getPoint(i).getY();
                y1 = this->getPoint(i - 1).getY();
                res += sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
            }
            if(getClosed()) {
                x = this->getPoint(0).getX();
                x1 = this->getPoint(this->getN() - 1).getX();
                y = this->getPoint(0).getY();
                y1 = this->getPoint(this->getN() - 1).getY();
                res += sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
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
        		//it's weird
        		if(pnt){
       	    		delete[] pnt;
       	    		pnt = 0;
        		}
    	}
    private:
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
        	//no herons, something else
            double ab = (a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY());
            ab = sqrt(ab);
            double bc = (c.getX() - b.getX()) * (c.getX() - b.getX()) + (c.getY() - b.getY()) * (c.getY() - b.getY());
            bc = sqrt(bc);
            double ca = (a.getX() - c.getX()) * (a.getX() - c.getX()) + (a.getY() - c.getY()) * (a.getY() - c.getY());
            ca = sqrt(ca);
            double p = (ab + bc + ca) / 2;
            return sqrt(p * (p - ab) * (p - bc) * (p - ca));
        }
};
class Triangle: public Polygon{
    public:
        Triangle(int sz, Point *pnt) : Polygon(sz, pnt) {
        }
        bool hasRightAngle()const{
        	//protected for points
            Point a = this->getPoint(0);
            Point b = this->getPoint(1);
            Point c = this->getPoint(2);
            //dist ^ 2
            int ab = (b.getX() - a.getX()) * (b.getX() - a.getX()) + ((b.getY() - a.getY()) * (b.getY() - a.getY()));
            int bc = (b.getX() - c.getX()) * (b.getX() - c.getX()) + ((b.getY() - c.getY()) * (b.getY() - c.getY()));
            int ca = (c.getX() - a.getX()) * (c.getX() - a.getX()) + ((c.getY() - a.getY()) * (c.getY() - a.getY()));
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
            int S = this->area();
            Point a = this->getPoint(1);
            Point b = this->getPoint(2);
            Point c = this->getPoint(0);
            Point d = this->getPoint(3);
            //foundation
            int fund1 = (a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() -b.getY());
            fund1 = sqrt(fund1);
            int fund2 = (c.getX() - d.getX()) * (c.getX() - d.getX()) + (c.getY() - d.getY()) * (c.getY() -d.getY());
            fund2 = sqrt(fund2);
            return 2 * S / (fund1 + fund2);
        }
        ~Trapezoid(){
    	}
};

//area and perimeter
class RegularPolygon: public Polygon{
    public:
        RegularPolygon(int sz,Point* pnt): Polygon(sz,pnt){
        }
        ~RegularPolygon(){
        	
    	}
};

