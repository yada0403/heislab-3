#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include  <unistd.h>
#include "driver/ekstra.h"

int main(){
    elevio_init();
    oppstart();
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    
    while(1){
        int floor = elevio_floorSensor(); // lese etasje

        if(floor != -1){ // sjekker at vi er på etasje
            heis.currentFloor = floor;
            elevio_floorIndicator(floor); // setter på etasjelys

            // åpne døren hvis : 
            // hvis det er en cab bestilling, stopper alltid uavhening retning
            if ((heis.cab[floor]) ||
            // eller hvis heisen kjører opp og noen venter i etasjen og vil opp 
            (heis.currentDirection == DIRN_UP && heis.hallup[floor]) ||
             // eller hvis heisen kjører ned og noen venter i etasjen og vil ned 
            (heis.currentDirection == DIRN_DOWN && heis.halldown[floor])) 
            {
                elevio_motorDirection(0);
                elevio_doorOpenLamp(1);
                telle3sek();
                elevio_doorOpenLamp(0); //  deretter skur av lys
                
                //slett bestillinger
                heis.cab[floor] = 0;
                if (heis.currentDirection == DIRN_UP) {
                    heis.hallup[floor] =0;
                }
                if (heis.currentDirection == DIRN_DOWN) {
                    heis.halldown[floor] =0;
                } 
            }
        }
        
        // lese knapper og lagrer bestillinger 
        for(int f = 0; f < N_FLOORS; f++){ // går gjennom alle etasjer
            if(elevio_callButton(f, BUTTON_HALL_UP)) { // hvis hall up knapp trykket på
                heis.hallup[f] = 1; // 
            }  
            if(elevio_callButton(f, BUTTON_HALL_DOWN)) {//hvis hall down knapp trykket på
                heis.halldown[f] = 1; // 
            }
            if(elevio_callButton(f, BUTTON_CAB)){//hvis cab knapp trykket på
                heis.cab[f] = 1;
            }
             // går gjennom alle knapper i alle etasjer og setter på lampe om den er trukket på
            elevio_buttonLamp(f, BUTTON_HALL_UP,   heis.hallup[f]);
            elevio_buttonLamp(f, BUTTON_HALL_DOWN, heis.halldown[f]);
            elevio_buttonLamp(f, BUTTON_CAB,       heis.cab[f]);
        }

        oppdater_motor();

        // hvis stoppknapp er trukket på
        if(elevio_stopButton())
        { 
            heis.currentDirection = DIRN_STOP;
            elevio_motorDirection(DIRN_STOP); // stopper motoren
            elevio_stopLamp(1); // setter på lyset til stopp knappen
            slettAlleBestillinger();
            if (elevio_floorSensor() !=-1)
            { // hvis vi er i en etasje
                elevio_doorOpenLamp(1);
                while (elevio_stopButton()) {   
                }
                telle3sek();
                elevio_doorOpenLamp(0); // slår av stopp-lampen når den ikke trykkes lenger
            }
        } else {
            elevio_stopLamp(0); // slår av stopp-lampen når den ikke trykkes lenger
            
        }   
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
    return 0;
} // halla
