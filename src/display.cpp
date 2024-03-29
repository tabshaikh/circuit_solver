#include "display.h"

//Constructor used to open the file name output.svg and write the header and compulsory data present in every svg
display::display()
{
    string start=R"foo(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
    <svg id="demo-tiger"  xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 800 800" version="1.1">
    <g id="g4" fill="none" transform="translate(-350.000000,-600.000000) matrix(1.7656463,0,0,1.7656463,324.90716,255.00942)">
    )foo";
    outfile.open("output.svg");
    outfile<<start;
}

//Destructor used to close the output.svg file and put the ending tags
display::~display()
{
    string end="\n</g>\n</svg>";
    outfile<<end;
}

//Function that writes the resistor in output.svg file
void display::resistor(float rotateangle,float transformx,float transformy,string type,string name,float magnitude,string unit,string fname)
{
    string resistor="\n<a xlink:href=\""+fname+"\" target=\"_blank\" >\n<g\nid=\"g4169\"\ntransform=\"rotate("+to_string(rotateangle)+","+to_string(transformx)+","+to_string(transformy)+")\"\n label=\"Resistor\">\n"+"<g transform=\"translate("+to_string(transformx)+","+to_string(transformy)+")\">\n<g\nid=\"g4171\">\n<path\nid=\"path4173\"\n label=\"none\"\nstyle=\"fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none\"\nd=\"m 0,0 h 15.5 l 2,3 3,-6 3,6 3,-6 3,6 3,-6 2,3 H 50\"\n connector-curvature=\"0\" />"+"\n<text x=\"20\" y=\"10\" font-size=\"3\" fill=\"black\" >"+type+name+"(";    
    outfile<<resistor;
    outfile<<magnitude;
    string remaining=unit+")\n</text>\n</g>\n</g>\n</g>\n</a>";
    outfile<<remaining;
}

//Function that writes the inductor in output.svg file
void display::inductor(float rotateangle,float translatex,float translatey,string type,string name,float magnitude,string unit,string fname)
{
    string inductor1 ="\n<a xlink:href=\""+fname+"\" target=\"_blank\">\n <g \n  label=\"Inductor\" \n transform=\"rotate("+to_string(rotateangle)+","+to_string(translatex)+","+to_string(translatey)+
    ")\" \n id=\"g4326\"> \n <g transform=\"translate("+to_string(translatex)+","+to_string(translatey);

    string inductor2 = R"foo(
    )">`
    <g transform="translate(-360,-530)">
    <g
        label="Inductor"
       id="g4328">
      <path
         d="m 360,530 h 13"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          label="none"
         id="path4330"
          connector-curvature="0" />
      <path
         d="M 410,530 H 397"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          label="none"
         id="path4332"
          connector-curvature="0" />
      <path
         d="m 379,530 a 3,3 0 0 1 -1.5,2.5980762114 3,3 0 0 1 -3,0 A 3,3 0 0 1 373,530"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          cx="376"
          cy="530"
          end="3.14159265359"
          open="true"
          rx="3"
          ry="3"
          start="0"
          type="arc"
          label="arc"
         id="path4334" />
      <path
         d="m 385,530 a 3,3 0 0 1 -1.5,2.5980762114 3,3 0 0 1 -3,0 A 3,3 0 0 1 379,530"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          cx="382"
          cy="530"
          end="3.14159265359"
          open="true"
          rx="3"
          ry="3"
          start="0"
          type="arc"
          label="arc"
         id="path4336" />
      <path
         d="m 391,530 a 3,3 0 0 1 -1.5,2.5980762114 3,3 0 0 1 -3,0 A 3,3 0 0 1 385,530"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          cx="388"
          cy="530"
          end="3.14159265359"
          open="true"
          rx="3"
          ry="3"
          start="0"
          type="arc"
          label="arc"
         id="path4338" />
      <path
         d="m 397,530 a 3,3 0 0 1 -1.5,2.5980762114 3,3 0 0 1 -3,0 A 3,3 0 0 1 391,530"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          cx="394"
          cy="530"
          end="3.14159265359"
          open="true"
          rx="3"
          ry="3"
          start="0"
          type="arc"
          label="arc"
         id="path4340" />
    </g>
    <text x="380" y="540" font-size="3" fill="black" >
    )foo" + type +name+ "(";
    outfile<<inductor1<<inductor2;
    outfile<<magnitude;
    string remaining= unit + ")" + "</text>\n</g>  \n</g> \n</g>\n</a>";
    outfile<<remaining;
}

//Function that writes the capacitor in output.svg file
void display::capacitor(float rotateangle,float translatex,float translatey,string type,string name,float magnitude,string unit,string fname)
{
    string capacitor= "\n<a xlink:href=\""+fname+"\" target=\"_blank\">\n<g\n label=\"Capacitor\"\ntransform=\"rotate("+to_string(rotateangle)+","+to_string(translatex)+","+to_string(translatey)+") translate("+to_string(translatex)+","+to_string(translatey)+")\""+R"foo(
     id="g4198">
    <g transform="translate(0,-30)">
    <g
        label="Capacitor"
       id="g4200">
      <path
         d="m 0,30 h 23"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          label="none"
         id="path4202"
          connector-curvature="0" />
      <path
         d="M 50,30 H 27"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          label="none"
         id="path4204"
          connector-curvature="0" />
      <path
         d="M 23,37 V 23"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          label="none"
         id="path4206"
          connector-curvature="0" />
      <path
         d="M 27,37 V 23"
         style="fill:none;stroke:#000000;stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stroke-dasharray:none"
          label="none"
         id="path4208"
          connector-curvature="0" />
    </g>
    <text x="20" y="45" font-size="3" fill="black" >)foo"+type+name+"(";
    outfile<<capacitor;
    outfile<<magnitude;
    string remaining=unit+")</text>\n</g>\n</g>\n</a>";
    outfile<<remaining;
}

//Function that writes the voltage source in output.svg file
void display::ac_source(float rotateangle,float translatex,float translatey,string type,string name,float dcoffset,float amplitude,float frequency,float delay,float df,string fname,string unit,bool posdirection)
{
    string voltage = "\n<g \n id=\"g4164\" \n transform=\"translate("+to_string(translatex)+","+to_string(translatey)+") rotate("+to_string(rotateangle)+",0,0)\">"
    R"foo(
    <g transform="translate(0,-7)">
    <a xlink:href=")foo"+fname+R"foo(" target="_blank">
    <g transform="translate(20,4.5)">
    <path
        nodetypes="czzzc"
        connector-curvature="0"
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
  <line x1="7.000000" y1="20.000000" x2="7.000000" y2="32.50000" stroke-width="1" stroke="black"/>
    <line x1="7.000000" y1="0.000000" x2="7.000000" y2="-19.000000" stroke-width="1" stroke="black"/>
  )foo";
  outfile<<voltage;
  if(posdirection)
  {
  string v1=R"foo(<text x="6" y="23" transform="rotate(90,8,23)" font-size="7" fill="black">-</text>
    <text x="8" y="-2" font-size="5" fill="black">+</text>
    <text x="-80" y="-8" font-size="3" fill="black" transform="rotate(-90,0,0) translate(50,4)">)foo"+
  type+name+" SINE (";
  outfile<<v1;
  }
  else
  {
    string v1=R"foo(<text x="6" y="23" transform="rotate(90,8,23)" font-size="5" fill="black">+</text>
    <text x="8" y="-2" font-size="7" transform="translate(0,-2) rotate(90,8,-2)" fill="black">-</text>
    <text x="-80" y="-8" font-size="3"  fill="black" transform="rotate(-90,0,0) translate(50,4)">)foo"+
    type+name+" SINE (";
    outfile<<v1;
  }    
    outfile<<dcoffset<<" "<<amplitude<<" "<<frequency<<unit<<" "<<delay<<"S  "<<df<<")\n</text></a>\n</g>\n</g>";
}

//Function that writes the current source in output.svg file
void display::ac_current(float rotateangle,float translatex,float translatey,string type,string name,float dcoffset,float amplitude,float frequency,float delay,float df,string fname,string unit,bool posdirection)
{
    string voltage = "\n<g \n id=\"g4164\" \n transform=\"translate("+to_string(translatex)+","+to_string(translatey)+") rotate("+to_string(rotateangle)+",0,0)\">"
    R"foo(
    <g transform="translate(0,-7)">
    <a xlink:href=")foo"+fname+R"foo(" target="_blank">
    <g transform="translate(20,4.5)">)foo";
    if(!posdirection)
    voltage+="\n<g transform=\"translate(-7,-5) rotate(90,0,5)\">";
    else
    voltage+="\n<g transform=\"translate(-17,6) rotate(-90,0,5)\">";

    voltage+=R"foo(<line x1="0" y1="10" x2="10.5" y2="10" stroke="#000" 
      stroke-width="1" />
      <line x1="8" y1="15" x2="10" y2="10" stroke="#000" 
      stroke-width="1" />
      <line x1="8" y1="5" x2="10" y2="10" stroke="#000" 
      stroke-width="1" />
      </g>
    </g>
    <circle
       r="10"
       cy="9.7865725"
       cx="8.4999971"
       id="path14021-7-1-7"
       style="color:#000000;clip-rule:nonzero;display:inline;overflow:visible;visibility:visible;opacity:1;isolation:auto;mix-blend-mode:normal;color-interpolation:sRGB;color-interpolation-filters:linearRGB;solid-color:#000000;solid-opacity:1;fill:none;fill-opacity:1;fill-rule:nonzero;stroke:#000000;stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;color-rendering:auto;image-rendering:auto;shape-rendering:auto;text-rendering:auto;enable-background:accumulate" />
  <line x1="7.000000" y1="20.000000" x2="7.000000" y2="32.50000" stroke-width="1" stroke="black"/>
    <line x1="7.000000" y1="0.000000" x2="7.000000" y2="-19.000000" stroke-width="1" stroke="black"/>
    <text x="-80" y="-8" font-size="3" fill="black" transform="rotate(-90,0,0) translate(50,4)">)foo"+
  type+name+" SINE (";
    outfile<<voltage;    
    outfile<<dcoffset<<" "<<amplitude<<" "<<frequency<<unit<<" "<<delay<<"S  "<<df<<")\n</text></a>\n</g>\n</g>";
}

//Function that writes the ground terminal in output.svg file
void display::ground(float rotateangle,float translatex,float translatey,std::vector<int> uniq)
{
    string ground ="\n<g\nid=\"layer1\" transform=\"translate("+to_string(translatex)+","+to_string(translatey)+")rotate("+to_string(rotateangle)+","+to_string(translatex)+","+to_string(translatey)+")scale(0.7)\">\n<g transform=\"translate(-12.5,-3)\">";
    outfile<<ground;
    int pos=0;
    for (int i=0;i<uniq.size();i++)
    {
      if(i==0)
        {
            text(pos-10,475,"Ground");
            pos+=75;
        }
      else if(i==uniq.size()-1)
        {
            text(pos+10,475,"Net "+to_string(uniq[i]));
            pos+=75;
        }
      else
        {
            text(pos,475,"Net "+to_string(uniq[i]));
            pos+=75;
        }

    }
    string part2 ="\n<path\nd=\"M 0.5,24.5 L 24.5,24.5\"\nstyle=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\nid=\"path4098\" />\n<path\nd=\"M 4.5,27.5 L 20.5,27.5\"\nstyle=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\nid=\"path4100\" />\n<path\nd=\"M 16.5,30.5 L 8.5,30.5\"\nstyle=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\nid=\"path4102\" />\n<path\nd=\"M 12.5,24.5 L 12.5,4.5\"\nstyle=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\nid=\"path4104\" />\n</g>\n</g>";
    outfile<<part2;
}

//Function used to draw a wire in svg 
void display::wire(float x1,float y1,float x2,float y2)
{
   string line="\n<line x1=\""+to_string(x1)+"\" y1=\""+to_string(y1)+"\" x2=\""+to_string(x2)+"\" y2=\""+to_string(y2)+"\" stroke-width=\"1\" stroke=\"black\"/>";
    outfile<<line;
}

//Function that writes text in output.svg file
void display::text(float x1,float y1,string s)
{
   string text="\n<text x=\""+to_string(x1)+"\" y1=\""+to_string(y1)+"\" font-size=\"5\" fill=\"black\">"+s+"</text>";
   outfile<<text;
}
