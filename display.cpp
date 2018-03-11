#include "display.h"

display::display()
{
    std::cout<<"Constructor initialized";
    outfile.open("output.svg");
    outfile<<"svg is going to written in it This is going to be awesome YO";
}

display::~display()
{
    std::cout<<"Constructor destroyed";
}

void display::resistor()
{
    std::cout<<"Hii the resistor is imported";
}
