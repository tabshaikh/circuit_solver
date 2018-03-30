#include <complex>
#include <iostream>
using namespace std;
extern void solver();
struct answer
{
    char type;
    int name;
    double voltage;
    double current;
    double voltage_phase;
    double current_phase;
    complex<double> net_voltage;
    complex<double> net_current;
};