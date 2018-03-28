#include "display.h"
#include "component.h"
#include "y.tab.h"
using namespace std;

display d;      //Creating object d of display class
extern vector <component> components; //data in form of a structure
extern vector <int> uniq; //data in form of a structure
vector <float> netposx;//x coordinates of nets
vector <float> netposy;//y coordinates of nets
float offset=50;//offset of 50units
int base=0,top=0;
int flag=1;

//------------------------------------------------------------------------------------------------------
template<typename T, typename M, template<typename> class C = std::less>
struct member_comparer : std::binary_function<T, T, bool>
{
    explicit member_comparer(M T::*p) : p_(p) { }

    bool operator ()(T const& lhs, T const& rhs) const
    {
        return C<M>()(lhs.*p_, rhs.*p_);
    }

private:
    M T::*p_;
};

template<typename T, typename M>
member_comparer<T, M> make_member_comparer(M T::*p)
{
    return member_comparer<T, M>(p);
}

template<template<typename> class C, typename T, typename M>
member_comparer<T, M, C> make_member_comparer2(M T::*p)
{
    return member_comparer<T, M, C>(p);
}

//----------------------------------------------------------------------------------------------

void write_component(float netpositionx,float netpositiony)
{            
    switch(components[top].type)
    {
        case 'R':
        d.resistor(0,netpositionx,netpositiony,"R",components[top].name,components[top].magnitude,components[top].unit);
        break;
        case 'L':
        d.inductor(0,netpositionx,netpositiony,"L",components[top].name,components[top].magnitude,components[top].unit);
        break;
        case 'C':
        d.capacitor(0,netpositionx,netpositiony,"C",components[top].name,components[top].magnitude,components[top].unit);
        break;
        case 'V':
        d.ac_source(90,netpositionx+25,netpositiony-7,"V",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor);
        break;                                                                                                                                                                                      
        case 'I':
        d.ac_source(90,netpositionx+25,netpositiony-7,"I",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor);
        break; 
    }
}

void special_sort()
{
    std::sort(components.begin(), components.end(), make_member_comparer(&component::start));
    int num1=components[0].start;
    int count1=0,count2=0;   
    for(int i=0;i<components.size();i++)
    {
        if(num1!=components[i].start)
        {
            num1=components[i].start;
            std::sort(components.begin()+count1,components.begin()+count2,make_member_comparer(&component::end));
            count1=count2=i;
        }
        count2++;
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
    int startindex=searchnet(components[top].start);
    int endindex=searchnet(components[top].end);
    if(flag==0)//make circuit up
    {   
        d.wire(netposx[startindex],netposy[startindex],netposx[startindex],netposy[startindex]-diff);
        d.wire(netposx[endindex],netposy[endindex],netposx[endindex],netposy[endindex]-diff);
        d.wire(netposx[startindex],netposy[startindex]-diff,((netposx[endindex]+netposx[startindex])/2)-25,netposy[endindex]-diff);
        d.wire(((netposx[endindex]+netposx[startindex])/2)+25,netposy[endindex]-diff,netposx[endindex],netposy[endindex]-diff);
        write_component(((netposx[endindex]+netposx[startindex])/2)-25,netposy[startindex]-diff);
    }
    else
    {
        d.wire(netposx[startindex],netposy[startindex],netposx[startindex],netposy[startindex]+diff);
        d.wire(netposx[endindex],netposy[endindex],netposx[endindex],netposy[endindex]+diff);
        d.wire(netposx[startindex],netposy[startindex]+diff,((netposx[endindex]+netposx[startindex])/2)-25,netposy[endindex]+diff);
        d.wire(((netposx[endindex]+netposx[startindex])/2)+25,netposy[endindex]+diff,netposx[endindex],netposy[endindex]+diff);
        write_component(((netposx[endindex]+netposx[startindex])/2)-25,netposy[startindex]+diff);        
    }
}

void display_circuit()
{  
    while(base<components.size())
    {
        if(flag==0)
        {
            flag=1;
        }   
        else
        {
            flag=0;
        }
        while(components[base].start==components[top].start && top<components.size())
        {   
            int diff = (top-base)*offset;
            draw(diff);
            top++;
        }
        base=top;
    }
}

int main()
{  
    if(parser()!=-1)
    {    
        special_sort();
        //intializing the coordinates of each netname
        float startpos=150;
        for(int i=0;i<uniq.size();i++)
        {
            netposx.push_back(startpos);
            netposy.push_back(450);
            startpos+=50;
        }
        //making ground point 
        d.ground(0,netposx[0],netposy[0]-1,uniq);
        display_circuit();
    }
    return 0;
}