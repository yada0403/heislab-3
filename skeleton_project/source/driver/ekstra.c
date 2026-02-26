#include <elevio.h>
#include <ekstra.h>
// setter ordre til i første element i lista, må bestemme oss for hvor vi skal putte ordre(logikk)


void oppstart() {
    Elevator heis = {
        .stoppknapp = 0,
        .hallup = {0,0,0,0},
        .halldown = {0,0,0,0},
        .cab = {0,0,0,0}

    };
    
    while (elevio_floorSensor() ==-1) { // hvis ikke i en etasje 
        elevio_motorDirection(DIRN_DOWN);  // heisen går ned
        

    } 
    if ( elevio_floorSensor()==0) { // når den har kommet til første etasje 
        elevio_motorDirection(DIRN_STOP);//så stopper heise
        elevio_floorIndicator(0); // sette etasjeindikator til 0
    }    
    elevio_doorOpenLamp(0); // døren er ikke åpen
    elevio_stopLamp(0); // stopp knappen er av
    
};