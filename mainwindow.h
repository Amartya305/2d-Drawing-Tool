#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void Mouse_Pressed();
    void showMousePosition(QPoint& pos);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void erasePolygon();
    int factorial(int n);
private slots:
    void on_show_axes_clicked();

    void on_Draw_clicked();

    void on_set_point1_clicked();

    void on_set_point2_clicked();

    void on_pushButton_clicked();

    void ChangeGridSize(int arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_showGrid_toggled(bool checked);

    void DDA(int x0, int y0, int x1, int y1);

    void bresenham(int x0, int y0, int x1, int y1);

    void drawcircleMidpoint(int x0,int y0,int r);
    void ellipse(int,int,int,int);

    void drawCircle(int xc, int yc, int x, int y);
    void circleBres(int xc, int yc, int r);
    void on_Flood_clicked();

    void on_pushButton_2_clicked();

    void on_Boundary_clicked();

    void on_translate_clicked();

    void on_rotate_clicked();


    void on_Scale_clicked();

    void on_reflect_clicked();

    void on_clip_clicked();

    void on_selectWindow_clicked();

    void on_drawWindow_clicked();

    void on_selectBottomLeft_clicked();

    void on_selectTopRight_clicked();

    void on_drawPolygon_clicked();

    void on_setVertex_clicked();

    void on_polygonClip_clicked();

    void on_setControlPoint_clicked();

    void on_drawCurve_clicked();

private:
    Ui::MainWindow *ui;
    QPoint p1,p2;
    QList<QPoint> sphereCentres,lineEp1,lineEp2,ellipseCentres,polygonVertices,tempClip,vec2;
    QList<int> radiusList,ellipseMajor,ellipseMinor;
    const int INSIDE = 0;
    const int LEFT = 1;
    const int RIGHT = 2;
    const int BOTTOM = 4;
    const int TOP = 8;
    int x_max,y_max,x_min,y_min;
    int computeCode(int x,int y);
    int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
    int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
    void cohenSutherlandClip();
    void clip(int x1, int y1, int x2, int y2);
    void suthHodgClip(int clipper_points[][2], int clipper_size);
    void point(int,int);
    void pointWindow(int x, int y);
    void erase(int,int);
    void swap(int &x, int &y);
    void floodFill(int x, int y, int oldcolor, int newcolor,int gridsize);
    void boundaryFill(int x, int y, int oldcolor, int newcolor ,int gridsize);
    void erasebresenham(int x0, int y0, int x1, int y1);
    void eraseCircle(int xc, int yc, int x, int y);
    void eraseCricleBres(int xc, int yc, int r);
};

#endif // MAINWINDOW_H
