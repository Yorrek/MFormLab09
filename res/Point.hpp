#ifndef Point_hpp
#define Point_hpp


class Point {

public:
    float m_x, m_y;

    Point(float x, float y);

    Point();

    ~Point();

    friend Point operator+(Point p, Point q);

    friend Point operator-(Point p, Point q);

    friend Point operator*(Point p, Point q);

    friend Point operator/(Point p, Point q);

    void setX(float x) { m_x = x; }

    void setY(float y) { m_y = y; }

};

#endif
