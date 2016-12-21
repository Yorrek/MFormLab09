//
// Created by Nico Lassen on 18.12.16.
//

#include <iostream>
#include "Poly.h"

using namespace std;

//Leerer Konstruktor
Poly::Poly() {
}

Poly::~Poly() {
}

// Methode um Poly in kubische Splines zu unterteilen

//TODO ALLES ANPASSEN, FOR-SCHLEIFEN FÜR BEIDE DIMENSIONEN! (EXCEL)
void Poly::subdivideSplines(Poly *poly) {
    vector<vector<float> > cubicSplineMask(poly->points.size() * 2 - 1, vector<float>(poly->points.size()));

    //alle stellen auf 0 setzen
    for (int i = 0; i < poly->points.size() * 2 - 1; i++) {
        for (int j = 0; j < poly->points.size(); j++) {
            cubicSplineMask[i][j] = 0;
        }
    }

    //erste stelle auf 1 setzen
    cubicSplineMask[0][0] = 1;

    // Alle zwei Zeilen
    int counter = 0;
    for (int i = 1; i < poly->points.size() * 2 - 1; i++) {
        cubicSplineMask[i][counter] = .5;
        cubicSplineMask[i][counter + 1] = .5;
        counter++;
        i++;
    }

    // Alle zwei Zeilen
    counter = 0;
    for (int i = 2; i < poly->points.size() * 2 - 1; i++) {
        cubicSplineMask[i][counter] = .125;
        cubicSplineMask[i][counter + 1] = .75;
        cubicSplineMask[i][counter + 2] = .125;
        i++;
        counter++;
    }

    // Letzte Zeile mit nullen füllen
    for (int i = 0; i < poly->points.size(); i++) {
        cubicSplineMask[poly->points.size() * 2 - 2][i] = 0;
    }

    // Letzte Stelle auf eins setzen
    cubicSplineMask[poly->points.size() * 2 - 2][poly->points.size() - 1] = 1;

    for (int i = 0; i < poly->points.size() * 2 - 1; i++) {

        pTmp.setX(0);
        pTmp.setY(0);
        for (int j = 0; j < poly->points.size(); j++) {
            pTmp.m_x += cubicSplineMask[i][j] * points[j].m_x;
            pTmp.m_y += cubicSplineMask[i][j] * points[j].m_y;
        }
        cubicPoints.push_back(pTmp); // Die neuen Punkte werden gespeichert
    }

}

//Methode um interpolierende kubische Segmente zu unterteilen.
void Poly::interpolCubic(Poly *interpol) {
    vector<vector<float> > interpolMask(interpol->points.size() * 2 - 1, vector<float>(interpol->points.size()));

    //alle stellen auf 0 setzen
    for (int i = 0; i < interpol->points.size() * 2 - 1; i++) {
        for (int j = 0; j < interpol->points.size(); j++) {
            interpolMask[i][j] = 0;
        }
    }

    // Alle "1" setzen
    for (int i = 0; i < interpol->points.size() * 2 - 1; i++) {
        for (int j = 0; j < interpol->points.size(); j++) {
            interpolMask[i * 6][j * 5] = 1;
            interpolMask[i * 6 + 2][j * 5 + 1] = 1;
            interpolMask[i * 6 + 4][j * 5 + 2] = 1;
        }
    }


    // Alle "3/8 3/4 -1/8" setzen
    counter = 0;
    for (int i = 1; i < interpol->points.size() * 2 - 1; i += 6) {
        interpolMask[i][counter] = .375;
        interpolMask[i][counter + 1] = .75;
        interpolMask[i][counter + 2] = -.125;
        counter++;
    }

    // Alle zwei Zeilen
    counter = 0;
    for (int i = 1; i < interpol->points.size() * 2 - 1; i += 2) {
        for (int j = 0; j < 2; j++){
            interpolMask[i * 3 + j * 2][counter] = -.0625;
            interpolMask[i * 3 + j * 2][counter + 1] = .5625;
            interpolMask[i * 3 + j * 2][counter + 2] = .5625;
            interpolMask[i * 3 + j * 2][counter + 3] = -.0625;
        }
        counter++;
        i++;
    }

    // Letzte Zeile mit nullen füllen
    for (int i = 0; i < interpol->points.size(); i++) {
        interpolMask[interpol->points.size() * 2 - 2][i] = 0;
    }

    // Letzte Stelle auf eins setzen
    interpolMask[interpol->points.size() * 2 - 2][interpol->points.size() - 1] = 1;

    for (int i = 0; i < interpol->points.size() * 2 - 1; i++) {

        pTmp.setX(0);
        pTmp.setY(0);
        for (int j = 0; j < interpol->points.size(); j++) {
            pTmp.m_x += interpolMask[i][j] * points[j].m_x;
            pTmp.m_y += interpolMask[i][j] * points[j].m_y;
        }
        interpolPoints.push_back(pTmp); // Die neuen Punkte werden gespeichert.
    }


}

// Methde um points einen Punkt hinzuzufügen
void Poly::addPoint(Point a) {
    points.push_back(a);
}
