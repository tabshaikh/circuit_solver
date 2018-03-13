#include "display.h"

display::display()
{
    string start=R"foo(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
    <svg id="demo-tiger"  xmlns="http://www.w3.org/2000/svg" xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd" xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape" viewBox="0 0 800 800" version="1.1">
    <g id="g4" fill="none" transform="translate(-300.000000,-650.000000) matrix(1.7656463,0,0,1.7656463,324.90716,255.00942)">
    )foo";
    outfile.open("output.svg");
    outfile<<start;
}

display::~display()
{
    string end="\n</g>\n</svg>";
    outfile<<end;
}

void display::resistor(float rotateangle,float transformx,float transformy,string type,string name,float magnitude,string unit)
{
    string resistor="\n<g\nid=\"g4169\"\ntransform=\"rotate("+to_string(rotateangle)+","+to_string(transformx)+","+to_string(transformy)+")\"\ninkscape:label=\"Resistor\">\n"+"<g transform=\"translate("+to_string(transformx)+","+to_string(transformy)+")\">\n<g\nid=\"g4171\">\n<path\nid=\"path4173\"\ninkscape:label=\"none\"\nstyle=\"fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none\"\nd=\"m 0,0 h 15.5 l 2,3 3,-6 3,6 3,-6 3,6 3,-6 2,3 H 50\"\ninkscape:connector-curvature=\"0\" />"+"\n<text x=\"13\" y=\"15\" font-size=\"3\" fill=\"black\" >"+type+name+"("+to_string(magnitude)+unit+")\n</text>\n</g>\n</g>\n</g>";
    outfile<<resistor;
}

void display::inductor(float rotateangle,float translatex,float translatey,string type,string name,float magnitude,string unit)
{
    string inductor1 ="\n <g \n inkscape:label=\"Inductor\" \n transform=\"rotate("+to_string(rotateangle)+","+to_string(translatex)+","+to_string(translatey)+
    ")\" \n id=\"g4326\"> \n <g transform=\"translate("+to_string(translatex)+","+to_string(translatey);

    string inductor2 = R"foo(
    )">`
    <g transform="translate(-360,-530)">
    <g
       inkscape:label="Inductor"
       id="g4328">
      <path
         d="m 360,530 h 13"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         inkscape:label="none"
         id="path4330"
         inkscape:connector-curvature="0" />
      <path
         d="M 410,530 H 397"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         inkscape:label="none"
         id="path4332"
         inkscape:connector-curvature="0" />
      <path
         d="m 379,530 a 3,3 0 0 1 -1.5,2.5980762114 3,3 0 0 1 -3,0 A 3,3 0 0 1 373,530"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         sodipodi:cx="376"
         sodipodi:cy="530"
         sodipodi:end="3.14159265359"
         sodipodi:open="true"
         sodipodi:rx="3"
         sodipodi:ry="3"
         sodipodi:start="0"
         sodipodi:type="arc"
         inkscape:label="arc"
         id="path4334" />
      <path
         d="m 385,530 a 3,3 0 0 1 -1.5,2.5980762114 3,3 0 0 1 -3,0 A 3,3 0 0 1 379,530"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         sodipodi:cx="382"
         sodipodi:cy="530"
         sodipodi:end="3.14159265359"
         sodipodi:open="true"
         sodipodi:rx="3"
         sodipodi:ry="3"
         sodipodi:start="0"
         sodipodi:type="arc"
         inkscape:label="arc"
         id="path4336" />
      <path
         d="m 391,530 a 3,3 0 0 1 -1.5,2.5980762114 3,3 0 0 1 -3,0 A 3,3 0 0 1 385,530"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         sodipodi:cx="388"
         sodipodi:cy="530"
         sodipodi:end="3.14159265359"
         sodipodi:open="true"
         sodipodi:rx="3"
         sodipodi:ry="3"
         sodipodi:start="0"
         sodipodi:type="arc"
         inkscape:label="arc"
         id="path4338" />
      <path
         d="m 397,530 a 3,3 0 0 1 -1.5,2.5980762114 3,3 0 0 1 -3,0 A 3,3 0 0 1 391,530"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         sodipodi:cx="394"
         sodipodi:cy="530"
         sodipodi:end="3.14159265359"
         sodipodi:open="true"
         sodipodi:rx="3"
         sodipodi:ry="3"
         sodipodi:start="0"
         sodipodi:type="arc"
         inkscape:label="arc"
         id="path4340" />
    </g>
    <text x="370" y="545" font-size="3" fill="black" >
    )foo" + type +name+ "(" + to_string(magnitude) + unit + ")" + "</text>\n</g>  </g> </g>";
    outfile<<inductor1<<inductor2;
}

void display::capacitor(float rotateangle,float translatex,float translatey,string type,string name,float magnitude,string unit)
{
    string capacitor= "\n<g\ninkscape:label=\"Capacitor\"\ntransform=\"rotate("+to_string(rotateangle)+","+to_string(translatex)+","+to_string(translatey)+") translate("+to_string(translatex)+","+to_string(translatey)+")\""+R"foo(
     id="g4198">
    <g transform="translate(0,-30)">
    <g
       inkscape:label="Capacitor"
       id="g4200">
      <path
         d="m 0,30 h 23"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         inkscape:label="none"
         id="path4202"
         inkscape:connector-curvature="0" />
      <path
         d="M 50,30 H 27"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         inkscape:label="none"
         id="path4204"
         inkscape:connector-curvature="0" />
      <path
         d="M 23,37 V 23"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         inkscape:label="none"
         id="path4206"
         inkscape:connector-curvature="0" />
      <path
         d="M 27,37 V 23"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
         inkscape:label="none"
         id="path4208"
         inkscape:connector-curvature="0" />
    </g>
    <text x="13" y="45" font-size="3" fill="black" >)foo"+type+name+"("+to_string(magnitude)+unit+")</text>\n</g>\n</g>";
    outfile<<capacitor;
}

void display::ac_source(float rotateangle,float translatex,float translatey,string type,string name,float dcoffset,float amplitude,float frequency,float delay,float df)
{
    string voltage = "\n<g \n id=\"g4164\" \n transform=\"translate("+to_string(translatex)+","+to_string(translatey)+") rotate("+to_string(rotateangle)+",0,0)\">"
    R"foo(
    <g transform="translate(0,-7)">
    <g transform="translate(20,4.5)">
    <path
       sodipodi:nodetypes="czzzc"
       inkscape:connector-curvature="0"
       transform="rotate(110,0,0)"
       id="path5536-8-3"
       d="m 0.3478974,9.7865691 c 0.67934,2.0380199 2.07525,4.0760499 4.09466,4.0760499 2.01941,0 3.3781,-2.03803 4.05744,-4.0760499 0.6793396,-2.03803 2.0380296,-4.07605 4.0760496,-4.07605 2.03803,0 3.39671,2.03802 4.07605,4.07605"
       style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1" />
    </g>
    <circle
       r="10"
       cy="9.7865725"
       cx="8.4999971"
       id="path14021-7-1-7"
       style="color:#000000;clip-rule:nonzero;display:inline;overflow:visible;visibility:visible;opacity:1;isolation:auto;mix-blend-mode:normal;color-interpolation:sRGB;color-interpolation-filters:linearRGB;solid-color:#000000;solid-opacity:1;fill:none;fill-opacity:1;fill-rule:nonzero;stroke:#000000;stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;color-rendering:auto;image-rendering:auto;shape-rendering:auto;text-rendering:auto;enable-background:accumulate" />
	<line x1="7.000000" y1="20.000000" x2="7.000000" y2="34.000000" stroke-width="1" stroke="black"/>
    <line x1="7.000000" y1="0.000000" x2="7.000000" y2="-19.000000" stroke-width="1" stroke="black"/>
    <text x="-90" y="-8" font-size="3" fill="black" transform="rotate(-90,0,0) translate(50,4)">)foo"+
	type+name+" SINE ("+ to_string(dcoffset) +" "+ to_string(amplitude) +" "+to_string(frequency)+"Khz "+ to_string(delay)+"S  "+to_string(df)+")\n</text>\n</g>\n</g>";
    outfile<<voltage;
}

void display::ground(float rotateangle,float translatex,float translatey)
{
    string ground ="\n<g\nid=\"layer1\" transform=\"translate("+to_string(translatex)+","+to_string(translatey)+")rotate("+to_string(rotateangle)+","+to_string(translatex)+","+to_string(translatey)+")scale(0.7)\">\n<g transform=\"translate(-12,-3)\">\n<path\nd=\"M 0.5,24.5 L 24.5,24.5\"\nstyle=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\nid=\"path4098\" />\n<path\nd=\"M 4.5,27.5 L 20.5,27.5\"\nstyle=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\nid=\"path4100\" />\n<path\nd=\"M 16.5,30.5 L 8.5,30.5\"\nstyle=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\nid=\"path4102\" />\n<path\nd=\"M 12.5,24.5 L 12.5,4.5\"\nstyle=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\nid=\"path4104\" />\n</g>\n</g>";
    outfile<<ground;
}

void display::wire(float x1,float y1,float x2,float y2)
{
   string line="\n<line x1=\""+to_string(x1)+"\" y1=\""+to_string(y1)+"\" x2=\""+to_string(x2)+"\" y2=\""+to_string(y2)+"\" stroke-width=\"1\" stroke=\"black\"/>";
    outfile<<line;
}
void display::text(float x1,float y1,string s)
{
   string text="\n<text x=\""+to_string(x1)+"\" y1=\""+to_string(y1)+"\" font-size=\"3\" fill=\"black\">"+s+"</text>";
   outfile<<text;
}
