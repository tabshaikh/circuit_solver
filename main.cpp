#include "display.h"

int main()
{   
    display d;
    d.resistor(0,50,50,"R",1,100.4,"OHM");
    d.inductor(0,100,50,"L",1,100.4,"KH");
    d.capacitor(0,150,50,"C",1,100.4,"KF");
    d.ac_source(90,212,43,"V",1,0,0,0,0,0);
    d.ground(0,50,50);
    d.wire(50,50,50,25);
    d.wire(50,25,212,25);
    d.wire(212,25,212,43);
    
    return 0;
}