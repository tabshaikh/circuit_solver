#include "display.h"
#include "component.h"

display d;      //Creating object d of display class
extern vector <component> components; //data in form of a structure
vector <float> netposx;//x coordinates of nets
vector <float> netposy;//y coordinates of nets
float offset=50;//offset of 50units
int base=0,top=0;

void write_component(float netpositionx,float netpositiony)
{            
    switch(component[top].type)
    {
        case 'R':
        d.resistor(0,netpositionx,netpositiony,"R",component[top].name,component[top].magnitude,component[top].unit);
        break;
        case 'L':
        d.inductor(0,netpositionx,netpositiony,"L",component[top].name,component[top].magnitude,component[top].unit);
        break;
        case 'C':
        d.capacitor(0,netpositionx,netpositiony,"C",component[top].name,component[top].magnitude,component[top].unit);
        break;
        case 'V':
        d.ac_source(90,netpositionx,netpositiony,"V",component[top].name,component[top].dcoffset,component[top].amplitude,component[top].frequency,component[top].delay,component[top].df);
        break;                                                                                                                                                                                      
        case 'I':
        break; 
    }
}

void special_sort()
{
    std::sort(components.begin(), components.end(), make_member_comparer(&component::start));
    for(int i=0;i<components.size();i++)
    {
      cout<<components[i].start<<components[i].end<<endl;
    }
    int num1=components[0].start;
    int count1=0,count2=0;   
    for(int i=0;i<components.size();i++)
    {
        if(num1!=components[i].a)
        {
            num1=components[i].a;
            std::sort(components.begin()+count1,components.begin()+count2,make_member_comparer(&component::b));
            count1=count2=i;
        }
        count2++;
    }
    for(int i=0;i<components.size();i++)
    {
      cout<<components[i].a<<components[i].b<<endl;
    }
}

int searchnet(int n)
{
    for(int i=0;i<uniq.size();i++)
    {
        if(uniq[i]==n)
        return(i);
    }
    return -1;
}

void draw(int diff)
{
    int startindex=searchnet(components[top].start());
    int endindex=searchnet(components[top].end());
    if(base%2==0)//make circuit up
    {
        if(diff!=0)
        {
            d.wire(netposx[startindex],netposy[startindex],netposx[startindex],netposy[startindex]-diff);
            d.wire(netposx[startindex],netposy[startindex],netposx[startindex],netposy[startindex]-diff);
            d.wire(netposx[startindex],netposy[startindex]-diff,((netposx[endindex]+netposx[startindex])/2)-25,netposy[endindex]-diff);
            d.wire(((netposx[endindex]+netposx[startindex])/2)+25,netposy[endindex]-diff,netposx[endindex],netposy[endindex]-diff);
            write_component(((netposx[endindex]+netposx[startindex])/2)-25,netposy[startindex]-diff);
        }
        else
        {
            d.wire(netposx[startindex],netposy[startindex],((netposx[endindex]+netposx[startindex])/2)-25,netposy[endindex]);
            d.wire(((netposx[endindex]+netposx[startindex])/2)+25,netposy[endindex],netposx[endindex],netposy[endindex]);
            write_component(((netposx[endindex]+netposx[startindex])/2)-25,diff+netposy[startindex]);
        }
    }
    else
    {
        if(diff!=0)
        {
            d.wire(netposx[startindex],netposy[startindex],netposx[startindex],netposy[startindex]+diff);
            d.wire(netposx[startindex],netposy[startindex],netposx[startindex],netposy[startindex]+diff);
            d.wire(netposx[startindex],netposy[startindex]+diff,((netposx[endindex]+netposx[startindex])/2)-25,netposy[endindex]+diff);
            d.wire(((netposx[endindex]+netposx[startindex])/2)+25,netposy[endindex]+diff,netposx[endindex],netposy[endindex]+diff);
            write_component(((netposx[endindex]+netposx[startindex])/2)-25,netposy[startindex]+diff);
        }
        else
        {
            d.wire(netposx[startindex],netposy[startindex],((netposx[endindex]+netposx[startindex])/2)-25,netposy[endindex]);
            d.wire(((netposx[endindex]+netposx[startindex])/2)+25,netposy[endindex],netposx[endindex],netposy[endindex]);
            write_component(((netposx[endindex]+netposx[startindex])/2)-25,diff+netposy[startindex]);
        }
    }
}

void display()
{
    while(base!=components.size())
    {
        while(components[base].start==components[top].start)
        {
            diff=(top-base)*offset;
            draw(diff);
            top++;
        }
        base=top;
    }
}

int main()
{   
    special_sort();
    //intializing the coordinates of each netname
    int startpos=150;
    for(int i=0;i<uniq.size();i++)
    {
        netposx.pushback(startpos);
        netposy.pushback(450);
        startpos+=50;
    }
    //making ground point 
    d.ground(0,netposx[0],netposy[0]);
    display();
    return 0;
}