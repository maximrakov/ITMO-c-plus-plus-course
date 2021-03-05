#ifndef GEOMETRY_H
#define GEOMETRY_H

class Point{
    public:
        Point(int x_ = 0,int y_ = 0);
        Point(Point const &pnt);
        Point& operator=(const  Point& other);
        
        int getX()const;
        int getY()const;
        
    private:
        int x,y;
};

class PolygonalChain{
    public:
        PolygonalChain(int sz_, Point *pnt_);
        PolygonalChain(PolygonalChain const &other);
        
        PolygonalChain& operator=(const PolygonalChain& other);
        
        int getN()const;
        Point getPoint(int ind)const;
        
        int perimeter()const;
        void setClosed(bool val);
        bool getClosed() const;
        
        ~PolygonalChain();
    	
    protected:
        int sz;
        Point *pnt;
        bool closed;
};

class ClosedPolygonalChain: public PolygonalChain{
    public:
        ClosedPolygonalChain(int sz, Point *pnt);
        
    	~ClosedPolygonalChain();
};

class Polygon: public ClosedPolygonalChain{
    public:
        Polygon(int sz, Point *pnt);
        
        double area()const;
        
        ~Polygon();
        
    private:
        double s_triangle(Point a,Point b, Point c)const;
};

class Triangle: public Polygon{
    public:
        Triangle(int sz, Point *pnt);
        
        bool hasRightAngle()const;
        
        ~Triangle();
        
};

class Trapezoid: public Polygon{
    public:
        Trapezoid(int sz, Point *pnt);
        
        int height()const;
        
        ~Trapezoid();
};

class RegularPolygon: public Polygon{
    public:
        RegularPolygon(int sz,Point* pnt);
        
	int perimeter()const;
        int area()const;
	
    	~RegularPolygon();
};

int dist(const Point& a, const Point& b);

int dist2(const Point& a, const Point& b);

#endif
