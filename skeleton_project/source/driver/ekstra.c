#include "elevio.h"
#include "ekstra.h"
#include <time.h>
// setter ordre til i første element i lista, må bestemme oss for hvor vi skal putte ordre(logikk)

Elevator heis;

void slettAlleBestillinger() {
    for (int f = 0;f < N_FLOORS; f++) { // går gjennom alle 4 etasjene
        //setter alle bestillinger 0
        heis.hallup[f] = 0; 
        heis.halldown[f]=0;
        heis.cab[f]  = 0;
    
    } 

}

void telle3sek() {
    time_t tidspunkt = time(NULL); // setter tidspunkt lik tiden nå
    while(time(NULL)-tidspunkt < 3) { // sjekker om det har gått 3 sek 
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
            // dette er for at vi fortsatt skal kunne lytte til knappene selv om vi teller til 3
             // går gjennom alle knapper i alle etasjer og setter på lampe om den er trukket på
            elevio_buttonLamp(f, BUTTON_HALL_UP,   heis.hallup[f]);
            elevio_buttonLamp(f, BUTTON_HALL_DOWN, heis.halldown[f]);
            elevio_buttonLamp(f, BUTTON_CAB,       heis.cab[f]);
        }
        
        if(elevio_obstruction()) {
            tidspunkt = time(NULL); // hver gang obstruksjon er aktiviert reset timeren til nå
            // døren forblir åpen så lenge obstruksjonen er aktiv, og lukker seg 3 sek etter at den slippes
        }

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL); // <
    }

}

void oppstart() {
    heis.currentFloor = 0; // setter at heisen starter i etasje 0
    heis.currentDirection = DIRN_STOP;; // stopper 
    slettAlleBestillinger(); 
    //elevio_motorDirection(DIRN_STOP);//setter retning 
    elevio_doorOpenLamp(0); // dørenåpen lampen er av
    elevio_stopLamp(0); // stopp knappen er av

  
    while (elevio_floorSensor() !=0) { // hvis ikke i en etasje 
        elevio_motorDirection(DIRN_DOWN);  // heisen går ned

    } 
    elevio_motorDirection(DIRN_STOP);//setter retning 
    heis.currentFloor = 0;
    //elevio_doorOpenLamp(0); // dørenåpen lampen er av
    //elevio_stopLamp(0); // stopp knappen er av

    // // if ( elevio_floorSensor()==0) { // når den har kommet til første etasje 
};


void oppdater_motor() {
    // sjekk om det er bestillinger over nåværende etasje
    for (int f = heis.currentFloor + 1;f<N_FLOORS;f++) {
        if (heis.cab[f] || heis.hallup[f] || heis.halldown[f]) {
            heis.currentDirection = DIRN_UP;
            elevio_motorDirection(DIRN_UP);
            return; // øsnker å stoppe funksjonen så fort vi finer den første bestillingen
        }
    }
    // sjekker om det er bestilliger under nåværende etasje
    for (int f = heis.currentFloor - 1;f>=0;f--) {
        if (heis.cab[f] || heis.hallup[f] || heis.halldown[f]) {
            heis.currentDirection = DIRN_DOWN;
            elevio_motorDirection(DIRN_DOWN);
            return; // øsnker å stoppe funksjonen så fort vi finer den første bestillingen
        }
    }

    //sjekker om det bestilli

    //ingen bestillinger
    heis.currentDirection = DIRN_STOP;
    elevio_motorDirection(DIRN_STOP);


}








