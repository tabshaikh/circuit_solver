#include "display.h"
#include "component.h"
//flag ground 

#include <vector>

display d;//Creating object d of display class
vector <string> netnames;
vector <float> netposx;
vector <float> netposy;
vector <component> components;
float offset=50;

vector <int> nodes;

void write_component(char type,float netposx,float netposy,int count,float value,string unit,float dcoffset,float amplitude,float frequency,float delay,float df)
{
    switch(type)
    {
        case 'R':
        d.resistor(rotateangle,netposx,netposy,"R",count,value,unit);
        break;
        case 'L':
        d.inductor(rotateangle,netposx,netposy,"L",count,value,unit);
        break;
        case 'C':
        d.capacitor(rotateangle,netposx,netposy,"C",count,value,unit);
        break;
        case 'V':
        d.ac_source(rotateangle,netposx,netposy,"V",count,dcoffset,amplitude,frequency,delay,df);
        break;                                                                                                                                                                                      
        case 'I':
        break; 
    }
}
int main()
{   
    int sizearray=4;
    netnames.push_back(components[0].start);
    netnames.push_back(components[0].end);
    netposx.push_back(400);
    netposy.push_back(50);
    write_component(components[0].type,netposx[0],netposy[0],components[0].count,components[0].value,components[0].unit,components[0].dcoffset,components[0].amplitude,components[0].frequency,components[0].delay,components[0].df);
        
    for(int i=1;i<sizearray;i++)
    {
        int startfound=0,endfound=0;
        for(int j=0;j<netnames.size();j++)
        {
            float netposstart=0,netposend=0;
            if((components[i].start).compare(netnames[j])==0)
            {
                startfound=1;
                netposstart=j;
            }
            if((components[i].end).compare(netnames[j])==0)
            {
                startfound=1;
                netposend=j;
            }
        }
        if(startfound==1 || endfound==1)
        {
            if(endfound==1 && startfound==1)
            {
                    write_component(components[i].type,netposx[netposstart],netposy[0],components[i].count,components[i].value,components[i].unit,components[i].dcoffset,components[i].amplitude,components[i].frequency,components[i].delay,components[i].df);
            }
            else if(endfound==1)
            {

            }
            else
            {

            }
        }
        else
        {

        }
    }
    string netname[10];
    float netpositionx[10];
    float netpositiony[10];
    netname[0]="Net3";
    netname[1]="0";
    netpositionx[0]=330;
    netpositiony[0]=330;
    netpositionx[1]=330;
    netpositiony[1]=380;
    display d;
    d.resistor(90,netpositionx[0],netpositiony[0],"R",1,100.4,"OHM");
  //d.inductor(0,100,50,"L",1,100.4,"KH");
    d.capacitor(270,330,330,"C",1,100.4,"KF");
  //d.ac_source(90,212,43,"V",1,0,0,0,0,0);
    d.ground(0,netpositionx[1],netpositiony[1]);
   // d.wire(50,50,50,25);
   // d.wire(50,25,212,25);
   // d.wire(212,25,212,43);
    return 0;
}