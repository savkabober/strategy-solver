// #include "aux.h"
// #include "field.h"
#include "include/drawing.h"
#include <time.h>
int main()
{
    
    // Field field = Field(FIELD_DX,FIELD_DY,PEN_DX,PEN_DY,POLARITY);
    // Point al_pos[MAX_ROBOT_COUNT];
    // Point en_pos[MAX_ROBOT_COUNT];
    // float al_ang[MAX_ROBOT_COUNT];
    // float en_ang[MAX_ROBOT_COUNT];
    // field.update_all(al_pos,al_ang,en_pos,en_ang,Point(10,10),time(NULL));
    Risovalka drawer = Risovalka(900,600);
    while (drawer.window.isOpen())
    {
        drawer.drawCircle(Point(4500,3000),100,Color(255,255,255));
        drawer.drawCircle(Point(0,0),500,Color(255,255,255));
        drawer.drawCircle(Point(0,0),480,FIELD_COLOR);
        // drawer.drawField(field);
        drawer.update();
    }
    
    return 0;
}