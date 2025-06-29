// #include "aux.h"
// #include "field.h"
#include "include/drawing.h"
#include <time.h>
int main()
{
    
    Field field = Field(FIELD_DX,FIELD_DY,PEN_DX,PEN_DY,POLARITY);
    // Point al_pos[MAX_ROBOT_COUNT];
    // Point en_pos[MAX_ROBOT_COUNT];
    // float al_ang[MAX_ROBOT_COUNT];
    // float en_ang[MAX_ROBOT_COUNT];
    // field.update_all(al_pos,al_ang,en_pos,en_ang,Point(10,10),time(NULL));
    Risovalka drawer = Risovalka(500,500);
    while (drawer.window.isOpen())
    {
        // drawer.drawCircle(Point(100,100),100,Color(200,200,200));
        drawer.drawField(field);
        drawer.update();
    }
    
    return 0;
}