#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

class display
{
    public:
        display();

        void resistor(float rotateangle,float transformx,float transformy,string type,string name,float magnitude,string unit,string fname);
        void inductor(float rotateangle,float translatex,float translatey,string type,string name,float magnitude,string unit,string fname);
        void capacitor(float rotateangle,float translatex,float translatey,string type,string name,float magnitude,string unit,string fname);
        void ac_source(float rotateangle,float translatex,float translatey,string type,string name,float dcoffset,float amplitude,float frequency,float delay,float df,string fname,bool posdirection);
        void ac_current(float rotateangle,float translatex,float translatey,string type,string name,float dcoffset,float amplitude,float frequency,float delay,float df,string fname,bool posdirection);  
        void ground(float rotateangle,float translatex,float translatey,std::vector<int> uniq);
        void wire(float x1,float y1,float x2,float y2);
        void text(float x1,float y1,string s);

        virtual ~display();

    protected:

    private:
            ofstream outfile;
            string start;
};

#endif // End DISPLAY_H
