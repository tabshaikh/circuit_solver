#include "display.h"
#include "component.h"
#include "y.tab.h"
#include "solver.h"
using namespace std;

display d;      //Creating object d of display class
extern vector <component> components; //data in form of a structure
extern vector <int> uniq; //data in form of a structure
vector <float> netposx;//x coordinates of nets
vector <float> netposy;//y coordinates of nets
float offset=50;//offset of 50units
int base=0,top=0;
int flag=1;
char *inputfile;
extern vector <answer> result_final;
int rcount=0,lcount=0,ccount=0,vcount=0,icount=0;
ofstream outfile1;
extern vector <source> voltage;       
extern vector <source> current;       

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

int search_voltage_source(int name)
{
    for(int i=0;i<voltage.size();i++)
    {
        if(name==voltage[i].name)
        {
            return i;
        }
    }
}
int search_current_source(int name)
{
    for(int i=0;i<current.size();i++)
    {
        if(name==current[i].name)
        {
            return i;
        }
    }
}

void onclick(string image_name,double v1,double v2,double i1,double i2)
{

  string data=R"foo("<!DOCTYPE html>
    <html>
        <body>
        <center>
            <img src=")foo"+image_name+R"foo(" width="500" height="300">
            <h3>V = )foo";
    outfile1<<data;
    outfile1<<v1<<" "<<v2<<"</h3>\n<h3>I = "<<i1<<" "<<i2<<"</h3>\n</center>\n</body>\n</html>";
}

void write_component(float netpositionx,float netpositiony)
{   string fname="";
    int va=-1;
    int ia=-1;         
    switch(components[top].type)
    {
        case 'R':
        fname="r"+to_string(rcount)+".html";
        d.resistor(0,netpositionx,netpositiony,"R",components[top].name,components[top].magnitude,components[top].unit,fname);
        outfile1.open(fname);
        onclick("resistor.png",10,45,2,10);
        outfile1.close();
        rcount++;
        break;
        case 'L':
        fname="l"+to_string(lcount)+".html";
        d.inductor(0,netpositionx,netpositiony,"L",components[top].name,components[top].magnitude,components[top].unit,fname);
        outfile1.open(fname);
        onclick("inductor.png",10,45,2,10);
        outfile1.close();
        lcount++;
        break;
        case 'C':
        fname="c"+to_string(ccount)+".html";
        d.capacitor(0,netpositionx,netpositiony,"C",components[top].name,components[top].magnitude,components[top].unit,fname);
        outfile1.open(fname);
        onclick("capacitor.png",10,45,2,10);
        outfile1.close();
        ccount++;
        break;
        case 'V':
        fname="v"+to_string(vcount)+".html";
        va=search_voltage_source(stoi(components[top].name));
        if(voltage[va].start>voltage[va].end)
        d.ac_source(90,netpositionx+25,netpositiony-7,"V",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor,fname,true);
        else
        d.ac_source(90,netpositionx+25,netpositiony-7,"V",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor,fname,false);
        outfile1.open(fname);
        onclick("voltage_source.png",10,45,2,10);
        outfile1.close();
        vcount++;
        break;                                                                                                                                                                                      
        case 'I':
        fname="i"+to_string(icount)+".html";
        ia=search_current_source(stoi(components[top].name));
        if(current[ia].start>current[ia].end)
        d.ac_current(90,netpositionx+25,netpositiony-7,"I",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor,fname,true);
        else
        d.ac_current(90,netpositionx+25,netpositiony-7,"I",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor,fname,false);
        outfile1.open(fname);
        onclick("current_source.png",10,45,2,10);
        outfile1.close();
        icount++;
        break; 
    }
}

void arrange()
{
    for(int i=0; i < components.size(); i++)
    {
        int start=components[i].start;
        int end=components[i].end;
        components[i].start = (start)<(end)? (start):(end);
        components[i].end = (start)>(end)? (start):(end);
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

int main(int argc, char * argv[])
{
    inputfile = argv[1]; 
    if(parser()!=-1)
    {        
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
        solver();
        arrange();
        special_sort();
        display_circuit();
    }
    return 0;
}