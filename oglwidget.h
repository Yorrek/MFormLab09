#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QVector>
#include "res/Point.hpp"
#include "res/CubicBezier.hpp"
#include "res/Poly.h"

class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

    // Used to select points
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    QVector<QPointF> selpoints; // Last position of mouse pressed, used for dragging
    //QVector<QPointF> bezierpoints; // bezier points, calculated from selpoints


    static const int viewportsize = 20;
};


#endif // OGLWIDGET_H
