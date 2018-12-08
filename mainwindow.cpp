
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>
/*image on which shapes wouldbe drawn*/
QImage img;
/*image on which grids will be drawn*/
QImage grid;
/*size of grid , a variable */
int grid_size;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   ui->setupUi(this);
    ui->x_axis->hide();
    ui->y_axis->hide();

    img=QImage(ui->label->width(),ui->label->height(),QImage::Format_RGB888);
    grid=QImage(ui->label->width(),ui->label->height(),QImage::Format_ARGB32);
    connect(ui->label,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed()));

    /*enabling mouse functionality*/

    connect(ui->label,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
    ChangeGridSize(5);
    ui->label->setVisible(false);
    grid_size=5;

    /*setting upper and lwer limits of  spinboxes */
    ui->xTrans->setMaximum(img.width()/grid_size);
    ui->yTrans->setMaximum(img.height()/grid_size);

    ui->pivotx->setMaximum(img.width()/grid_size);
    ui->pivoty->setMaximum(img.height()/grid_size);

    ui->xTrans->setMinimum(-img.width()/grid_size);
    ui->yTrans->setMinimum(-img.height()/grid_size);

    ui->pivotx->setMinimum(-img.width()/grid_size);
    ui->pivoty->setMinimum(-img.height()/grid_size);

    ui->scalePivotX->setMaximum(img.width()/grid_size);
    ui->scalePivotY->setMaximum(img.height()/grid_size);

    ui->scalePivotX->setMinimum(-img.width()/grid_size);
    ui->scalePivotY->setMinimum(-img.height()/grid_size);

    ui->a->setMaximum(img.width()/grid_size);
    ui->b->setMaximum(img.height()/grid_size);
    ui->c->setMaximum(img.height()/grid_size);

    ui->a->setMinimum(-img.width()/grid_size);
    ui->b->setMinimum(-img.height()/grid_size);
    ui->c->setMinimum(-img.height()/grid_size);

    ui->degrees->setMaximum(360);
    ui->degrees->setMinimum(-360);

    /*setting bg color of groupBoxes*/
    QPalette outerpal = palette();
    outerpal.setColor(QPalette::Background, qRgb(220,220,220));
    ui->toolBox->setAutoFillBackground(true);
    ui->toolBox->setPalette(outerpal);
    ui->drawBox->setAutoFillBackground(true);
    ui->drawBox->setPalette(outerpal);
    ui->fillBox->setAutoFillBackground(true);
    ui->fillBox->setPalette(outerpal);
    ui->transformBox->setAutoFillBackground(true);
    ui->transformBox->setPalette(outerpal);
    ui->clipBox->setAutoFillBackground(true);
    ui->clipBox->setPalette(outerpal);
    ui->curveBox->setAutoFillBackground(true);
    ui->curveBox->setPalette(outerpal);
    ui->polygonBox->setAutoFillBackground(true);
    ui->polygonBox->setPalette(outerpal);

    QPalette innerpal = palette();
    innerpal.setColor(QPalette::Background, qRgb(180,180,180));

    ui->circleBox->setAutoFillBackground(true);
    ui->circleBox->setPalette(innerpal);
    ui->ellipseBox->setAutoFillBackground(true);
    ui->ellipseBox->setPalette(innerpal);
    ui->lineBox->setAutoFillBackground(true);
    ui->lineBox->setPalette(innerpal);
    ui->scaleBox->setAutoFillBackground(true);
    ui->scaleBox->setPalette(innerpal);
    ui->translateBox->setAutoFillBackground(true);
    ui->translateBox->setPalette(innerpal);
    ui->rotatationBox->setAutoFillBackground(true);
    ui->rotatationBox->setPalette(innerpal);
    ui->reflectBox->setAutoFillBackground(true);
    ui->reflectBox->setPalette(innerpal);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::point(int x,int y)
{
    for(int i=x-x%grid_size;i<x-x%grid_size+grid_size;i++){
    for(int j=y-y%grid_size;j<y-y%grid_size+grid_size;j++){
        img.setPixel(i,j,qRgb(255,255,0));
    }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::pointWindow(int x,int y)
{

    for(int i=x-x%grid_size;i<x-x%grid_size+grid_size;i++){
    for(int j=y-y%grid_size;j<y-y%grid_size+grid_size;j++){
        img.setPixel(i,j,qRgb(255,255,255));
    }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::erase(int x, int y)
{
    for(int i=x-x%grid_size;i<x-x%grid_size+grid_size;i++){
    for(int j=y-y%grid_size;j<y-y%grid_size+grid_size;j++){
        img.setPixel(i,j,qRgb(0,0,0));
    }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::showMousePosition(QPoint &pos)
{
    ui->mouse_movement->setText(" X : "+QString::number(pos.x())+", Y : "+QString::number(pos.y()));
}
void MainWindow::Mouse_Pressed()
{
    ui->mouse_pressed->setText(" X : "+QString::number(ui->label->x)+", Y : "+QString::number(ui->label->y));
    point(ui->label->x,ui->label->y);
    ui->x_axis->move(60,ui->label->y+10);
    ui->y_axis->move(ui->label->x+60,10);

}

void MainWindow::on_show_axes_clicked()
{
    if(ui->show_axes->isChecked())
    {
        ui->x_axis->show();
        ui->y_axis->show();
    }
    else{
        ui->x_axis->hide();
        ui->y_axis->hide();
    }
}
void MainWindow::on_set_point1_clicked()
{
    if(ui->draw_line->isChecked()){
        p1.setX(ui->label->x);
        p1.setY(ui->label->y);
    }
}

void MainWindow::on_set_point2_clicked()
{
    if(ui->draw_line->isChecked()){
        p2.setX(ui->label->x);
        p2.setY(ui->label->y);
    }
}

void MainWindow::on_Draw_clicked()
{
    int r0=(ui->circle_radius->value())*grid_size;
    QPainter painter(&img);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    if(ui->draw_circle->isChecked()){

        sphereCentres.append(QPoint(ui->label->x,ui->label->y));
        radiusList.append(r0);
        if(ui->midPointCircle->isChecked()){
            drawcircleMidpoint(ui->label->x,ui->label->y,r0);
        }
        else if(ui->bresenhamcircle->isChecked()){
            circleBres(ui->label->x,ui->label->y,r0);
        }
        else{
        p1.setX(ui->label->x);
        p1.setY(ui->label->y);
        painter.setPen(pen);
        painter.drawEllipse(p1,r0,r0);
        }
    }

    if(ui->drawEllipse->isChecked()){
        /*Add ellipse control points to list*/
        ellipseCentres.append(QPoint(ui->label->x,ui->label->y));
        ellipseMajor.append(ui->major->value());
        ellipseMinor.append(ui->minor->value());

        /*draw ellipse*/
        ellipse(ui->label->x,ui->label->y,(ui->major->value())*grid_size,(ui->minor->value())*grid_size);
    }

    if(ui->draw_line->isChecked()){
        qDebug()<<p1.x();
        lineEp1.append(p1);
        lineEp2.append(p2);

        if(ui->dda->isChecked()){
            DDA(p1.x(),p1.y(),p2.x(),p2.y());
        }
        else if(ui->bresenham->isChecked()){
            bresenham(p1.x(),p1.y(),p2.x(),p2.y());
        }
        else{
        painter.setPen(Qt::red);
        painter.drawLine(p1,p2);
        }
    }


    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_clicked()
{
    for(int j=0;j<img.height();j++)
    {
        for(int i=0;i<img.width();i++)
        {
            img.setPixel(i,j,qRgb(0,0,0));
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::ChangeGridSize(int arg1)
{
    for(int i=0;i<grid.width();i++){
        for(int j=0;j<=grid.height();j++){
            grid.setPixel(i,j,qRgba(0,0,0,0));
        }
    }
    for(int i=0;i<grid.width();i+=arg1){
        for(int j=0;j<=grid.height();j++){
            grid.setPixel(i,j,qRgb(255,0,0));
        }
    }
    for(int i=0;i<grid.width();i+=arg1){
        for(int j=0;j<=grid.height();j++){
            grid.setPixel(j,i,qRgb(255,0,0));
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(grid));
    on_pushButton_clicked();

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(arg1=="5 X 5"){ChangeGridSize(5);grid_size=5;}
    if(arg1=="10 X 10") {ChangeGridSize(10);grid_size=10;}
    if(arg1=="20 X 20") {ChangeGridSize(20);grid_size=20;}
    if(arg1=="30 X 30") {ChangeGridSize(30);grid_size=30;}
    if(arg1=="40 X 40"){ ChangeGridSize(40);grid_size=40;}
    if(arg1=="50 X 50"){ ChangeGridSize(50);grid_size=50;}
    if(arg1=="60 X 60") {ChangeGridSize(60);grid_size=60;}
    if(arg1=="100 X 100") {ChangeGridSize(100);grid_size=100;}
}


void MainWindow::on_showGrid_toggled(bool checked)
{
    if(checked) ui->label->setVisible(true);
    else ui->label->setVisible(false);
}
void MainWindow::ellipse(int x0, int y0, int rx, int ry){
    int x,y;
    double p;
    p=ry*ry-rx*rx*ry+rx*rx/4;
    x=0;
    y=ry;
    erase(x0,y0);
    while(2.0*ry*ry*x <= 2.0*rx*rx*y){
        if(p < 0){
            x++;
            p = p+2*ry*ry*x+ry*ry;
        }
        else{
            x++;y--;
            p = p+2*ry*ry*x-2*rx*rx*y-ry*ry;
        }
        point(x0+x,y0+y);
        point(x0+x,y0-y);
        point(x0-x,y0+y);
        point(x0-x,y0-y);
       }

    p=ry*ry*(x+0.5)*(x+0.5)+rx*rx*(y-1)*(y-1)-rx*rx*ry*ry;
    while(y > 0){
        if(p <= 0){
            x++;
            y--;
            p = p+2*ry*ry*x-2*rx*rx*y+rx*rx;
        }
        else{
            y--;
            p = p-2*rx*rx*y+rx*rx;
        }
        point(x0+x,y0+y);
        point(x0+x,y0-y);
        point(x0-x,y0+y);
        point(x0-x,y0-y);
    }
}


void MainWindow::drawCircle(int xc, int yc, int x, int y)
{
    point(xc+x, yc+y);
    point(xc-x, yc+y);
    point(xc+x, yc-y);
    point(xc-x, yc-y);
    point(xc+y, yc+x);
    point(xc-y, yc+x);
    point(xc+y, yc-x);
    point(xc-y, yc-x);
}

// Function for circle-generation
// using Bresenham's algorithm
void MainWindow::circleBres(int xc, int yc, int r)
{
    erase(xc,yc);
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels
        drawCircle(xc, yc, x, y);
        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y);
    }
}

void MainWindow::eraseCircle(int xc, int yc, int x, int y)
{
    erase(xc+x, yc+y);
     erase(xc-x, yc+y);
     erase(xc+x, yc-y);
     erase(xc-x, yc-y);
     erase(xc+y, yc+x);
     erase(xc-y, yc+x);
     erase(xc+y, yc-x);
     erase(xc-y, yc-x);
}

// Function for circle-generation
// using Bresenham's algorithm
void MainWindow::eraseCricleBres(int xc, int yc, int r)
{
    erase(xc,yc);
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels
        eraseCircle(xc, yc, x, y);
        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        eraseCircle(xc, yc, x, y);
    }
}
void MainWindow::drawcircleMidpoint(int x0, int y0, int radius)
{
    int x = radius;
    int y = 0;
    int err = 0;
    erase(x0,y0);
    while (x >= y)
    {
    point(x0 + x, y0 + y);
    point(x0 + y, y0 + x);
    point(x0 - y, y0 + x);
    point(x0 - x, y0 + y);
    point(x0 - x, y0 - y);
    point(x0 - y, y0 - x);
    point(x0 + y, y0 - x);
    point(x0 + x, y0 - y);

    if (err <= 0)
    {
        y += 1;
        err += 2*y + 1;
    }

    if (err > 0)
    {
        x -= 1;
        err -= 2*x + 1;
    }
    }
}
void MainWindow::DDA(int x0, int y0, int x1, int y1){
    int dx=x1-x0;
    int dy=y1-y0;
    int step=abs(dx)>abs(dy)?abs(dx):abs(dy);
    double Xinc = dx / (float) step;
    double Yinc = dy / (float) step;
    double X = x0;
    double Y = y0;
    for(int i=0;i<=step;i++){
        point(X,Y);
        X+= Xinc;
        Y+= Yinc;
    }

}
void MainWindow::swap(int &x,int &y){
    int tmp=x;
    x=y;
    y=tmp;
}
void MainWindow::bresenham(int x0, int y0, int x1, int y1){
    int dx=abs(x1-x0);
    int dy=abs(y1-y0);
    int p,x,y,xEnd,yEnd,m1,m2;
    if(dx>dy){
        p=2*dy-dx;
        m1=2*dy;
        m2=2*dy-2*dx;
        if(x0>x1){
            x=x1;
            y=y1;
            xEnd=x0;
            yEnd=y0;
            }
        else{
            x=x0;
            y=y0;
            xEnd=x1;
            yEnd=y1;
        }
        point(x,y);
        if(yEnd>y){
            while(x<xEnd){
               x++;
                if(p<0) p+=m1;
                else{
                    y++;
                    p+=m2;
                 }
                point(x,y);
            }
        }
        else{
            while(x<xEnd){
                x++;
                if(p<0) p+=m1;
                else{
                    y--;
                    p+=m2;
                 }
                point(x,y);
            }
        }
    }
    else{
        swap(dx,dy);
        swap(x0,y0);
        swap(x1,y1);
        p=2*dy-dx;
        m1=2*dy;
        m2=2*dy-2*dx;
        if(x0>x1){
            x=x1;
            y=y1;
            xEnd=x0;
            yEnd=y0;
            }
        else{
            x=x0;
            y=y0;
            xEnd=x1;
            yEnd=y1;
        }
        point(y,x);
        if(yEnd>y){
            while(x<xEnd){
               x++;
                if(p<0) p+=m1;
                else{
                    y++;
                    p+=m2;
                 }
                point(y,x);
            }
        }
        else{
            while(x<xEnd){
                x++;
                if(p<0) p+=m1;
                else{
                    y--;
                    p+=m2;
                 }
                point(y,x);
            }
        }
    }
}
void MainWindow::erasebresenham(int x0, int y0, int x1, int y1){
    int dx=abs(x1-x0);
    int dy=abs(y1-y0);
    int p,x,y,xEnd,yEnd,m1,m2;
    if(dx>dy){
        p=2*dy-dx;
        m1=2*dy;
        m2=2*dy-2*dx;
        if(x0>x1){
            x=x1;
            y=y1;
            xEnd=x0;
            yEnd=y0;
            }
        else{
            x=x0;
            y=y0;
            xEnd=x1;
            yEnd=y1;
        }
        erase(x,y);
        if(yEnd>y){
            while(x<xEnd){
               x++;
                if(p<0) p+=m1;
                else{
                    y++;
                    p+=m2;
                 }
                erase(x,y);
            }
        }
        else{
            while(x<xEnd){
                x++;
                if(p<0) p+=m1;
                else{
                    y--;
                    p+=m2;
                 }
                erase(x,y);
            }
        }
    }
    else{
        swap(dx,dy);
        swap(x0,y0);
        swap(x1,y1);
        p=2*dy-dx;
        m1=2*dy;
        m2=2*dy-2*dx;
        if(x0>x1){
            x=x1;
            y=y1;
            xEnd=x0;
            yEnd=y0;
            }
        else{
            x=x0;
            y=y0;
            xEnd=x1;
            yEnd=y1;
        }
        erase(y,x);
        if(yEnd>y){
            while(x<xEnd){
               x++;
                if(p<0) p+=m1;
                else{
                    y++;
                    p+=m2;
                 }
                erase(y,x);
            }
        }
        else{
            while(x<xEnd){
                x++;
                if(p<0) p+=m1;
                else{
                    y--;
                    p+=m2;
                 }
                erase(y,x);
            }
        }
    }
}
void MainWindow::floodFill(int x,int y,int oldcolor,int newcolor,int gridsize){
    uint col=img.pixel(x,y);
    if(col== oldcolor)
    {
        point(x,y);
        /*recursively fill all the pixels which are black*/
        floodFill(x+gridsize,y,oldcolor,newcolor,gridsize);
        floodFill(x,y+gridsize,oldcolor,newcolor,gridsize);
        floodFill(x-gridsize,y,oldcolor,newcolor,gridsize);
        floodFill(x,y-gridsize,oldcolor,newcolor,gridsize);
    }
}
void MainWindow::on_Flood_clicked()
{
    floodFill(ui->label->x,ui->label->y,qRgb(0,0,0),qRgb(255,255,255),grid_size);
}

void MainWindow::on_pushButton_2_clicked()
{
    erase(ui->label->x,ui->label->y);
}
void MainWindow::boundaryFill(int x,int y,int oldcolor,int newcolor,int gridsize){
    uint col=img.pixel(x,y);
    int flag=0;
    if(col== oldcolor)
    {
        point(x,y);
        boundaryFill(x+gridsize,y,oldcolor,newcolor,gridsize);
        boundaryFill(x,y+gridsize,oldcolor,newcolor,gridsize);
        boundaryFill(x-gridsize,y,oldcolor,newcolor,gridsize);
        boundaryFill(x,y-gridsize,oldcolor,newcolor,gridsize);
        if(img.pixel(x+gridsize,y)==oldcolor or img.pixel(x,y+gridsize)==oldcolor)boundaryFill(x+gridsize,y+gridsize,oldcolor,newcolor,gridsize);
        if(img.pixel(x+gridsize,y)==oldcolor or img.pixel(x,y-gridsize)==oldcolor)boundaryFill(x+gridsize,y-gridsize,oldcolor,newcolor,gridsize);
        if(img.pixel(x-gridsize,y)==oldcolor or img.pixel(x,y+gridsize)==oldcolor)boundaryFill(x-gridsize,y+gridsize,oldcolor,newcolor,gridsize);
        if(img.pixel(x-gridsize,y)==oldcolor or img.pixel(x,y-gridsize)==oldcolor)boundaryFill(x-gridsize,y-gridsize,oldcolor,newcolor,gridsize);
    }
}

void MainWindow::on_Boundary_clicked()
{
   boundaryFill(ui->label->x,ui->label->y,qRgb(0,0,0),qRgb(255,255,255),grid_size);
}

void MainWindow::on_translate_clicked()
{
    /*erase screen*/
    on_pushButton_clicked();
    int xtrans=ui->xTrans->value();
    int ytrans=-ui->yTrans->value();

    /*shift line endpoints*/
    for(int i=0;i<lineEp1.length();i++){
        int xOld1=lineEp1[i].x();
        int yOld1=lineEp1[i].y();
        //calculate new endpoint values
        int xNew1=xOld1+xtrans*grid_size;
        int yNew1=yOld1+ytrans*grid_size;
        int xOld2=lineEp2[i].x();
        int yOld2=lineEp2[i].y();
        int xNew2=xOld2+xtrans*grid_size;
        int yNew2=yOld2+ytrans*grid_size;

        bresenham(xNew1,yNew1,xNew2,yNew2);

        //add back new endpoint values to list
        lineEp1[i].setX(xNew1);
        lineEp1[i].setY(yNew1);
        lineEp2[i].setX(xNew2);
        lineEp2[i].setY(yNew2);
    }
   /*shift circleCentres*/
    for(int i=0;i<sphereCentres.length();i++){
        int xOld1=sphereCentres[i].x();
        int yOld1=sphereCentres[i].y();
        //calculate new centre values
        int xNew1=xOld1+xtrans*grid_size;
        int yNew1=yOld1+ytrans*grid_size;
        circleBres(xNew1,yNew1,radiusList[i]);
        //add new centres back to list
        sphereCentres[i].setX(xNew1);
        sphereCentres[i].setY(yNew1);
    }
}

void MainWindow::on_rotate_clicked()
{
    on_pushButton_clicked();
    double rad=(ui->degrees->value()*2*M_PI)/180;

    int xr=ui->pivotx->value()*grid_size+300;
    int yr=-(ui->pivoty->value()*grid_size)+300;

    for(int i=0;i<lineEp1.length();i++){
        int xOld1=lineEp1[i].x();
        int yOld1=lineEp1[i].y();
        int xNew1=xr+(int)((double)(xOld1-xr)*qCos(rad)-(double)(yOld1-yr)*qSin(rad));
        int yNew1=yr+(int)((double)(xOld1-xr)*qSin(rad)+(double)(yOld1-yr)*qCos(rad));

        int xOld2=lineEp2[i].x();
        int yOld2=lineEp2[i].y();
        int xNew2=xr+(int)((double)(xOld2-xr)*qCos(rad)-(double)(yOld2-yr)*qSin(rad));
        int yNew2=yr+(int)((double)(xOld2-xr)*qSin(rad)+(double)(yOld2-yr)*qCos(rad));
        //erasebresenham(xOld1,yOld1,xOld2,yOld2);
        bresenham(xNew1,yNew1,xNew2,yNew2);

        lineEp1[i].setX(xNew1);
        lineEp1[i].setY(yNew1);
        lineEp2[i].setX(xNew2);
        lineEp2[i].setY(yNew2);
    }

    for(int i=0;i<sphereCentres.length();i++){
        int xOld1=sphereCentres[i].x();
        int yOld1=sphereCentres[i].y();
        int xNew1=xr+(int)((double)(xOld1-xr)*qCos(rad)-(double)(yOld1-yr)*qSin(rad));
        int yNew1=yr+(int)((double)(xOld1-xr)*qSin(rad)+(double)(yOld1-yr)*qCos(rad));
        //eraseCricleBres(xOld1,yOld1,radiusList[i]);
        circleBres(xNew1,yNew1,radiusList[i]);
        sphereCentres[i].setX(xNew1);
        sphereCentres[i].setY(yNew1);
    }
}

void MainWindow::on_Scale_clicked()
{
    on_pushButton_clicked();
    int scalePivotx=ui->label->x;
    int scalePivoty=ui->label->y;
    ui->scalePivotX->setValue((scalePivotx-300)/grid_size);
    ui->scalePivotY->setValue((300-scalePivoty)/grid_size);
    double S=ui->scaleValue->value();

     for(int i=0;i<lineEp1.length();i++){
         int xOld1=lineEp1[i].x();
         int yOld1=lineEp1[i].y();
         int xNew1=(xOld1-scalePivotx)*S+scalePivotx;
         int yNew1=(yOld1-scalePivoty)*S+scalePivoty;

         int xOld2=lineEp2[i].x();
         int yOld2=lineEp2[i].y();
         int xNew2=(xOld2-scalePivotx)*S+scalePivotx;
         int yNew2=(yOld2-scalePivoty)*S+scalePivoty;
          //erasebresenham(xOld1,yOld1,xOld2,yOld2);
         bresenham(xNew1,yNew1,xNew2,yNew2);

         lineEp1[i].setX(xNew1);
         lineEp1[i].setY(yNew1);
         lineEp2[i].setX(xNew2);
         lineEp2[i].setY(yNew2);
     }

     for(int i=0;i<sphereCentres.length();i++){
         int xOld1=sphereCentres[i].x();
         int yOld1=sphereCentres[i].y();
         int xNew1=(xOld1-scalePivotx)*S+scalePivotx;
         int yNew1=(yOld1-scalePivoty)*S+scalePivoty;
         radiusList[i]*=S;
         //eraseCricleBres(xOld1,yOld1,radiusList[i]);
         circleBres(xNew1,yNew1,radiusList[i]);
         sphereCentres[i].setX(xNew1);
         sphereCentres[i].setY(yNew1);
     }
}

void MainWindow::on_reflect_clicked()
{
   on_pushButton_clicked();
   int a=ui->a->value();
   int b=-ui->b->value();
   int c=ui->c->value()*grid_size;

   for(int i=0;i<lineEp1.length();i++){
       int x1=(lineEp1[i].x()-300);
       int y1=(lineEp1[i].y()-300);
       int xNew1=x1+300+(double)a*(double)(-2*a*x1-2*b*y1-2*c)/(double)(a*a+b*b);
       int yNew1=y1+300+(double)b*(double)(-2*a*x1-2*b*y1-2*c)/(double)(a*a+b*b);
       int x2=lineEp2[i].x()-300;
       int y2=lineEp2[i].y()-300;
       int xNew2=x2+300+(double)a*(double)(-2*a*x2-2*b*y2-2*c)/(double)(a*a+b*b);
       int yNew2=y2+300+(double)b*(double)(-2*a*x2-2*b*y2-2*c)/(double)(a*a+b*b);
        //erasebresenham(xOld1,yOld1,xOld2,yOld2);
       bresenham(xNew1,yNew1,xNew2,yNew2);

       lineEp1[i].setX(xNew1);
       lineEp1[i].setY(yNew1);
       lineEp2[i].setX(xNew2);
       lineEp2[i].setY(yNew2);
   }

   for(int i=0;i<sphereCentres.length();i++){
       int x1=(sphereCentres[i].x()-300);
       int y1=(sphereCentres[i].y()-300);
       int xNew1=x1+300+(double)a*(double)(-2*a*x1-2*b*y1-2*c)/(double)(a*a+b*b);
       int yNew1=y1+300+(double)b*(double)(-2*a*x1-2*b*y1-2*c)/(double)(a*a+b*b);
       circleBres(xNew1,yNew1,radiusList[i]);
       sphereCentres[i].setX(xNew1);
       sphereCentres[i].setY(yNew1);
   }
}

int MainWindow::computeCode(int x, int y)
{
    int code = INSIDE;
        if (x < x_min) code |= LEFT;
        else if (x > x_max)  code |= RIGHT;
        if (y < y_min)       code |= BOTTOM;
        else if (y > y_max)  code |= TOP;
       return code;
}
void MainWindow::cohenSutherlandClip()
{
  for(int i=0;i<lineEp1.length();i++){
    int x1=lineEp1[i].x();
    int y1=lineEp1[i].y();

    int x2=lineEp2[i].x();
    int y2=lineEp2[i].y();

    erasebresenham(x1,y1,x2,y2);

    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1 & code2)
        {
            // If both endpoints are outside rectangle,
            // in same region
            break;
        }
        else
        {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            double x, y;

            // At least one endpoint is outside the
            // rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP)
            {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                // point is below the rectangle
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Now intersection point x,y is found
            // We replace point outside rectangle
            // by intersection point
            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept)
    {
        lineEp1[i].setX(x1);
        lineEp1[i].setY(y1);
        lineEp2[i].setX(x2);
        lineEp2[i].setY(y2);
        bresenham(x1,y1,x2,y2);
    }
  }
}

void MainWindow::on_clip_clicked()
{
cohenSutherlandClip();
on_drawWindow_clicked();
}

void MainWindow::on_selectWindow_clicked()
{
    x_min=ui->label->x;
    y_min=ui->label->x;
}

void MainWindow::on_drawWindow_clicked()
{
    qDebug()<<"here";
    for(int i=x_min;i<=x_max;i++) pointWindow(i,y_min);
    for(int i=x_min;i<=x_max;i++) pointWindow(i,y_max);
    for(int i=y_min;i<=y_max;i++) pointWindow(x_max,i);
    for(int i=y_min;i<=y_max;i++) pointWindow(x_min,i);
}

void MainWindow::on_selectBottomLeft_clicked()
{
    erase(ui->label->x,ui->label->y);
    x_min=ui->label->x;
    y_min=ui->label->y;
}

void MainWindow::on_selectTopRight_clicked()
{
    erase(ui->label->x,ui->label->y);
    x_max=ui->label->x;
    y_max=ui->label->y;
}
int MainWindow::x_intersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4)
{
    int num = (x1*y2 - y1*x2) * (x3-x4) -
              (x1-x2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

// Returns y-value of point of intersectipn of
// two lines
int  MainWindow::y_intersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4)
{
    int num = (x1*y2 - y1*x2) * (y3-y4) -
              (y1-y2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

// This functions clips all the edges w.r.t one clip
// edge of clipping area
void  MainWindow::clip(int x1, int y1, int x2, int y2)
{
     QList<QPoint> tempClip;
    // (ix,iy),(kx,ky) are the co-ordinate values of
    // the points
    for (int i = 0; i < polygonVertices.size(); i++)
    {
        // i and k form a line in polygon
        int k = (i+1) % polygonVertices.size();
        int ix = polygonVertices[i].x(), iy = polygonVertices[i].y();
        int kx = polygonVertices[k].x(), ky = polygonVertices[k].y();

        // Calculating position of first point
        // w.r.t. clipper line
        int i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1);

        // Calculating position of second point
        // w.r.t. clipper line
        int k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1);

        // Case 1 : When both points are inside
        if (i_pos < 0  && k_pos < 0)
        {
            //Only second point is added
            tempClip.append(QPoint(kx,ky));
        }

        // Case 2: When only first point is outside
        else if (i_pos >= 0  && k_pos < 0)
        {
            // Point of intersection with edge
            // and the second point is added
            tempClip.append(QPoint(x_intersect(x1,
                                               y1, x2, y2, ix, iy, kx, ky), y_intersect(x1,
                                                                                        y1, x2, y2, ix, iy, kx, ky)));


            tempClip.append(QPoint(kx,ky));
        }

        // Case 3: When only second point is outside
        else if (i_pos < 0  && k_pos >= 0)
        {
            //Only point of intersection with edge is added
            tempClip.append(QPoint(x_intersect(x1,
                                               y1, x2, y2, ix, iy, kx, ky), y_intersect(x1,
                                                                                        y1, x2, y2, ix, iy, kx, ky)));
        }

        // Case 4: When both points are outside
        else
        {
            //No points are added
        }
    }

    // Copying new points into original array
    // and changing the no. of vertices
    polygonVertices=tempClip;
}

// Implements Sutherland–Hodgman algorithm
void  MainWindow::suthHodgClip(int clipper_points[][2], int clipper_size)
{
    //i and k are two consecutive indexes
    for (int i=0; i<clipper_size; i++)
    {
        int k = (i+1) % clipper_size;

        // We pass the current array of vertices, it's size
        // and the end points of the selected clipper line
        clip(clipper_points[i][0],
             clipper_points[i][1], clipper_points[k][0],
             clipper_points[k][1]);
    }

}

void MainWindow::on_setVertex_clicked()
{
    ui->polygonList->addItem(QString("X=%1,Y=%2").arg(ui->label->x).arg(ui->label->y));
    /*add vertex to vertex list*/
    polygonVertices.append(QPoint(ui->label->x,ui->label->y));
}

void MainWindow::on_drawPolygon_clicked()
{
    /*draw sides of the polygon in order they were clicked*/
    for(int i=1;i<=polygonVertices.size();i++){
        bresenham(polygonVertices[i-1].x(),polygonVertices[i-1].y(),polygonVertices[i%polygonVertices.size()].x(),polygonVertices[i%polygonVertices.size()].y());

}
}

void MainWindow::erasePolygon()
{
    for(int i=1;i<=polygonVertices.size();i++){
        erasebresenham(polygonVertices[i-1].x(),polygonVertices[i-1].y(),polygonVertices[i%polygonVertices.size()].x(),polygonVertices[i%polygonVertices.size()].y());

}
}

void MainWindow::on_polygonClip_clicked()
{
    erasePolygon();
    int clipperPoints[4][2];
    clipperPoints[0][0]=x_min;
    clipperPoints[0][1]=y_min;

    clipperPoints[1][0]=x_min;
    clipperPoints[1][1]=y_max;

    clipperPoints[2][0]=x_max;
    clipperPoints[2][1]=y_max;

    clipperPoints[3][0]=x_max;
    clipperPoints[3][1]=y_min;

    suthHodgClip(clipperPoints,4);
    on_drawPolygon_clicked();

}


void MainWindow::on_setControlPoint_clicked()
{
    erase(ui->label->x,ui->label->y);
    ui->curveCtrlPts->addItem(QString("X=%1,Y=%2").arg(ui->label->x).arg(ui->label->y));
    vec2.append(QPoint(ui->label->x,ui->label->y));
}
int MainWindow:: factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}
void MainWindow::on_drawCurve_clicked()
{
    int n=vec2.length()-1,i;
    int xt,yt;
  for(double t=0;t<=1;t=t+0.01){
        xt=0;
        yt=0;

        i=0;
        while(i<=n){
            xt=xt+(factorial(n)/(factorial(n-i)*factorial(i)))*pow(1-t,n-i)*pow(t,i)*vec2[i].x();
            yt=yt+(factorial(n)/(factorial(n-i)*factorial(i)))*pow(1-t,n-i)*pow(t,i)*vec2[i].y();

            i++;
        }
        point(xt,yt);
    }

    ui->curveCtrlPts->clear();
    vec2.clear();
}

