//
//  CubicBezier.hpp
//  Labor_7_1
//
//  Created by Felix Ohlsen on 14.12.16.
//  Copyright © 2016 Felix Ohlsen. All rights reserved.
//

/**TODO NOT DONE YET*/

#ifndef CubicBezier_hpp
#define CubicBezier_hpp

#include <stdio.h>
#include "Point.hpp"

class CubicBezier {
private:
    //Point m_points[4];

public:
    void setPoint(int i, Point a);
    CubicBezier();
    ~CubicBezier();
    Point points[4];
    Point subDivMatrix1[4];
    Point subDivMatrix2[4];
    void Subdivide(float t, CubicBezier *segment1, CubicBezier *segment2);
    void multipliyMatrix(float t, CubicBezier *aMatrix, CubicBezier *bMatrix);
};

#endif /* CubicBezier_hpp */




