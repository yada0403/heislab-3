#include <elevio.h>
#include <stdbool.h>



typedef struct {
    int floor;
    MotorDirection direction;
    bool stoppknapp;
    bool dooropen;
    bool hallup[4];
    bool halldown[4];
    bool cab[4];

} Elevator;


void oppstart();
