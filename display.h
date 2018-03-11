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

        void resistor();

        virtual ~display();

    protected:

    private:
            ofstream outfile;
            string start;
};

#endif // End DISPLAY_H
