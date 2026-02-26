#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"



int main(){
    elevio_init();
    oppstart();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }

        // går gjennom alle knapper i alle etasjer og setter på lampe om den er trukket på
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b); // sjekker om en spesifik knapp er trukket på 
                elevio_buttonLamp(f, b, btnPressed); // setter lampens tilstand ( enten av eller på)
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP); // stopper motoren
            elevio_stopLamp(1); // setter på lyset til stopp knappen

            if (elevio_floorSensor !=-1){ // hvis vi er i en etasje
                
                // starte timer 3 sek , og deretter lukke døren
                while (elevio_stopButton()){
                    elevio_doorOpenLamp(1); // åpne dør 
                }
                // stoppknappen sluppet, vent i 3 sekunder 
                time_t sluppet =time(NULL);
                while(time(NULL)-sluppet<3) {
                    usleep(1000);
                }
                elevio_doorOpenLamp(0); // lukker døra igjen
            }

            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
