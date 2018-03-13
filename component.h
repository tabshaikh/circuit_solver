struct component
{
    char type = ' ';
    std::string name = "";
    int start=0;
    int end=0;
    int magnitude=0;
    float dcoffset=0.0;
    float amplitude=0.0;
    float f=0.0;
    float delay=0.0;
    float dampingfactor=0.0;
    std::string unit="";
};