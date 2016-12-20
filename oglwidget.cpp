#include "oglwidget.h"
#include <cmath>
#include <QDebug>
#include <iostream>

using namespace std;

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void OGLWidget::paintGL()
{
    // Clear the scene
    glClearColor(0.f, 0.f, 0.f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Prepare projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
                                               // Parallel projection with
    glOrtho(-viewportsize/2, viewportsize/2,   // clipping planes: left,   right
            -viewportsize/2, viewportsize/2,   //                  bottom, top
            -viewportsize/2, viewportsize/2 ); //                  near,   far

    // Prepare model matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // No lines to draw
    if( selpoints.size() < 2 )
        return;

    // Draw line segments

    glBegin(GL_LINE_STRIP);

    for( int i = 0; i < selpoints.size(); i++ ){
        glVertex2f( selpoints[i].x(), selpoints[i].y() );
    }
    glEnd();

    /*
     * Draw Bezier segments
     */

    if( selpoints.size() > 3){
        glColor3ub(0xFF, 0x00, 0x00); // draw color = red
        // Ein CubicBezier Objekt (bezier) wird erstellt und mit den Punkten von selpoints befüllt

        CubicBezier bezier;
        for( int i = 0; i < selpoints.size(); i++ ){
             bezier.setPoint(i, Point( selpoints[i].x(), selpoints[i].y() ));
        }

        // Die Segmente werden erzeugt und berechnet

        CubicBezier segment1;
        CubicBezier segment2;

        bezier.Subdivide((float)0.5, &segment1, &segment2);

        // Die Segmente werden gezeichnet

        glBegin(GL_LINE_STRIP);

        // Segment1:
        for (int i = 0; i<(int)ARRAYSIZE(segment1.points); i++){
            glVertex2f( segment1.points[i].m_x, segment1.points[i].m_y );
        }

        // Segment2:
        for (int i = 0; i < (int)ARRAYSIZE(segment2.points); i++){
            glVertex2f( segment2.points[i].m_x, segment2.points[i].m_y );
        }
        glEnd();
    }



    if( selpoints.size() > 4){
        Poly poly;
        for( int i = 0; i < (int)selpoints.size(); i++ ){
             poly.addPoint(Point( selpoints[i].x(), selpoints[i].y() ));
        }
        poly.subdivideSplines(&poly);
        poly.interpolCubic(&poly);

        Poly poly2;
        for ( int i = 0; i < (int)poly.interpolPoints.size(); i++) {
            poly2.addPoint(poly.interpolPoints[i]);
        }

        poly2.interpolCubic(&poly2);

        Poly poly3;
        for ( int i = 0; i < (int)poly2.interpolPoints.size(); i++) {
            poly3.addPoint(poly2.interpolPoints[i]);
        }

        poly3.interpolCubic(&poly3);

        glColor3ub(0x00, 0xFF, 0x00); // draw color = green

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < (int)poly.cubicPoints.size(); i++){
            glVertex2f( poly.cubicPoints[i].m_x, poly.cubicPoints[i].m_y);
        }
        glEnd();

        glColor3ub(0x00, 0xFF, 0xFF); // draw color = cyan

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < (int)poly3.interpolPoints.size(); i++){
            glVertex2f( poly.interpolPoints[i].m_x, poly.interpolPoints[i].m_y);
        }
        glEnd();

    }

}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    // Upon mouse pressed, we store the current position...
    QPoint mp = event->pos();

    // ... determine the current widget size ...
    double w  = this->width();
    double h  = this->height();

    // ... and adjust to the current GL viewport
    QPointF wp( double( mp.x() ) / w * viewportsize - viewportsize/2,
                viewportsize/2 - double( mp.y() ) / h * viewportsize );

    // Add this point to the list of selected points
    selpoints.append( wp );
    //bezierpoints.append( wp );

    // This forces the GL widget to be redrawn
    update();
}
