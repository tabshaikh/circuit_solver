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
float offset=50;    //offset of 50units
int base=0,top=0;   
int flag=1; //For up-down placement of the branches according to even-odd rule
char *inputfile;
extern vector <answer> result_final; //This struct stores the results after calculation such as voltage and current across each component
int rcount=0,lcount=0,ccount=0,vcount=0,icount=0; // To count the number of resistors,inductors,capacitors and power sources in an ac-ciruit 
ofstream outfile1;  
extern vector <source> voltage;//Struct to store data of voltage sources       
extern vector <source> current;//Struct to store data of current sources       

//------------------------------------------------------------------------------------------------------
//This template is used to sort the struct using extended radix sort
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
//Searches for a specific voltage source among all voltage sources
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
//Searches for a specific current source among all current sources
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
//Searches for the result of a particular component
int search_result(char type,int name)
{
    for(int i=0;i<result_final.size();i++)
    {
        if(name==result_final[i].name && type==result_final[i].type)
        {
            return i;
        }
    }
}

/*n clicking the desired component this function makes the html file tailoured specific to the component and 
then links it with the component*/
void onclick(string image_name,double v1,double v2,double i1,double i2)
{

  string data=R"foo(<!DOCTYPE html>
    <html>
        <body>
        <center>
            <img src=")foo"+image_name+R"foo(" width="500" height="300">
            <h3>V = )foo";
    outfile1<<data;
    outfile1<<v1<<" /_"<<(v2*180)/3.141<<"</h3>\n<h3>I = "<<i1<<" /_"<<(i2*180)/3.141<<"</h3>\n</center>\n</body>\n</html>";
}

/*Writes the component in output.svg file*/
void write_component(float netpositionx,float netpositiony)
{   string fname="";
    int va=-1;
    int ia=-1;
    int respos=0;         
    switch(components[top].type)
    {
        case 'R':
        fname="./click/r"+to_string(rcount)+".html";
        respos=search_result(components[top].type,stoi(components[top].name));
        d.resistor(0,netpositionx,netpositiony,"R",components[top].name,components[top].magnitude,components[top].unit,fname);
        outfile1.open(fname);
        onclick("../circuit_elements/resistor.png",result_final[respos].voltage,result_final[respos].voltage_phase,result_final[respos].current,result_final[respos].current_phase);
        outfile1.close();
        rcount++;
        break;
        case 'L':
        fname="./click/l"+to_string(lcount)+".html";
        respos=search_result(components[top].type,stoi(components[top].name));
        d.inductor(0,netpositionx,netpositiony,"L",components[top].name,components[top].magnitude,components[top].unit,fname);
        outfile1.open(fname);
        onclick("../circuit_elements/inductor.png",result_final[respos].voltage,result_final[respos].voltage_phase,result_final[respos].current,result_final[respos].current_phase);
        outfile1.close();
        lcount++;
        break;
        case 'C':
        fname="./click/c"+to_string(ccount)+".html";
        respos=search_result(components[top].type,stoi(components[top].name));
        d.capacitor(0,netpositionx,netpositiony,"C",components[top].name,components[top].magnitude,components[top].unit,fname);
        outfile1.open(fname);        
        onclick("../circuit_elements/capacitor.png",result_final[respos].voltage,result_final[respos].voltage_phase,result_final[respos].current,result_final[respos].current_phase);
        outfile1.close();
        ccount++;
        break;
        case 'V':
        fname="./click/v"+to_string(vcount)+".html";
        va=search_voltage_source(stoi(components[top].name));
        respos=search_result(components[top].type,stoi(components[top].name));
        if(voltage[va].start>voltage[va].end)
        d.ac_source(90,netpositionx+25,netpositiony-7,"V",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor,fname,components[top].unit,true);
        else
        d.ac_source(90,netpositionx+25,netpositiony-7,"V",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor,fname,components[top].unit,false);
        outfile1.open(fname);
        onclick("../circuit_elements/voltage_source.png",result_final[respos].voltage,result_final[respos].voltage_phase,result_final[respos].current,result_final[respos].current_phase);
        outfile1.close();
        vcount++;
        break;                                                                                                                                                                                      
        case 'I':
        fname="./click/i"+to_string(icount)+".html";
        ia=search_current_source(stoi(components[top].name));
        respos=search_result(components[top].type,stoi(components[top].name));
        if(current[ia].start>current[ia].end)
        d.ac_current(90,netpositionx+25,netpositiony-7,"I",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor,fname,components[top].unit,true);
        else
        d.ac_current(90,netpositionx+25,netpositiony-7,"I",components[top].name,components[top].dcoffset,components[top].amplitude,components[top].f,components[top].delay,components[top].dampingfactor,fname,components[top].unit,false);
        outfile1.open(fname);
        onclick("../circuit_elements/current_source.png",result_final[respos].voltage,result_final[respos].voltage_phase,result_final[respos].current,result_final[respos].current_phase);
        outfile1.close();
        icount++;
        break; 
    }
}

//To arrange the components in a specific order ie. making the start net value of the component always less than the end net value
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

//Function used to call radix sort
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

//This searches the unique vector to find the array position of a given net name
int searchnet(int n)
{
    for(int i=0;i<uniq.size();i++)
    {
        if(uniq[i]==n)
        return(i);
    }
    return -1;
}

//Used to call write_component function and draws wires connecting the components together
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

//To sort the structure of the circuit according to the even odd method 
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

//Main function 
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