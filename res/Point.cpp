#include "Point.hpp"

Point::Point() {}

Point::Point( float x, float y){
    this->m_x = x;
    this->m_y = y;
}

Point::~Point() {}

Point operator+( Point p, Point q){
    return Point(p.m_x + q.m_x, p.m_y + q.m_y);
}

Point operator-( Point p, Point q){
    return Point(p.m_x - q.m_x, p.m_y - q.m_y);
}

Point operator*( Point p, Point q){
    return Point(p.m_x * q.m_x, p.m_y * q.m_y);
}

Point operator/( Point p, Point q){
    return Point(p.m_x / q.m_x, p.m_y / q.m_y);
}
