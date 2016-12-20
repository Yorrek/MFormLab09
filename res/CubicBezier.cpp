//
//  CubicBezier.cpp
//  Labor_7_1
//
//  Created by Felix Ohlsen on 14.12.16.
//  Copyright © 2016 Felix Ohlsen. All rights reserved.
//

/**TODO NOT DONE YET*/

#include "CubicBezier.hpp"
#include "iostream"

using namespace std;

CubicBezier::CubicBezier() {
}

CubicBezier::~CubicBezier() {
}

void CubicBezier::Subdivide(float t, CubicBezier *segment1, CubicBezier *segment2) {

    Point pTmp; //Temporärer speicher für einen Punkt
    Point p1; //Erster Punkt
    Point p2; //Zweiter Punkt

    segment1->points[0] = points[0]; //Erster Wert in Segment 1
    segment2->points[3] = points[3]; //Letzter Wert in Segment 2

    // Erste Generation
    for (int i = 0; i < 3; i++) {

        p1 = this->points[i]; //Erster Punkt wird gesetzt
        p2 = this->points[i + 1]; //Zweiter Punkt wird gesetzt

        p1.setX(p1.m_x * (1 - t)); //X-Wert für den ersten Punkt
        p1.setY(p1.m_y * (1 - t)); //y-Wert für den ersten Punkt
        p2.setX(p2.m_x * t); //X-Wert für den zweiten Punkt
        p2.setY(p2.m_y * t); //Y-Wert für dem zweiten Punkt

        if (i == 0) {
            segment1->setPoint(1, p1 + p2); //Zweiter Punkt für Segment1
        } else if (i == 1) {
            pTmp = (p1 + p2); //Temporärer Punkt
        } else {
            segment2->setPoint(2, p1 + p2); //Zweiter Punkt für Segment2
        }
    }

    // Zweite Generation
    p1 = segment1->points[1];
    p2 = pTmp;

    p1.setX(p1.m_x * (1 - t)); //X-Wert für den ersten Punkt
    p1.setY(p1.m_y * (1 - t)); //Y-Wert für den ersten Punkt
    p2.setX(p2.m_x * t); //X-Wert für den zweiten Punkt
    p2.setY(p2.m_y * t); //Y-Wert für den zweiten Punkt
    segment1->setPoint(2, p1 + p2); //Dritter Punkt für Segment1

    p1 = pTmp;
    p2 = segment2->points[2];
    p1.setX(p1.m_x * (1 - t)); //X-Wert für den ersten Punkt
    p1.setY(p1.m_y * (1 - t)); //Y-Wert für den ersten Punkt
    p2.setX(p2.m_x * t); //X-Wert für den zweiten Punkt
    p2.setY(p2.m_y * t); //Y-Wert für den zweiten Punkt
    segment2->setPoint(1, p1 + p2); //Dritter Punkt für Segment2

    // Dritte Generation
    p1 = segment1->points[2];
    p2 = segment2->points[1];

    p1.setX(p1.m_x * (1 - t)); //X-Wert für den ersten Punkt
    p1.setY(p1.m_y * (1 - t)); //Y-Wert für den ersten Punkt
    p2.setX(p2.m_x * t); //X-Wert für den zweiten Punkt
    p2.setY(p2.m_y * t); //Y-Wert für dem zweiten Punkt

    segment1->setPoint(3, p1 + p2); //Vierter Punkt für Segment1
    segment2->setPoint(0, p1 + p2); //Vierter Punkt für Segment2

    multipliyMatrix(0.5, segment1, segment2);
    //cout << "Ist es hier " << sizeof(segment1->points) << endl;
}


void CubicBezier::multipliyMatrix(float t, CubicBezier *aMatrix, CubicBezier *bMatrix) {

    float product1[4][4] = {{1,                           0,                         0,                   0},
                            {(1 - t),                     t,                         0,                   0},
                            {(1 - t) * (1 - t),           2 * (1 - t) * t,           t * t,               0},
                            {(1 - t) * (1 - t) * (1 - t), 3 * (1 - t) * (1 - t) * t, 3 * (1 - t) * t * t, t * t * t}};

    float product2[4][4] = {{0,         0,                   0,                         1},
                            {0,         0,                   t,                         (1 - t)},
                            {0,         t * t,               2 * (1 - t) * t,           (1 - t) * (1 - t)},
                            {t * t * t, 3 * (1 - t) * t * t, 3 * (1 - t) * (1 - t) * t, (1 - t) * (1 - t) * (1 - t)}};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            subDivMatrix1[i].m_x += product1[i][j] * aMatrix->points[j].m_x;
            subDivMatrix1[i].m_y += product1[i][j] * aMatrix->points[j].m_y;
            subDivMatrix2[i].m_x += product2[i][j] * bMatrix->points[j].m_x;
            subDivMatrix2[i].m_y += product2[i][j] * bMatrix->points[j].m_y;
        }
    }


/*
    cout << "subDivMatrix für die rechte Hälfte" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Stelle " << i << " " << "x: " << subDivMatrix1[i].m_x << "Y: " << subDivMatrix1[i].m_y << endl;
    }

    cout << "subDivMatrix für die linke Hälfte" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Stelle " << i << " " << "x: " << subDivMatrix2[i].m_x << "Y: " << subDivMatrix1[i].m_y << endl;
    }
*/
}

void CubicBezier::setPoint(int i, Point a) {
    points[i] = a;
}


