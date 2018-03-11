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

        void resistor(float rotateangle,float rotatex,float rotatey,float transformx,float transformy);
        void inductor();
        void capacitor();
        void ac_source();
        void ground();
        void wire();

        virtual ~display();

    protected:

    private:
            ofstream outfile;
            string start;
};

#endif // End DISPLAY_H
