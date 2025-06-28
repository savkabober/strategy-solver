// #include "drawing.h"
#include <stdio.h>
#include "aux.h"
int main()
{
    // Risovalka drawer = Risovalka(1000,1000);
    // while (drawer.window.isOpen())
    // {
    //     drawer.drawCircle(Point(100,100),100,Color(255,255,255));
    //     drawer.drawLine(Point(100,100),Point(200,200),3,Color(200,200,200));
    //     drawer.drawRectangle(Point(300,300),500,500,Color(200,200,200));
    //     drawer.update();
    // }
    Point pt = Point(10,10);
    Point p = Point(100,23);
    pt=pt+p;
    printf("%f",pt.x);
    return 0;
}