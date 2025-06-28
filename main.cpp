#include "field.h"
#include <time.h>
using namespace std;
// #include "aux.h"
int main()
{
    Field field = Field(FIELD_DX,FIELD_DY,PEN_DX,PEN_DY,POLARITY);
    Point al_pos[MAX_ROBOT_COUNT];
    Point en_pos[MAX_ROBOT_COUNT];
    float al_ang[MAX_ROBOT_COUNT];
    float en_ang[MAX_ROBOT_COUNT];
    field.update_all(al_pos,al_ang,en_pos,en_ang,Point(10,10),time(NULL));
    // printf("%f",field.ball.pos.x);
    field.ball.pos.print();

    return 0;
}