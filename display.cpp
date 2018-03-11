#include "display.h"

display::display()
{
    std::cout<<"Constructor initialized";

    string start="<svg\nxmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\nxmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\nviewBox=\"0 0 800 800\"\nid=\"circuit\"\nversion=\"1.1\"\ninkscape:version=\"0.92.2 (unknown)\">\n<rect width=\"800\" height=\"800\" style=\"fill:rgb(250, 250, 252);stroke-width:1;stroke:rgb(110,0,0);opacity:1.0\">\n</rect>";
    outfile.open("output.svg");
    outfile<<start;
}

display::~display()
{
    string end="\n</svg>";
    outfile<<end;
    std::cout<<"Constructor destroyed";
}

void display::resistor(float rotateangle,float rotatex,float rotatey,float transformx,float transformy)
{
    string resistor="\n<g\nid=\"g4169\"\ntransform=\"rotate("+to_string(rotateangle)+","+to_string(rotatex)+","+to_string(rotatey)+")\"\ninkscape:label=\"Resistor\">\n"+"<g transform=\"translate("+to_string(transformx)+","+to_string(transformy)+")\">\n<g\nid=\"g4171\">\n<path\nid=\"path4173\"\ninkscape:label=\"none\"\nstyle=\"fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none\"\nd=\"m 0,0 h 15.5 l 2,3 3,-6 3,6 3,-6 3,6 3,-6 2,3 H 50\"\ninkscape:connector-curvature=\"0\" />\n</g>\n</g>\n</g>";
    outfile<<resistor;
}

void display::inductor()
{
    std::cout<<"Hii the resistor is imported";
}

void display::capacitor()
{
    std::cout<<"Hii the resistor is imported";
}

void display::ac_source()
{
    std::cout<<"Hii the resistor is imported";
}

void display::ground()
{
    std::cout<<"Hii the resistor is imported";
}

void display::wire()
{

}
