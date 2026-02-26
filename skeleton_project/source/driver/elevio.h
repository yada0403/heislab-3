#pragma once


#define N_FLOORS 4

typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;


void elevio_init(void);
//setter funksjoner, setter tilstand 
void elevio_motorDirection(MotorDirection dirn);// setter motorretning. Du sender DIRN_Up, DIRN_DOWN, DIRN_STOP
void elevio_buttonLamp(int floor, ButtonType button, int value); // skrur en knappelampe av eller på, value 1 eller 0
void elevio_floorIndicator(int floor); // setter etasjeindikator, viser hvilken etasje heisen er i 
void elevio_doorOpenLamp(int value); // skur dør åpen lampen av eller på
void elevio_stopLamp(int value); // skurs stoppknap lampen av eller på 


//spørs om tilstand får svar tilbake svar
int elevio_callButton(int floor, ButtonType button); // returnerer 1 om den bestemte knappen i den etasjen er trukket på, hvis ikke 0
int elevio_floorSensor(void);// returnerer etasjenummer (0-3), -1 hvis den er i mellom etasjer
int elevio_stopButton(void);//returnerer 1 hvis stoppknappen er trykket, 0 ellers
int elevio_obstruction(void); // retunerer 1 hvis obstruksjonsbryteren er aktivert, 0

