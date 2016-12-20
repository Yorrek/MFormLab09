//
// Created by Nico Lassen on 18.12.16.
//

#ifndef LABOR8_Poly_H
#define LABOR8_Poly_H

#include <stdio.h>
#include <vector>
#include "Point.hpp"

using namespace std;

class Poly {

public:
    Poly();
    ~Poly();
    Point pTmp;
    vector <Point> points;
    vector <Point> cubicPoints;
    vector <Point> interpolPoints;
    void addPoint(Point a);
    void subdivideSplines(Poly *poly);
    void interpolCubic(Poly *interpol);
};


#endif //LABOR8_Poly_H
