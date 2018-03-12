#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class display
{
    public:
        display();

        void resistor(float rotateangle,float transformx,float transformy,string type,int count,float magnitude,string unit);
        void inductor(float rotateangle,float translatex,float translatey,string type,int count,float magnitude,string unit);
        void capacitor(float rotateangle,float translatex,float translatey,string type,int count,float magnitude,string unit);
        void ac_source(float rotateangle,float translatex,float translatey,string type,int count,float dcoffset,float amplitude,float frequency,float delay,float df);
        void ground(float rotateangle,float translatex,float translatey);
        void wire(float x1,float y1,float x2,float y2);

        virtual ~display();

    protected:

    private:
            ofstream outfile;
            string start;
};

#endif // End DISPLAY_H
