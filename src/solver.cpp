//  libraries for armadillo
#define ARMA_DONT_USE_WRAPPER
#define ARMA_USE_LAPACK
#include <iostream>
#include <armadillo>
#include <complex>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include "component.h"
#include "solver.h"

using namespace std;
using namespace arma;

extern vector <int> uniq;             //    structured data of node
extern vector <source> voltage;       //structured data of voltages
extern vector <source> current;       //structured data of current
extern vector <component> components; //structured data of all the components
vector <answer> result_temp;
vector <answer> result_final;

int n, m;

cx_mat A;
Mat<double> z;
cx_mat x;


double value(double val, char ch)
{
    if (ch == 'K'||ch == 'k')
    {
        return val * 1000.0;
    }
    else if (ch == 'M'||ch == 'm')
    {
        return val / 1000.0;
    }
    else if (ch == 'N'||ch == 'n')
    {
        return val / 1000000000.0;
    }
    else if (ch == 'P'||ch == 'p')
    {
        return val / 1000000000.0;
    }
    else if (ch == 'U'||ch == 'u')
    {
        return val / 1000000.0;
    }
    else
    {
        return val ;
    }
}

void makeBC()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (voltage[i].start == uniq[j+1])
            {
                A(j, n + i) = complex<double>(1, 0);
                A(n + i, j) = complex<double>(1, 0);
            }
            else if (voltage[i].end == uniq[j+1])
            {
                A(j, n + i) = complex<double>(-1, 0);
                A(n + i, j) = complex<double>(-1, 0);
            }
            else
            {
                A(j, n + i) = complex<double>(0, 0);
                A(n + i, j) = complex<double>(0, 0);
            }
        }
    }
}

// void makez()
// {
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < current.size(); j++)
//         {
//             if (current[j].start == uniq[i+1])
//             {
//                 z(i, 0) = current[j].amplitude;
//             }
//             else if (current[j].end == uniq[i+1])
//             {
//                 z(i, 0) = -1 * current[j].amplitude;
//             }
//         }
//     }
//     for (int i = 0; i < m; i++)
//     {
//         z(i + n, 0) = voltage[i].amplitude;
//     }
// }

int findagain(int s)
{
    for (int i = 0; i < n; i++)
    {
        if (uniq[i+1] == s)
        {
            return i;
        }
    }
    return -1;
}

int findvoltage(int s)
{
    for (int i = 0; i < m; i++)
    {
        if (voltage[i].name == s)
        {
            return i;
        }
    }
    return -1;
}

complex<double> impedence(char c, double magnitude, char unit, double f)
{
    double w = 2 * 3.14 * f;
    if (c == 'R')
    {
        return complex<double>(1.0 / value(magnitude, unit), 0);
    }
    else if (c == 'L')
    {
        return complex<double>(0, -1.0 / (value(magnitude, unit) * w));
    }
    else if (c == 'C')
    {
        return complex<double>(0, (value(magnitude, unit) * w));
    }
}

void makeG(double f)
{
    for (int i = 0; i < components.size(); i++)
    {
        if (components[i].type != 'V' && components[i].type != 'I')
        {
            if (components[i].start != -1 && components[i].end != -1)
            {
                int j1 = findagain(components[i].start);
                int j2 = findagain(components[i].end);
                A(j1, j1) += impedence(components[i].type, components[i].magnitude, components[i].unit[0], f);
                A(j2, j2) += impedence(components[i].type, components[i].magnitude, components[i].unit[0], f);
                A(j1, j2) -= impedence(components[i].type, components[i].magnitude, components[i].unit[0], f);
                A(j2, j1) -= impedence(components[i].type, components[i].magnitude, components[i].unit[0], f);
            }
            else if (components[i].start != -1 || components[i].end != -1)
            {
                int j1 = findagain(components[i].start);
                int j2 = findagain(components[i].end);
                if (j2 != -1)
                {
                    A(j2, j2) += impedence(components[i].type, components[i].magnitude, components[i].unit[0], f);
                }
                else if (j1 != -1)
                {
                    A(j1, j1) += impedence(components[i].type, components[i].magnitude, components[i].unit[0], f);
                }
            }
        }
    }
}

void filewrite(double f, char ch)
{
    if(ch=='h')
    {
        ch=NULL;
    }
    ofstream solverfile;
    solverfile.open("result.txt",ofstream::app);
    string voltages="",currents="";
    voltages+="FREQ = "+to_string(f)+ch+"hz\nVOLTAGES\n";
    for(int i=0;i<result_temp.size();i++)
    {
        voltages+=result_temp[i].type+to_string(result_temp[i].name)+" "+to_string(round(result_temp[i].voltage*1000.0)/1000.0)+" "+to_string(round(result_temp[i].voltage_phase*180*100.0/3.14)/100.0)+"\n";
        currents+=result_temp[i].type+to_string(result_temp[i].name)+" "+to_string(round(result_temp[i].current*1000.0)/1000.0)+" "+to_string(round(result_temp[i].current_phase*100.0*180/3.14)/100.0)+"\n";
        
    }
    currents=voltages+"CURRENT\n"+currents;
    solverfile << currents;
    solverfile.close();
}

void calculate(double f,char ch)
{
    cx_mat Z = cx_mat(z,zeros(n + m,1));
    x = solve(A, Z);
    cout<<"A is"<<A<<endl<<"Z is"<<Z<<endl<<"x is"<<x<<endl;
    result_temp.clear();
    for(int i=n;i<n+m;i++)
    {
        x(i,0)=-1.0*x(i,0);
    }
    for( int i=0; i<components.size(); i++)
    {
        answer temp;
        temp.type=components[i].type;
        temp.name=stoi(components[i].name);
        if(components[i].type=='V')
        {
            temp.voltage=components[i].amplitude;
            temp.voltage_phase=components[i].delay;
            temp.net_voltage=temp.voltage;
            temp.current=abs(x(findvoltage(temp.name)+n,0));
            temp.current_phase=arg(x(findvoltage(temp.name)+n,0));
            temp.net_current=x(findvoltage(temp.name)+n,0);
        }
        else
        {
            // complex<double> voltage_difference;
            if(components[i].start!=-1 && components[i].end!=-1)
            {
                temp.net_voltage=x(findagain(components[i].start),0)-x(findagain(components[i].end),0);
            }
            else
            {
                if(components[i].end!=-1)
                {
                    temp.net_voltage=-x(findagain(components[i].end),0);
                }
                else if(components[i].start!=-1)
                {
                    temp.net_voltage=(x(findagain(components[i].start),0));                    
                }                
            }

            temp.voltage=abs(temp.net_voltage);
            temp.voltage_phase=arg(temp.net_voltage);

            if(components[i].type=='I')
            {
                temp.current=components[i].amplitude;
                temp.current_phase=components[i].delay;
                temp.net_current=temp.current;                                        
            }
            else
            {
                temp.net_current=temp.net_voltage*impedence(components[i].type, components[i].magnitude, components[i].unit[0],value(f,ch));
                temp.current=abs(temp.net_current);
                temp.current_phase=arg(temp.net_current);                                        
            }
        }
        result_temp.push_back(temp);
        result_final[i].net_current+=temp.net_current;
        result_final[i].net_voltage+=temp.net_voltage;
        result_final[i].voltage=abs(result_final[i].net_voltage);
        result_final[i].voltage_phase=arg(result_final[i].net_voltage);
        result_final[i].current=abs(result_final[i].net_current);
        result_final[i].current_phase=arg(result_final[i].net_current);

    }
    filewrite(f,ch);
}
void solver()
{
    remove("result.txt");
    n = uniq.size()-1;    //  number of nodes
    m = voltage.size(); //  number of voltages sources
    for(int i=0;i<components.size();i++)
    {
        answer temp;

        temp.type=components[i].type;
        temp.name=stoi(components[i].name);
        temp.current_phase=0;
        temp.current=0;
        temp.net_current=(0,0);
        temp.voltage_phase=0;
        temp.voltage=0;
        temp.net_voltage=(0,0);
        
        result_final.push_back(temp);
    }
    
    int l=current.size();
    for(int i=0;i<l+m;i++)
    {
        A = zeros<cx_mat>(n + m, n + m);
        x = zeros<cx_mat>(n+m, 1);
        z = mat(n + m, 1, fill::zeros);
        makeBC();   //  Prepare the B, C and D Matrix

        if(i<l)
        {
            makeG(value(current[i].f,current[i].unit[0]));
            for (int t = 0; t < n; t++)
            {
                if (current[i].start == uniq[t+1])
                {
                    z(t, 0) = current[i].amplitude;
                }
                else if (current[i].end == uniq[t+1])
                {
                    z(t, 0) = -1 * current[i].amplitude;
                }        
            }
            calculate(current[i].f,current[i].unit[0]);
        }
        else
        {
            makeG(value(voltage[i-l].f,voltage[i-l].unit[0]));
            z(i-l + n, 0) = voltage[i-l].amplitude;
            calculate(voltage[i-l].f,voltage[i-l].unit[0]);
        }
    }
}