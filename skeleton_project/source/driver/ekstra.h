#include "elevio.h"
#include <stdbool.h>



typedef struct {
    int currentFloor;
    MotorDirection currentDirection;
    bool hallup[4];
    bool halldown[4];
    bool cab[4];

} Elevator;

extern Elevator heis;
void slettAlleBestillinger();
void telle3sek();
void oppstart();
void oppdater_motor();