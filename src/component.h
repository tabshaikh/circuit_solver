struct component
{
    char type = ' ';
    std::string name = "";
    int start=0;
    int end=0;
    float magnitude=0;
    float dcoffset=0.0;
    float amplitude=0.0;
    float f=0.0;
    float delay=0.0;
    float dampingfactor=0.0;
    std::string unit="";
    component():type(' '), name(" "), start(0), end(0), magnitude(0), dcoffset(0), amplitude(0),f(0),delay(0),dampingfactor(0),unit(" ") {}
    component(char type_, std::string name_ ,int start_ ,int end_ ,int magnitude_ ,float dcoffset_ , float amplitude_ , float f_ ,float delay_ , float dampingfactor_,std::string unit_ ) : type(type_), name(name_), start(start_), end(end_), magnitude(magnitude_), dcoffset(dcoffset_), amplitude(amplitude_),f(f_),delay(delay_),dampingfactor(dampingfactor_),unit(unit_) { }
};
struct source
{
    int name=-1;
    int start=0;
    int end=0;
    float dcoffset=0.0;
    float amplitude=0.0;
    float f=0.0;
    float delay=0.0;
    float dampingfactor=0.0;
    std::string unit="";
};
extern int parser();
extern char *inputfile;